void ARMFrameLowering::emitPopInst(MachineBasicBlock &MBB,
                                   MachineBasicBlock::iterator MI,
                                   const std::vector<CalleeSavedInfo> &CSI,
                                   unsigned LdmOpc, unsigned LdrOpc,
                                   bool isVarArg, bool NoGap,
                                   bool(*Func)(unsigned, bool)) const {
  MachineFunction &MF = *MBB.getParent();
  const TargetInstrInfo &TII = *MF.getTarget().getInstrInfo();
  ARMFunctionInfo *AFI = MF.getInfo<ARMFunctionInfo>();
  DebugLoc DL = MI->getDebugLoc();
  unsigned RetOpcode = MI->getOpcode();
  bool isTailCall = (RetOpcode == ARM::TCRETURNdi ||
                     RetOpcode == ARM::TCRETURNdiND ||
                     RetOpcode == ARM::TCRETURNri ||
                     RetOpcode == ARM::TCRETURNriND);

  SmallVector<unsigned, 4> Regs;
  unsigned i = CSI.size();
  while (i != 0) {
    unsigned LastReg = 0;
    bool DeleteRet = false;
    for (; i != 0; --i) {
      unsigned Reg = CSI[i-1].getReg();
      if (!(Func)(Reg, STI.isTargetDarwin())) continue;

      if (Reg == ARM::LR && !isTailCall && !isVarArg && STI.hasV5TOps()) {
        Reg = ARM::PC;
        LdmOpc = AFI->isThumbFunction() ? ARM::t2LDMIA_RET : ARM::LDMIA_RET;
        // Fold the return instruction into the LDM.
        DeleteRet = true;
      }

      // If NoGap is true, pop consecutive registers and then leave the rest
      // for other instructions. e.g.
      // vpop {d8, d10, d11} -> vpop {d8}, vpop {d10, d11}
      if (NoGap && LastReg && LastReg != Reg-1)
        break;

      LastReg = Reg;
      Regs.push_back(Reg);
    }

    if (Regs.empty())
      continue;
    if (Regs.size() > 1 || LdrOpc == 0) {
      MachineInstrBuilder MIB =
        AddDefaultPred(BuildMI(MBB, MI, DL, TII.get(LdmOpc), ARM::SP)
                       .addReg(ARM::SP));
      for (unsigned i = 0, e = Regs.size(); i < e; ++i)
        MIB.addReg(Regs[i], getDefRegState(true));
      if (DeleteRet)
        MI->eraseFromParent();
      MI = MIB;
    } else if (Regs.size() == 1) {
      // If we adjusted the reg to PC from LR above, switch it back here. We
      // only do that for LDM.
      if (Regs[0] == ARM::PC)
        Regs[0] = ARM::LR;
      MachineInstrBuilder MIB =
        BuildMI(MBB, MI, DL, TII.get(LdrOpc), Regs[0])
          .addReg(ARM::SP, RegState::Define)
          .addReg(ARM::SP);
      // ARM mode needs an extra reg0 here due to addrmode2. Will go away once
      // that refactoring is complete (eventually).
      if (LdrOpc == ARM::LDR_POST) {
        MIB.addReg(0);
        MIB.addImm(ARM_AM::getAM2Opc(ARM_AM::add, 4, ARM_AM::no_shift));
      } else
        MIB.addImm(4);
      AddDefaultPred(MIB);
    }
    Regs.clear();
  }
}