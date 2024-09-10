void SIInsertSkips::kill(MachineInstr &MI) {
  MachineBasicBlock &MBB = *MI.getParent();
  DebugLoc DL = MI.getDebugLoc();
  const MachineOperand &Op = MI.getOperand(0);

#ifndef NDEBUG
  CallingConv::ID CallConv = MBB.getParent()->getFunction()->getCallingConv();
  // Kill is only allowed in pixel / geometry shaders.
  assert(CallConv == CallingConv::AMDGPU_PS ||
         CallConv == CallingConv::AMDGPU_GS);
#endif
  // Clear this thread from the exec mask if the operand is negative.
  if (Op.isImm()) {
    // Constant operand: Set exec mask to 0 or do nothing
    if (Op.getImm() & 0x80000000) {
      BuildMI(MBB, &MI, DL, TII->get(AMDGPU::S_MOV_B64), AMDGPU::EXEC)
        .addImm(0);
    }
  } else {
    BuildMI(MBB, &MI, DL, TII->get(AMDGPU::V_CMPX_LE_F32_e32))
      .addImm(0)
      .addOperand(Op);
  }
}