bool fixSSA(Procedure& proc)
{
    PhaseScope phaseScope(proc, "fixSSA");
    
    // Collect the stack "variables". If there aren't any, then we don't have anything to do.
    // That's a fairly common case.
    HashMap<StackSlotValue*, Type> stackVariable;
    for (Value* value : proc.values()) {
        if (StackSlotValue* stack = value->as<StackSlotValue>()) {
            if (stack->kind() == StackSlotKind::Anonymous)
                stackVariable.add(stack, Void);
        }
    }

    if (stackVariable.isEmpty())
        return false;

    // Make sure that we know how to optimize all of these. We only know how to handle Load and
    // Store on anonymous variables.
    for (Value* value : proc.values()) {
        auto reject = [&] (Value* value) {
            if (StackSlotValue* stack = value->as<StackSlotValue>())
                stackVariable.remove(stack);
        };
        
        auto handleAccess = [&] (Value* access, Type type) {
            StackSlotValue* stack = access->lastChild()->as<StackSlotValue>();
            if (!stack)
                return;
            
            if (value->as<MemoryValue>()->offset()) {
                stackVariable.remove(stack);
                return;
            }

            auto result = stackVariable.find(stack);
            if (result == stackVariable.end())
                return;
            if (result->value == Void) {
                result->value = type;
                return;
            }
            if (result->value == type)
                return;
            stackVariable.remove(result);
        };
        
        switch (value->opcode()) {
        case Load:
            // We're OK with loads from stack variables at an offset of zero.
            handleAccess(value, value->type());
            break;
        case Store:
            // We're OK with stores to stack variables, but not storing stack variables.
            reject(value->child(0));
            handleAccess(value, value->child(0)->type());
            break;
        default:
            for (Value* child : value->children())
                reject(child);
            break;
        }
    }

    Vector<StackSlotValue*> deadValues;
    for (auto& entry : stackVariable) {
        if (entry.value == Void)
            deadValues.append(entry.key);
    }

    for (StackSlotValue* deadValue : deadValues) {
        deadValue->replaceWithNop();
        stackVariable.remove(deadValue);
    }

    if (stackVariable.isEmpty())
        return false;

    // We know that we have variables to optimize, so do that now.
    breakCriticalEdges(proc);

    SSACalculator ssa(proc);

    // Create a SSACalculator::Variable for every stack variable.
    Vector<StackSlotValue*> variableToStack;
    HashMap<StackSlotValue*, SSACalculator::Variable*> stackToVariable;

    for (auto& entry : stackVariable) {
        StackSlotValue* stack = entry.key;
        SSACalculator::Variable* variable = ssa.newVariable();
        RELEASE_ASSERT(variable->index() == variableToStack.size());
        variableToStack.append(stack);
        stackToVariable.add(stack, variable);
    }

    // Create Defs for all of the stores to the stack variable.
    for (BasicBlock* block : proc) {
        for (Value* value : *block) {
            if (value->opcode() != Store)
                continue;

            StackSlotValue* stack = value->child(1)->as<StackSlotValue>();
            if (!stack)
                continue;

            if (SSACalculator::Variable* variable = stackToVariable.get(stack))
                ssa.newDef(variable, block, value->child(0));
        }
    }

    // Decide where Phis are to be inserted. This creates them but does not insert them.
    ssa.computePhis(
        [&] (SSACalculator::Variable* variable, BasicBlock* block) -> Value* {
            StackSlotValue* stack = variableToStack[variable->index()];
            Value* phi = proc.add<Value>(Phi, stackVariable.get(stack), stack->origin());
            if (verbose) {
                dataLog(
                    "Adding Phi for ", pointerDump(stack), " at ", *block, ": ",
                    deepDump(proc, phi), "\n");
            }
            return phi;
        });

    // Now perform the conversion.
    InsertionSet insertionSet(proc);
    HashMap<StackSlotValue*, Value*> mapping;
    for (BasicBlock* block : proc.blocksInPreOrder()) {
        mapping.clear();

        for (auto& entry : stackToVariable) {
            StackSlotValue* stack = entry.key;
            SSACalculator::Variable* variable = entry.value;

            SSACalculator::Def* def = ssa.reachingDefAtHead(block, variable);
            if (def)
                mapping.set(stack, def->value());
        }

        for (SSACalculator::Def* phiDef : ssa.phisForBlock(block)) {
            StackSlotValue* stack = variableToStack[phiDef->variable()->index()];

            insertionSet.insertValue(0, phiDef->value());
            mapping.set(stack, phiDef->value());
        }

        for (unsigned valueIndex = 0; valueIndex < block->size(); ++valueIndex) {
            Value* value = block->at(valueIndex);
            value->performSubstitution();

            switch (value->opcode()) {
            case Load: {
                if (StackSlotValue* stack = value->child(0)->as<StackSlotValue>()) {
                    if (Value* replacement = mapping.get(stack))
                        value->replaceWithIdentity(replacement);
                }
                break;
            }
                
            case Store: {
                if (StackSlotValue* stack = value->child(1)->as<StackSlotValue>()) {
                    if (stackToVariable.contains(stack)) {
                        mapping.set(stack, value->child(0));
                        value->replaceWithNop();
                    }
                }
                break;
            }

            default:
                break;
            }
        }

        unsigned upsilonInsertionPoint = block->size() - 1;
        Origin upsilonOrigin = block->last()->origin();
        for (BasicBlock* successorBlock : block->successorBlocks()) {
            for (SSACalculator::Def* phiDef : ssa.phisForBlock(successorBlock)) {
                Value* phi = phiDef->value();
                SSACalculator::Variable* variable = phiDef->variable();
                StackSlotValue* stack = variableToStack[variable->index()];

                Value* mappedValue = mapping.get(stack);
                if (verbose) {
                    dataLog(
                        "Mapped value for ", *stack, " with successor Phi ", *phi, " at end of ",
                        *block, ": ", pointerDump(mappedValue), "\n");
                }
                
                if (!mappedValue)
                    mappedValue = insertionSet.insertBottom(upsilonInsertionPoint, phi);
                
                insertionSet.insert<UpsilonValue>(
                    upsilonInsertionPoint, upsilonOrigin, mappedValue, phi);
            }
        }

        insertionSet.execute(block);
    }

    // Finally, kill the stack slots.
    for (StackSlotValue* stack : variableToStack)
        stack->replaceWithNop();

    if (verbose) {
        dataLog("B3 after SSA conversion:\n");
        dataLog(proc);
    }

    return true;
}