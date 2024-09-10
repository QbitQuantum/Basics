PeepHoleOpt::Changed PeepHoleOpt::handleInst_MOV(Inst* inst)
{
    Node* node = inst->getNode();
    if (((BasicBlock*)node)->getLayoutSucc() == NULL)
    {
        Inst *next = inst->getNextInst();

        Node *currNode = node;
        bool methodMarkerOccur = false;
        MethodMarkerPseudoInst* methodMarker = NULL;
        // ignoring instructions that have no effect and saving method markers to correct them during optimizations
        while (next == NULL || next->getKind() == Inst::Kind_MethodEndPseudoInst || next->getMnemonic() == Mnemonic_JMP)
        {
            if (next == NULL)
            {
                currNode = currNode->getOutEdge(Edge::Kind_Unconditional)->getTargetNode();
                if (currNode->getKind() == Node::Kind_Exit)
                    return Changed_Nothing;
                next = (Inst*) currNode->getFirstInst();
            }
            else
            {
                if (next->getKind() == Inst::Kind_MethodEndPseudoInst)
                {
                    //max 1 saved method marker
                    if (methodMarkerOccur)
                    {
                        return Changed_Nothing;
                    }
                    methodMarker = (MethodMarkerPseudoInst*)next;
                    methodMarkerOccur = true;
                }
                next = next->getNextInst();
            }
        }

        Inst *jump = next->getNextInst();


        bool step1 = true;
        currNode = node;
        while (currNode != next->getNode())
        {
            currNode = currNode->getOutEdge(Edge::Kind_Unconditional)->getTargetNode();
            if (currNode->getInDegree()!=1)
            {
                step1 = false;
                break;
            }
        }

        // step1:
        // ---------------------------------------------
        // MOV opnd, opnd2             MOV opnd3, opnd2
        // MOV opnd3, opnd      ->
        // ---------------------------------------------
        // nb: applicable if opnd will not be used further
        if (step1 && next->getMnemonic() == Mnemonic_MOV)
        {
            Opnd *movopnd1, *movopnd2, *nextmovopnd1, *nextmovopnd2;
            bool isInstCopyPseudo = (inst->getKind() == Inst::Kind_CopyPseudoInst);
            if (isInstCopyPseudo)
            {
                movopnd1 = inst->getOpnd(0);
                movopnd2 = inst->getOpnd(1);
            }
            else
            {
                Inst::Opnds movuses(inst, Inst::OpndRole_Explicit|Inst::OpndRole_Use);
                Inst::Opnds movdefs(inst, Inst::OpndRole_Explicit|Inst::OpndRole_Def);
                movopnd1 = inst->getOpnd(movdefs.begin());
                movopnd2 = inst->getOpnd(movuses.begin());
            }
            bool isNextCopyPseudo = (next->getKind() == Inst::Kind_CopyPseudoInst);
            if (isNextCopyPseudo)
            {
                nextmovopnd1 = next->getOpnd(0);
                nextmovopnd2 = next->getOpnd(1);
            }
            else
            {
                Inst::Opnds nextmovuses(next, Inst::OpndRole_Explicit|Inst::OpndRole_Use);
                Inst::Opnds nextmovdefs(next, Inst::OpndRole_Explicit|Inst::OpndRole_Def);
                nextmovopnd1 = next->getOpnd(nextmovdefs.begin());
                nextmovopnd2 = next->getOpnd(nextmovuses.begin());
            }
            if (movopnd1->getId() == nextmovopnd2->getId() && 
                !isMem(movopnd2) && !isMem(nextmovopnd1) &&
                !isMem(movopnd1)
                )
            {
                BitSet ls(irManager->getMemoryManager(), irManager->getOpndCount());
                irManager->updateLivenessInfo();
                irManager->getLiveAtExit(next->getNode(), ls);
                for (Inst* i = (Inst*)next->getNode()->getLastInst(); i!=next; i = i->getPrevInst()) {
                    irManager->updateLiveness(i, ls);
                }
                bool dstNotUsed = !ls.getBit(movopnd1->getId());
                if (dstNotUsed)
                {
                    if (isInstCopyPseudo && isNextCopyPseudo)
                        irManager->newCopyPseudoInst(Mnemonic_MOV, nextmovopnd1, movopnd2)->insertAfter(inst);
                    else
                        irManager->newInst(Mnemonic_MOV, nextmovopnd1, movopnd2)->insertAfter(inst);
                    inst->unlink();
                    next->unlink();
                    return Changed_Node;
                }
            }
        }

        // step2:
        // --------------------------------------------------------------
        // MOV opnd, 0/1                Jmp smwh/BB1            Jmp smwh/BB1
        // CMP opnd, 0           ->     CMP opnd, 0     v
        // Jcc smwh                     Jcc smwh
        // BB1:                         BB1:
        // --------------------------------------------------------------
        // nb: applicable if opnd will not be used further
        if (next->getMnemonic() == Mnemonic_CMP && jump!= NULL && (jump->getMnemonic() == Mnemonic_JE ||
            jump->getMnemonic() == Mnemonic_JNE))
        {
            Opnd *movopnd1, *movopnd2;
            if (inst->getKind() == Inst::Kind_CopyPseudoInst)
            {
                movopnd1 = inst->getOpnd(0);
                movopnd2 = inst->getOpnd(1);
            }
            else
            {
                Inst::Opnds movuses(inst, Inst::OpndRole_Explicit|Inst::OpndRole_Use);
                Inst::Opnds movdefs(inst, Inst::OpndRole_Explicit|Inst::OpndRole_Def);
                movopnd1 = inst->getOpnd(movdefs.begin());
                movopnd2 = inst->getOpnd(movuses.begin());
            }
            Inst::Opnds cmpuses(next, Inst::OpndRole_Explicit|Inst::OpndRole_Use);
            Opnd* cmpopnd1 = next->getOpnd(cmpuses.begin());
            Opnd* cmpopnd2 = next->getOpnd(cmpuses.next(cmpuses.begin()));
            
            if (isImm(movopnd2) && (movopnd2->getImmValue() == 0 || movopnd2->getImmValue() == 1) &&
                movopnd1->getId() == cmpopnd1->getId() &&
                isImm(cmpopnd2) && cmpopnd2->getImmValue() == 0)
            {
                BitSet ls(irManager->getMemoryManager(), irManager->getOpndCount());
                irManager->updateLivenessInfo();
                irManager->getLiveAtExit(jump->getNode(), ls);
                bool opndNotUsed = !ls.getBit(movopnd1->getId());
                if (opndNotUsed)
                {
                    ControlFlowGraph* cfg = irManager->getFlowGraph();
                    Node* destination = ((BranchInst*)jump)->getTrueTarget();
                    if ((jump->getMnemonic() == Mnemonic_JNE || movopnd2->getImmValue() == 1) && !(jump->getMnemonic() == Mnemonic_JNE && movopnd2->getImmValue() == 1))
                    {
                        destination = ((BranchInst*)jump)->getFalseTarget();
                    }
                    if (node->getId() != next->getNode()->getId())
                    {
                        if (methodMarkerOccur)
                        {
                            inst->getNode()->appendInst(irManager->newMethodEndPseudoInst(methodMarker->getMethodDesc()));
                        }
                        inst->unlink();
                        Edge *outEdge = node->getOutEdge(Edge::Kind_Unconditional);
                        cfg->replaceEdgeTarget(outEdge, destination, true);
                        cfg->purgeUnreachableNodes(); // previous successor may become unreachable
                    }
                    else
                    {
                        cfg->removeEdge(node->getOutEdge(Edge::Kind_True));
                        cfg->removeEdge(node->getOutEdge(Edge::Kind_False));
                        cfg->addEdge(node, destination);
                        inst->unlink();
                        next->unlink();
                        jump->unlink();
                    }

                    return Changed_Node;
                }
            }
        }
    }
    return Changed_Nothing;
}