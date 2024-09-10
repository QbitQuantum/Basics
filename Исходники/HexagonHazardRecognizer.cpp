ScheduleHazardRecognizer::HazardType
HexagonHazardRecognizer::getHazardType(SUnit *SU, int stalls) {
  MachineInstr *MI = SU->getInstr();
  if (!MI || TII->isZeroCost(MI->getOpcode()))
    return NoHazard;

  if (!Resources->canReserveResources(*MI)) {
    DEBUG(dbgs() << "*** Hazard in cycle " << PacketNum << ", " << *MI);
    HazardType RetVal = Hazard;
    if (TII->mayBeNewStore(*MI)) {
      // Make sure the register to be stored is defined by an instruction in the
      // packet.
      MachineOperand &MO = MI->getOperand(MI->getNumOperands() - 1);
      if (!MO.isReg() || RegDefs.count(MO.getReg()) == 0)
        return Hazard;
      // The .new store version uses different resources so check if it
      // causes a hazard.
      MachineFunction *MF = MI->getParent()->getParent();
      MachineInstr *NewMI =
        MF->CreateMachineInstr(TII->get(TII->getDotNewOp(*MI)),
                               MI->getDebugLoc());
      if (Resources->canReserveResources(*NewMI))
        RetVal = NoHazard;
      DEBUG(dbgs() << "*** Try .new version? " << (RetVal == NoHazard) << "\n");
      MF->DeleteMachineInstr(NewMI);
    }
    return RetVal;
  }

  if (SU == UsesDotCur && DotCurPNum != (int)PacketNum) {
    DEBUG(dbgs() << "*** .cur Hazard in cycle " << PacketNum << ", " << *MI);
    return Hazard;
  }

  return NoHazard;
}