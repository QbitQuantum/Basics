void X86CallFrameOptimization::adjustCallSequence(MachineFunction &MF,
                                                  const CallContext &Context) {
  // Ok, we can in fact do the transformation for this call.
  // Do not remove the FrameSetup instruction, but adjust the parameters.
  // PEI will end up finalizing the handling of this.
  MachineBasicBlock::iterator FrameSetup = Context.FrameSetup;
  MachineBasicBlock &MBB = *(FrameSetup->getParent());
  TII->setFrameAdjustment(*FrameSetup, Context.ExpectedDist);

  DebugLoc DL = FrameSetup->getDebugLoc();
  bool Is64Bit = STI->is64Bit();
  // Now, iterate through the vector in reverse order, and replace the store to
  // stack with pushes. MOVmi/MOVmr doesn't have any defs, so no need to
  // replace uses.
  for (int Idx = (Context.ExpectedDist >> Log2SlotSize) - 1; Idx >= 0; --Idx) {
    MachineBasicBlock::iterator Store = *Context.ArgStoreVector[Idx];
    MachineOperand PushOp = Store->getOperand(X86::AddrNumOperands);
    MachineBasicBlock::iterator Push = nullptr;
    unsigned PushOpcode;
    switch (Store->getOpcode()) {
    default:
      llvm_unreachable("Unexpected Opcode!");
    case X86::AND16mi8:
    case X86::AND32mi8:
    case X86::AND64mi8:
    case X86::OR16mi8:
    case X86::OR32mi8:
    case X86::OR64mi8:
    case X86::MOV32mi:
    case X86::MOV64mi32:
      PushOpcode = Is64Bit ? X86::PUSH64i32 : X86::PUSHi32;
      // If the operand is a small (8-bit) immediate, we can use a
      // PUSH instruction with a shorter encoding.
      // Note that isImm() may fail even though this is a MOVmi, because
      // the operand can also be a symbol.
      if (PushOp.isImm()) {
        int64_t Val = PushOp.getImm();
        if (isInt<8>(Val))
          PushOpcode = Is64Bit ? X86::PUSH64i8 : X86::PUSH32i8;
      }
      Push = BuildMI(MBB, Context.Call, DL, TII->get(PushOpcode)).add(PushOp);
      break;
    case X86::MOV32mr:
    case X86::MOV64mr: {
      unsigned int Reg = PushOp.getReg();

      // If storing a 32-bit vreg on 64-bit targets, extend to a 64-bit vreg
      // in preparation for the PUSH64. The upper 32 bits can be undef.
      if (Is64Bit && Store->getOpcode() == X86::MOV32mr) {
        unsigned UndefReg = MRI->createVirtualRegister(&X86::GR64RegClass);
        Reg = MRI->createVirtualRegister(&X86::GR64RegClass);
        BuildMI(MBB, Context.Call, DL, TII->get(X86::IMPLICIT_DEF), UndefReg);
        BuildMI(MBB, Context.Call, DL, TII->get(X86::INSERT_SUBREG), Reg)
            .addReg(UndefReg)
            .add(PushOp)
            .addImm(X86::sub_32bit);
      }

      // If PUSHrmm is not slow on this target, try to fold the source of the
      // push into the instruction.
      bool SlowPUSHrmm = STI->isAtom() || STI->isSLM();

      // Check that this is legal to fold. Right now, we're extremely
      // conservative about that.
      MachineInstr *DefMov = nullptr;
      if (!SlowPUSHrmm && (DefMov = canFoldIntoRegPush(FrameSetup, Reg))) {
        PushOpcode = Is64Bit ? X86::PUSH64rmm : X86::PUSH32rmm;
        Push = BuildMI(MBB, Context.Call, DL, TII->get(PushOpcode));

        unsigned NumOps = DefMov->getDesc().getNumOperands();
        for (unsigned i = NumOps - X86::AddrNumOperands; i != NumOps; ++i)
          Push->addOperand(DefMov->getOperand(i));

        DefMov->eraseFromParent();
      } else {
        PushOpcode = Is64Bit ? X86::PUSH64r : X86::PUSH32r;
        Push = BuildMI(MBB, Context.Call, DL, TII->get(PushOpcode))
                   .addReg(Reg)
                   .getInstr();
      }
      break;
    }
    }

    // For debugging, when using SP-based CFA, we need to adjust the CFA
    // offset after each push.
    // TODO: This is needed only if we require precise CFA.
    if (!TFL->hasFP(MF))
      TFL->BuildCFI(
          MBB, std::next(Push), DL,
          MCCFIInstruction::createAdjustCfaOffset(nullptr, SlotSize));

    MBB.erase(Store);
  }

  // The stack-pointer copy is no longer used in the call sequences.
  // There should not be any other users, but we can't commit to that, so:
  if (Context.SPCopy && MRI->use_empty(Context.SPCopy->getOperand(0).getReg()))
    Context.SPCopy->eraseFromParent();

  // Once we've done this, we need to make sure PEI doesn't assume a reserved
  // frame.
  X86MachineFunctionInfo *FuncInfo = MF.getInfo<X86MachineFunctionInfo>();
  FuncInfo->setHasPushSequences(true);
}