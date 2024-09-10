//___________________________________________________________________________________________________
void EarlyPropagation::runImpl()
{ 
        irManager->updateLoopInfo();
        U_32 opndCount=irManager->getOpndCount();

        MemoryManager mm("early_prop");
        OpndInfo * opndInfos = new(mm) OpndInfo[opndCount];
        Node * currentLoopHeader = NULL;

        bool anyInstHandled=false;

        LoopTree* lt = irManager->getFlowGraph()->getLoopTree();
        const Nodes& postOrdered = irManager->getFlowGraph()->getNodesPostOrder();
        for (Nodes::const_reverse_iterator it = postOrdered.rbegin(), end = postOrdered.rend(); it!=end; ++it) {
            Node * node=*it;
            if (!node->isBlockNode())  {
                continue;
            }
            Node * loopHeader = lt->getLoopHeader(node, false);
            if (currentLoopHeader != loopHeader){
                currentLoopHeader = loopHeader;
                for (U_32 i = 0; i < opndCount; ++i)
                    if (opndInfos[i].sourceOpndId != EmptyUint32)
                        opndInfos[i].defCount++;
            }

            for (Inst * inst = (Inst*)node->getFirstInst(); inst != NULL; inst=inst->getNextInst()){
                bool assignedOpndPropagated = false;
                Inst::Opnds opnds(inst, Inst::OpndRole_All);
                for (Inst::Opnds::iterator it = opnds.begin(); it != opnds.end(); it = opnds.next(it)){
                    Opnd * opnd=inst->getOpnd(it);
                    U_32 roles=inst->getOpndRoles(it);
                    U_32 opndId = opnd->getId();
                    OpndInfo& opndInfo = opndInfos[opndId];

                    U_32 mask = 0;

                    if (roles & Inst::OpndRole_Def){
                        ++opndInfo.defCount;
                    }else if (roles & Inst::OpndRole_Use){
                        if (opndInfo.sourceOpndId != EmptyUint32){
                            if (opndInfo.sourceOpndDefCountAtCopy < opndInfos[opndInfo.sourceOpndId].defCount)
                                opndInfo.sourceOpndId = EmptyUint32;
                            else{
                                Opnd * srcOpnd = irManager->getOpnd(opndInfo.sourceOpndId);
                                Constraint co = srcOpnd->getConstraint(Opnd::ConstraintKind_Location);
                                if (co.getKind() == OpndKind_Mem){
                                    mask = (1<<it)-1;
                                    if ((roles & Inst::OpndRole_Explicit) == 0 ||
                                        inst->hasKind(Inst::Kind_PseudoInst) || irManager->isGCSafePoint(inst) ||
                                        opndInfo.sourceInst != inst->getPrevInst() || assignedOpndPropagated ||
                                    (inst->getConstraint(it, mask, co.getSize())&co).isNull()
                                    )
                                        opndInfo.sourceOpndId = EmptyUint32;
                                    assignedOpndPropagated = true;
                                }
                            }
                        }
                    }
                    if (opndInfo.defCount > 1){
                        opndInfo.sourceOpndId = EmptyUint32;
                    }
                }
                /*
                Here is the previous version to test whether the inst is copy or not.
                bool isCopy = inst->getMnemonic() == Mnemonic_MOV ||(
                        (inst->getMnemonic() == Mnemonic_ADD || inst->getMnemonic() == Mnemonic_SUB) && 
                        inst->getOpnd(3)->isPlacedIn(OpndKind_Imm) && inst->getOpnd(3)->getImmValue()==0
                        && inst->getOpnd(3)->getRuntimeInfo()==NULL
                    );
                It considered special case of 'dst = src +/- 0' as copy. 
                In fact there are more similar cases like 'IMUL src, 1 ; shift src, 0' etc.
                Such checks are obsolete now, Should as peephole takes care about such copies.

                Anyway, the code above had a bug: 'inst->getOpnd(3)' crashes in instructions 
                in native form (like ADD def_use, use).
                */
                const bool isCopy = inst->getMnemonic() == Mnemonic_MOV;

                if (isCopy){ // CopyPseudoInst or mov
                    Opnd * defOpnd = inst->getOpnd(0);
                    Opnd * srcOpnd = inst->getOpnd(1);
                    U_32 defOpndId = defOpnd->getId();
                    OpndInfo * opndInfo = opndInfos + defOpndId;
                    bool instHandled=false;
                    bool typeConvOk = isTypeConversionAllowed(srcOpnd, defOpnd);
                    if (typeConvOk && opndInfo->defCount == 1 && ! srcOpnd->isPlacedIn(OpndKind_Reg)){
                        if (!defOpnd->hasAssignedPhysicalLocation()){
                            opndInfo->sourceInst = inst;
                            opndInfo->sourceOpndId = srcOpnd->getId();
                            instHandled=true;
                        }
                    }
                    if (instHandled){
                        if (opndInfos[opndInfo->sourceOpndId].sourceOpndId != EmptyUint32)
                            opndInfo->sourceOpndId = opndInfos[opndInfo->sourceOpndId].sourceOpndId;
                        opndInfo->sourceOpndDefCountAtCopy = opndInfos[opndInfo->sourceOpndId].defCount;
                        anyInstHandled=true;
                    }
                }
            }
        }

        if (anyInstHandled){
            Opnd ** replacements = new(mm) Opnd* [opndCount];
            memset(replacements, 0, sizeof(Opnd*) * opndCount);
            bool hasReplacements = false;
            for (U_32 i = 0; i < opndCount; ++i){
                if (opndInfos[i].sourceOpndId != EmptyUint32){
                    Inst * inst = opndInfos[i].sourceInst;
                    if (inst !=NULL){
                        inst->unlink();
                    }
                    if (opndInfos[i].sourceOpndId != i){
                        Opnd* origOpnd= irManager->getOpnd(i);
                        Opnd* replacementOpnd = irManager->getOpnd(opndInfos[i].sourceOpndId);
                        assert(isTypeConversionAllowed(replacementOpnd, origOpnd));
                        if (origOpnd->getType()->isUnmanagedPtr() && replacementOpnd->getType()->isInteger()) {
                            replacementOpnd->setType(origOpnd->getType());
                        }/* else if (origOpnd->getType()->isObject() && replacementOpnd->getType()->isUnmanagedPtr()) {
                            replacementOpnd->setType(origOpnd->getType());
                        }*/
                        replacements[i] = replacementOpnd;
                        hasReplacements = true;
                    }
                }
            }

            if (hasReplacements){
                const Nodes& postOrdered = irManager->getFlowGraph()->getNodesPostOrder();
                for (Nodes::const_reverse_iterator it = postOrdered.rbegin(), end = postOrdered.rend(); it!=end; ++it) {
                    Node * node=*it;
                    if (!node->isBlockNode())  {
                        continue;
                    }
                    for (Inst * inst = (Inst*)node->getFirstInst(); inst != NULL; inst=inst->getNextInst()){
                        inst->replaceOpnds(replacements);
                    }   
                }
            }
        }
}