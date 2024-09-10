void MipsSEInstrInfo::
storeRegToStack(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                unsigned SrcReg, bool isKill, int FI,
                const TargetRegisterClass *RC, const TargetRegisterInfo *TRI,
                int64_t Offset) const {
  DebugLoc DL;
  MachineMemOperand *MMO = GetMemOperand(MBB, FI, MachineMemOperand::MOStore);

  unsigned Opc = 0;

  if (Mips::GPR32RegClass.hasSubClassEq(RC))
    Opc = Mips::SW;
  else if (Mips::GPR64RegClass.hasSubClassEq(RC))
    Opc = Mips::SD;
  else if (Mips::ACC64RegClass.hasSubClassEq(RC))
    Opc = Mips::STORE_ACC64;
  else if (Mips::ACC64DSPRegClass.hasSubClassEq(RC))
    Opc = Mips::STORE_ACC64DSP;
  else if (Mips::ACC128RegClass.hasSubClassEq(RC))
    Opc = Mips::STORE_ACC128;
  else if (Mips::DSPCCRegClass.hasSubClassEq(RC))
    Opc = Mips::STORE_CCOND_DSP;
  else if (Mips::FGR32RegClass.hasSubClassEq(RC))
    Opc = Mips::SWC1;
  else if (Mips::AFGR64RegClass.hasSubClassEq(RC))
    Opc = Mips::SDC1;
  else if (Mips::FGR64RegClass.hasSubClassEq(RC))
    Opc = Mips::SDC164;
  else if (TRI->isTypeLegalForClass(*RC, MVT::v16i8))
    Opc = Mips::ST_B;
  else if (TRI->isTypeLegalForClass(*RC, MVT::v8i16) ||
           TRI->isTypeLegalForClass(*RC, MVT::v8f16))
    Opc = Mips::ST_H;
  else if (TRI->isTypeLegalForClass(*RC, MVT::v4i32) ||
           TRI->isTypeLegalForClass(*RC, MVT::v4f32))
    Opc = Mips::ST_W;
  else if (TRI->isTypeLegalForClass(*RC, MVT::v2i64) ||
           TRI->isTypeLegalForClass(*RC, MVT::v2f64))
    Opc = Mips::ST_D;
  else if (Mips::LO32RegClass.hasSubClassEq(RC))
    Opc = Mips::SW;
  else if (Mips::LO64RegClass.hasSubClassEq(RC))
    Opc = Mips::SD;
  else if (Mips::HI32RegClass.hasSubClassEq(RC))
    Opc = Mips::SW;
  else if (Mips::HI64RegClass.hasSubClassEq(RC))
    Opc = Mips::SD;

  // Hi, Lo are normally caller save but they are callee save
  // for interrupt handling.
  const Function *Func = MBB.getParent()->getFunction();
  if (Func->hasFnAttribute("interrupt")) {
    if (Mips::HI32RegClass.hasSubClassEq(RC)) {
      BuildMI(MBB, I, DL, get(Mips::MFHI), Mips::K0);
      SrcReg = Mips::K0;
    } else if (Mips::HI64RegClass.hasSubClassEq(RC)) {
      BuildMI(MBB, I, DL, get(Mips::MFHI64), Mips::K0_64);
      SrcReg = Mips::K0_64;
    } else if (Mips::LO32RegClass.hasSubClassEq(RC)) {
      BuildMI(MBB, I, DL, get(Mips::MFLO), Mips::K0);
      SrcReg = Mips::K0;
    } else if (Mips::LO64RegClass.hasSubClassEq(RC)) {
      BuildMI(MBB, I, DL, get(Mips::MFLO64), Mips::K0_64);
      SrcReg = Mips::K0_64;
    }
  }

  assert(Opc && "Register class not handled!");
  BuildMI(MBB, I, DL, get(Opc)).addReg(SrcReg, getKillRegState(isKill))
    .addFrameIndex(FI).addImm(Offset).addMemOperand(MMO);
}