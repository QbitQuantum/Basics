bool AMDGPUInstructionSelector::selectG_CONSTANT(MachineInstr &I) const {
  MachineBasicBlock *BB = I.getParent();
  MachineFunction *MF = BB->getParent();
  MachineRegisterInfo &MRI = MF->getRegInfo();
  MachineOperand &ImmOp = I.getOperand(1);

  // The AMDGPU backend only supports Imm operands and not CImm or FPImm.
  if (ImmOp.isFPImm()) {
    const APInt &Imm = ImmOp.getFPImm()->getValueAPF().bitcastToAPInt();
    ImmOp.ChangeToImmediate(Imm.getZExtValue());
  } else if (ImmOp.isCImm()) {
    ImmOp.ChangeToImmediate(ImmOp.getCImm()->getZExtValue());
  }

  unsigned DstReg = I.getOperand(0).getReg();
  unsigned Size;
  bool IsSgpr;
  const RegisterBank *RB = MRI.getRegBankOrNull(I.getOperand(0).getReg());
  if (RB) {
    IsSgpr = RB->getID() == AMDGPU::SGPRRegBankID;
    Size = MRI.getType(DstReg).getSizeInBits();
  } else {
    const TargetRegisterClass *RC = TRI.getRegClassForReg(MRI, DstReg);
    IsSgpr = TRI.isSGPRClass(RC);
    Size = TRI.getRegSizeInBits(*RC);
  }

  if (Size != 32 && Size != 64)
    return false;

  unsigned Opcode = IsSgpr ? AMDGPU::S_MOV_B32 : AMDGPU::V_MOV_B32_e32;
  if (Size == 32) {
    I.setDesc(TII.get(Opcode));
    I.addImplicitDefUseOperands(*MF);
    return constrainSelectedInstRegOperands(I, TII, TRI, RBI);
  }

  DebugLoc DL = I.getDebugLoc();
  const TargetRegisterClass *RC = IsSgpr ? &AMDGPU::SReg_32_XM0RegClass :
                                           &AMDGPU::VGPR_32RegClass;
  unsigned LoReg = MRI.createVirtualRegister(RC);
  unsigned HiReg = MRI.createVirtualRegister(RC);
  const APInt &Imm = APInt(Size, I.getOperand(1).getImm());

  BuildMI(*BB, &I, DL, TII.get(Opcode), LoReg)
          .addImm(Imm.trunc(32).getZExtValue());

  BuildMI(*BB, &I, DL, TII.get(Opcode), HiReg)
          .addImm(Imm.ashr(32).getZExtValue());

  const MachineInstr *RS =
      BuildMI(*BB, &I, DL, TII.get(AMDGPU::REG_SEQUENCE), DstReg)
              .addReg(LoReg)
              .addImm(AMDGPU::sub0)
              .addReg(HiReg)
              .addImm(AMDGPU::sub1);

  // We can't call constrainSelectedInstRegOperands here, because it doesn't
  // work for target independent opcodes
  I.eraseFromParent();
  const TargetRegisterClass *DstRC =
      TRI.getConstrainedRegClassForOperand(RS->getOperand(0), MRI);
  if (!DstRC)
    return true;
  return RBI.constrainGenericRegister(DstReg, *DstRC, MRI);
}