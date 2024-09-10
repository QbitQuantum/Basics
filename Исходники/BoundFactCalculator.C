void BoundFactsCalculator::CalcTransferFunction(Node::Ptr curNode, BoundFact *newFact){
    SliceNode::Ptr node = boost::static_pointer_cast<SliceNode>(curNode);
    if (!node->assign()) return;
    if (node->assign() && node->assign()->out().absloc().type() == Absloc::Register &&
	    (node->assign()->out().absloc().reg() == x86::zf || node->assign()->out().absloc().reg() == x86_64::zf)) {
	    // zf should be only predecessor of this node
        parsing_printf("\t\tThe predecessor node is zf assignment!\n");
	newFact->SetPredicate(node->assign(), ExpandAssignment(node->assign()) );
	return;
    }
    entryID id = node->assign()->insn()->getOperation().getID();
    // The predecessor is not a conditional jump,
    // then we can determine buond fact based on the src assignment
    parsing_printf("\t\tThe predecessor node is normal node\n");
    parsing_printf("\t\t\tentry id %d\n", id);

    AbsRegion &ar = node->assign()->out();
    Instruction::Ptr insn = node->assign()->insn();
    pair<AST::Ptr, bool> expandRet = ExpandAssignment(node->assign());

    if (expandRet.first == NULL) {
        parsing_printf("\t\t\t No semantic support for this instruction. Assume it does not affect jump target calculation. Ignore it (Treat as identity function) except for ptest. ptest should kill the current predicate\n");
	if (id == e_ptest) {
	    parsing_printf("\t\t\t\tptest instruction, kill predciate.\n");
	    newFact->pred.valid = false;
	}
	return;
    } else {
        parsing_printf("\tAST: %s\n", expandRet.first->format().c_str());
    }

    AST::Ptr calculation = expandRet.first;
    BoundCalcVisitor bcv(*newFact, node->block(), handleOneByteRead);
    calculation->accept(&bcv);
    AST::Ptr outAST;
    // If the instruction writes memory,
    // we need the AST that represents the memory access and the address.
    // When the AbsRegion represents memory,
    // the generator of the AbsRegion is set to be the AST that represents
    // the memory address during symbolic expansion.
    // In other cases, if the AbsRegion represents a register,
    // the generator is not set.
    if (ar.generator() != NULL)
        outAST = SimplifyAnAST(RoseAST::create(ROSEOperation(ROSEOperation::derefOp, ar.size()), ar.generator()), node->assign()->insn()->size());
    else
        outAST = VariableAST::create(Variable(ar));
/*
 * Naively, bsf and bsr produces a bound from 0 to the number of bits of the source operands.
 * In pratice, especially in libc, the real bound is usually smaller than the size of the source operand.
 * Ex 1: shl    %cl,%edx
 *       bsf    %rdx,%rcx
 * Here rcx is in range [0,31] rather than [0,63] even though rdx has 64 bits.
 *
 * Ex 2: pmovmskb %xmm0,%edx
 *       bsf    %rdx, %rdx
 * Here rdx is in range[0,15] because pmovmskb only sets the least significat 16 bits
 * In addition, overapproximation of the bound can lead to bogus control flow
 * that causes overlapping blocks or function.
 * It is important to further anaylze the operand in bsf rather than directly conclude the bound
    if (id == e_bsf || id == e_bsr) {
	int size = node->assign()->insn()->getOperand(0).getValue()->size();
	newFact->GenFact(outAST, new BoundValue(StridedInterval(1,0, size * 8 - 1)), false);
        parsing_printf("\t\t\tCalculating transfer function: Output facts\n");
	newFact->Print();
	return;

    }
*/
    if (id == e_xchg) {
        newFact->SwapFact(calculation, outAST);
        parsing_printf("\t\t\tCalculating transfer function: Output facts\n");
	newFact->Print();
	return;
    }

    if (id == e_push) {
         if (calculation->getID() == AST::V_ConstantAST) {
	     ConstantAST::Ptr c = boost::static_pointer_cast<ConstantAST>(calculation);
	     newFact->PushAConst(c->val().val);
	     parsing_printf("\t\t\tCalculating transfer function: Output facts\n");
	     newFact->Print();
	     return;
	 }
    }

    if (id == e_pop) {
        if (newFact->PopAConst(outAST)) {
	     parsing_printf("\t\t\tCalculating transfer function: Output facts\n");
	     newFact->Print();
	     return;
        }
    }

    // Assume all SETxx entry ids are contiguous
    if (id >= e_setb && id <= e_setz) {
        newFact->GenFact(outAST, new BoundValue(StridedInterval(1,0,1)), false);
	parsing_printf("\t\t\tCalculating transfer function: Output facts\n");
	newFact->Print();
	return;
    }


    if (bcv.IsResultBounded(calculation)) {
        parsing_printf("\t\t\tGenerate bound fact for %s\n", outAST->format().c_str());
	newFact->GenFact(outAST, new BoundValue(*bcv.GetResultBound(calculation)), false);
    }
    else {
        parsing_printf("\t\t\tKill bound fact for %s\n", outAST->format().c_str());
	newFact->KillFact(outAST, false);
    }
    if (calculation->getID() == AST::V_VariableAST) {
        // We only track alising between registers
	parsing_printf("\t\t\t%s and %s are equal\n", calculation->format().c_str(), outAST->format().c_str());
	newFact->InsertRelation(calculation, outAST, BoundFact::Equal);
    }
    newFact->AdjustPredicate(outAST, calculation);

    // Now try to track all aliasing.
    // Currently, all variables in the slice are presented as an AST
    // consists of input variables to the slice (the variables that
    // we do not the sources of their values).
    newFact->TrackAlias(DeepCopyAnAST(calculation), outAST);

    // Apply tracking relations to the calculation to generate a
    // potentially stricter bound
    BoundValue *strictValue = newFact->ApplyRelations(outAST);
    if (strictValue != NULL) {
        parsing_printf("\t\t\tGenerate stricter bound fact for %s\n", outAST->format().c_str());
	newFact->GenFact(outAST, strictValue, false);
    }
    parsing_printf("\t\t\tCalculating transfer function: Output facts\n");
    newFact->Print();

}