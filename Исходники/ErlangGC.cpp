bool ErlangGC::findCustomSafePoints(GCFunctionInfo &FI, MachineFunction &MF) {
  for (MachineFunction::iterator BBI = MF.begin(), BBE = MF.end(); BBI != BBE;
       ++BBI)
    for (MachineBasicBlock::iterator MI = BBI->begin(), ME = BBI->end();
         MI != ME; ++MI)

      if (MI->getDesc().isCall()) {

        // Do not treat tail call sites as safe points.
        if (MI->getDesc().isTerminator())
          continue;

        /* Code copied from VisitCallPoint(...) */
        MachineBasicBlock::iterator RAI = MI; ++RAI;
        MCSymbol* Label = InsertLabel(*MI->getParent(), RAI, MI->getDebugLoc());
        FI.addSafePoint(GC::PostCall, Label, MI->getDebugLoc());
      }

  return false;
}