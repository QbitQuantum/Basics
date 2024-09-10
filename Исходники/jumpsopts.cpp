// If main trace starts with guards, have them generate a patchable jump
// to the anchor trace
static void hoistGuardJumps(Trace* trace, IRFactory* irFactory) {
  LabelInstruction* guardLabel = nullptr;
  IRInstruction::List& instList = trace->getInstructionList();
  // Check the beginning of the trace for guards
  for (IRInstruction* inst : instList) {
    Opcode opc = inst->getOpcode();
    if (inst->getLabel() &&
        (opc == LdLoc    || opc == LdStack ||
         opc == GuardLoc || opc == GuardStk)) {
      LabelInstruction* exitLabel = inst->getLabel();
      // Find the GuardFailure's label and confirm this branches there
      if (!guardLabel && exitLabel->getParent() != trace) {
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