void eliminateDeadCode(Trace* trace, IRFactory* irFactory) {
  IRInstruction::List wl; // worklist of live instructions
  Trace::List& exitTraces = trace->getExitTraces();
  // first mark all exit traces as unreachable by setting the id on
  // their labels to 0
  for (Trace::Iterator it = exitTraces.begin();
       it != exitTraces.end();
       it++) {
    Trace* trace = *it;
    trace->getLabel()->setId(DEAD);
  }

  // mark the essential instructions and add them to the initial
  // work list; also mark the exit traces that are reachable by
  // any control flow instruction in the main trace.
  initInstructions(trace, wl);
  for (Trace::Iterator it = exitTraces.begin();
       it != exitTraces.end();
       it++) {
    // only process those exit traces that are reachable from
    // the main trace
    Trace* trace = *it;
    if (trace->getLabel()->getId() != DEAD) {
      initInstructions(trace, wl);
    }
  }

  // process the worklist
  while (!wl.empty()) {
    IRInstruction* inst = wl.front();
    wl.pop_front();
    for (uint32 i = 0; i < inst->getNumSrcs(); i++) {
      SSATmp* src = inst->getSrc(i);
      if (src->getInstruction()->isDefConst()) {
        continue;
      }
      IRInstruction* srcInst = src->getInstruction();
      if (srcInst->getId() == DEAD) {
        srcInst->setId(LIVE);
        wl.push_back(srcInst);
      }
      // <inst> consumes <srcInst> which is an IncRef,
      // so we mark <srcInst> as REFCOUNT_CONSUMED.
      if (inst->consumesReference(i) && srcInst->getOpcode() == IncRef) {
        if (inst->getParent()->isMain() || !srcInst->getParent()->isMain()) {
          // <srcInst> is consumed from its own trace.
          srcInst->setId(REFCOUNT_CONSUMED);
        } else {
          // <srcInst> is consumed off trace.
          if (srcInst->getId() != REFCOUNT_CONSUMED) {
            // mark <srcInst> as REFCOUNT_CONSUMED_OFF_TRACE unless it is
            // also consumed from its own trace.
            srcInst->setId(REFCOUNT_CONSUMED_OFF_TRACE);
          }
        }
      }
    }
  }

  // Optimize IncRefs and DecRefs.
  optimizeRefCount(trace);
  for (Trace::Iterator it = exitTraces.begin(); it != exitTraces.end(); ++it) {
    optimizeRefCount(*it);
  }

  if (RuntimeOption::EvalHHIREnableSinking) {
    // Sink IncRefs consumed off trace.
    IRInstruction::List toSink;
    sinkIncRefs(trace, irFactory, toSink);
  }

  // now remove instructions whose id == DEAD
  removeDeadInstructions(trace);
  for (Trace::Iterator it = exitTraces.begin(); it != exitTraces.end(); it++) {
    removeDeadInstructions(*it);
  }

  // If main trace ends with an unconditional jump, copy the target of
  // the jump to the end of the trace
  IRInstruction::List& instList = trace->getInstructionList();
  IRInstruction::Iterator lastInst = instList.end();
  lastInst--; // go back to the last instruction
  IRInstruction* jmpInst = *lastInst;
  if (jmpInst->getOpcode() == Jmp_) {
    Trace* targetTrace = jmpInst->getLabel()->getParent();
    IRInstruction::List& targetInstList = targetTrace->getInstructionList();
    IRInstruction::Iterator instIter = targetInstList.begin();
    instIter++; // skip over label
    // update the parent trace of the moved instructions
    for (IRInstruction::Iterator it = instIter;
         it != targetInstList.end();
         ++it) {
      (*it)->setParent(trace);
    }
    instList.splice(lastInst, targetInstList, instIter, targetInstList.end());
    // delete the jump instruction
    instList.erase(lastInst);
  }

  // If main trace ends with a conditional jump with no side-effects on exit,
  // hook it to the exitTrace and make it a TraceExitType::NormalCc
  if (RuntimeOption::EvalHHIRDirectExit) {
    IRInstruction::List& instList = trace->getInstructionList();
    IRInstruction::Iterator tail  = instList.end();
    IRInstruction* jccInst        = NULL;
    IRInstruction* exitInst       = NULL;
    IRInstruction* exitCcInst     = NULL;
    Opcode opc = OpAdd;
    // Normally Jcc comes before a Marker
    for (int idx = 3; idx >= 0; idx--) {
      tail--; // go back to the previous instruction
      IRInstruction* inst = *tail;
      opc = inst->getOpcode();
      if (opc == ExitTrace) {
        exitInst = *tail;
        continue;
      }
      if (opc == Marker) {
        continue;
      }
      if (jccCanBeDirectExit(opc)) {
        jccInst = inst;
        break;
      }
      break;
    }
    if (jccCanBeDirectExit(opc)) {
      SSATmp* dst = jccInst->getDst();
      Trace* targetTrace = jccInst->getLabel()->getParent();
      IRInstruction::List& targetInstList = targetTrace->getInstructionList();
      IRInstruction::Iterator targetInstIter = targetInstList.begin();
      targetInstIter++; // skip over label

      // Check for a NormalCc exit with no side effects
      for (IRInstruction::Iterator it = targetInstIter;
           it != targetInstList.end();
           ++it) {
        IRInstruction* instr = (*it);
        // Extend to support ExitSlow, ExitSlowNoProgress, ...
        Opcode opc = instr->getOpcode();
        if (opc == ExitTraceCc) {
          exitCcInst = instr;
          break;
        } else if (opc == Marker) {
          continue;
        } else {
          // Do not optimize if there are other instructions
          break;
        }
      }

      if (exitInst && exitCcInst) {
        // Found both exits, link them to Jcc for codegen
        assert(dst);
        exitCcInst->appendSrc(*irFactory, dst);
        exitInst->appendSrc(*irFactory, dst);
        // Set flag so Jcc and exits know this is active
        dst->setTCA(kIRDirectJccJmpActive);
      }
    }
  }

  // If main trace starts with guards, have them generate a patchable jump
  // to the anchor trace
  if (RuntimeOption::EvalHHIRDirectExit) {
    LabelInstruction* guardLabel = NULL;
    IRInstruction::List& instList = trace->getInstructionList();
    // Check the beginning of the trace for guards
    for (IRInstruction::Iterator it = instList.begin(); it != instList.end();
         ++it) {
      IRInstruction* inst = *it;
      Opcode opc = inst->getOpcode();
      if (inst->getLabel() &&
          (opc == LdLoc    || opc == LdStack ||
           opc == GuardLoc || opc == GuardStk)) {
        LabelInstruction* exitLabel = inst->getLabel();
        // Find the GuardFailure's label and confirm this branches there
        if (guardLabel == NULL) {
          Trace* exitTrace = exitLabel->getParent();
          IRInstruction::List& xList = exitTrace->getInstructionList();
          IRInstruction::Iterator instIter = xList.begin();
          instIter++; // skip over label
          // Confirm this is a GuardExit
          for (IRInstruction::Iterator it = instIter; it != xList.end(); ++it) {
            IRInstruction* i = *it;
            Opcode op = i->getOpcode();
            if (op == Marker) {
              continue;
            }
            if (op == ExitGuardFailure) {
              guardLabel = exitLabel;
            }
            // Do not optimize if other instructions are on exit trace
            break;
          }
        }
        if (exitLabel == guardLabel) {
          inst->setTCA(kIRDirectGuardActive);
          continue;
        }
        break;
      }
      if (opc == Marker || opc == DefLabel || opc == DefSP || opc == DefFP ||
          opc == LdStack) {
        continue;
      }
      break;
    }
  }
}