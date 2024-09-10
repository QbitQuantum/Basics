void LinearScan::rematerializeAux(Trace* trace,
                                  SSATmp* curSp,
                                  SSATmp* curFp,
                                  std::vector<SSATmp*> localValues) {
  IRInstruction::List& instList = trace->getInstructionList();
  for (IRInstruction::Iterator it = instList.begin();
       it != instList.end();
       ++it) {
    IRInstruction* inst = *it;
    Opcode opc = inst->getOpcode();
    SSATmp* dst = inst->getDst();
    if (opc == DefFP || opc == FreeActRec) {
      curFp = dst;
      assert(dst && dst->getReg() == rVmFp);
    }
    if (opc == Reload) {
      // s = Spill t0
      // t = Reload s
      SSATmp* spilledTmp = getSpilledTmp(dst);
      IRInstruction* spilledInst = spilledTmp->getInstruction();
      IRInstruction* newInst = NULL;
      if (spilledInst->isRematerializable() ||
          (spilledInst->getOpcode() == LdStack &&
           spilledInst->getSrc(0) == curSp)) {
        // XXX: could change <newInst> to the non-check version.
        // Rematerialize those rematerializable instructions (i.e.,
        // isRematerializable returns true) and LdStack.
        newInst = spilledInst->clone(m_irFactory);
        // The new instruction needn't have an exit label, because it is always
        // dominated by the original instruction.
        newInst->setLabel(NULL);
      } else {
        // Rematerialize LdLoc.
        std::vector<SSATmp*>::iterator pos =
          std::find(localValues.begin(),
                    localValues.end(),
                    canonicalize(spilledTmp));
        // Search for a local that stores the value of <spilledTmp>.
        if (pos != localValues.end()) {
          size_t locId = pos - localValues.begin();
          assert(curFp != NULL);
          ConstInstruction constInst(curFp, Local(locId));
          IRInstruction* ldHomeInst =
            m_irFactory->cloneInstruction(&constInst);
          newInst = m_irFactory->gen(LdLoc,
                                     dst->getType(),
                                     m_irFactory->getSSATmp(ldHomeInst));
        }
      }
      if (newInst) {
        UNUSED Type::Tag oldType = dst->getType();
        newInst->setDst(dst);
        dst->setInstruction(newInst);
        assert(outputType(newInst) == oldType);
        *it = newInst;
        newInst->setParent(trace);
      }
    }

    // Updating <curSp> and <localValues>.
    if (dst && dst->getReg() == rVmSp) {
      // <inst> modifies the stack pointer.
      curSp = dst;
    }
    if (opc == LdLoc || opc == StLoc || opc == StLocNT) {
      // dst = LdLoc home
      // StLoc/StLocNT home, src
      int locId = getLocalIdFromHomeOpnd(inst->getSrc(0));
      // Note that when we implement inlining, we will need to deal
      // with the new local id space of the inlined function.
      SSATmp* localValue = (opc == LdLoc ? dst : inst->getSrc(1));
      if (int(localValues.size()) < locId + 1) {
        localValues.resize(locId + 1);
      }
      localValues[locId] = canonicalize(localValue);
    }
    // Other instructions that may have side effects on locals must
    // kill the local variable values.
    else if (opc == IterInit) {
      int valLocId = inst->getSrc(3)->getConstValAsInt();
      localValues[valLocId] = NULL;
      if (inst->getNumSrcs() == 5) {
        int keyLocId = inst->getSrc(4)->getConstValAsInt();
        localValues[keyLocId] = NULL;
      }
    } else if (opc == IterNext) {
      int valLocId = inst->getSrc(2)->getConstValAsInt();
      localValues[valLocId] = NULL;
      if (inst->getNumSrcs() == 4) {
        int keyLocId = inst->getSrc(3)->getConstValAsInt();
        localValues[keyLocId] = NULL;
      }
    }

    if (inst->isControlFlowInstruction()) {
      LabelInstruction* label = inst->getLabel();
      if (label != NULL && label->getId() == inst->getId() + 1) {
        rematerializeAux(label->getParent(), curSp, curFp, localValues);
      }
    }
  }
}