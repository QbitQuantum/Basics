bool SIFoldOperands::runOnMachineFunction(MachineFunction &MF) {
  MachineRegisterInfo &MRI = MF.getRegInfo();
  const SIInstrInfo *TII =
      static_cast<const SIInstrInfo *>(MF.getSubtarget().getInstrInfo());
  const SIRegisterInfo &TRI = TII->getRegisterInfo();

  for (MachineFunction::iterator BI = MF.begin(), BE = MF.end();
                                                  BI != BE; ++BI) {

    MachineBasicBlock &MBB = *BI;
    MachineBasicBlock::iterator I, Next;
    for (I = MBB.begin(); I != MBB.end(); I = Next) {
      Next = std::next(I);
      MachineInstr &MI = *I;

      if (!isSafeToFold(MI.getOpcode()))
        continue;

      unsigned OpSize = TII->getOpSize(MI, 1);
      MachineOperand &OpToFold = MI.getOperand(1);
      bool FoldingImm = OpToFold.isImm();

      // FIXME: We could also be folding things like FrameIndexes and
      // TargetIndexes.
      if (!FoldingImm && !OpToFold.isReg())
        continue;

      // Folding immediates with more than one use will increase program size.
      // FIXME: This will also reduce register usage, which may be better
      // in some cases.  A better heuristic is needed.
      if (FoldingImm && !TII->isInlineConstant(OpToFold, OpSize) &&
          !MRI.hasOneUse(MI.getOperand(0).getReg()))
        continue;

      // FIXME: Fold operands with subregs.
      if (OpToFold.isReg() &&
          (!TargetRegisterInfo::isVirtualRegister(OpToFold.getReg()) ||
           OpToFold.getSubReg()))
        continue;

      std::vector<FoldCandidate> FoldList;
      for (MachineRegisterInfo::use_iterator
           Use = MRI.use_begin(MI.getOperand(0).getReg()), E = MRI.use_end();
           Use != E; ++Use) {

        MachineInstr *UseMI = Use->getParent();
        const MachineOperand &UseOp = UseMI->getOperand(Use.getOperandNo());

        // FIXME: Fold operands with subregs.
        if (UseOp.isReg() && ((UseOp.getSubReg() && OpToFold.isReg()) ||
            UseOp.isImplicit())) {
          continue;
        }

        APInt Imm;

        if (FoldingImm) {
          unsigned UseReg = UseOp.getReg();
          const TargetRegisterClass *UseRC
            = TargetRegisterInfo::isVirtualRegister(UseReg) ?
            MRI.getRegClass(UseReg) :
            TRI.getRegClass(UseReg);

          Imm = APInt(64, OpToFold.getImm());

          // Split 64-bit constants into 32-bits for folding.
          if (UseOp.getSubReg()) {
            if (UseRC->getSize() != 8)
              continue;

            if (UseOp.getSubReg() == AMDGPU::sub0) {
              Imm = Imm.getLoBits(32);
            } else {
              assert(UseOp.getSubReg() == AMDGPU::sub1);
              Imm = Imm.getHiBits(32);
            }
          }

          // In order to fold immediates into copies, we need to change the
          // copy to a MOV.
          if (UseMI->getOpcode() == AMDGPU::COPY) {
            unsigned DestReg = UseMI->getOperand(0).getReg();
            const TargetRegisterClass *DestRC
              = TargetRegisterInfo::isVirtualRegister(DestReg) ?
              MRI.getRegClass(DestReg) :
              TRI.getRegClass(DestReg);

            unsigned MovOp = TII->getMovOpcode(DestRC);
            if (MovOp == AMDGPU::COPY)
              continue;

            UseMI->setDesc(TII->get(MovOp));
          }
        }

        const MCInstrDesc &UseDesc = UseMI->getDesc();

        // Don't fold into target independent nodes.  Target independent opcodes
        // don't have defined register classes.
        if (UseDesc.isVariadic() ||
            UseDesc.OpInfo[Use.getOperandNo()].RegClass == -1)
          continue;

        if (FoldingImm) {
          MachineOperand ImmOp = MachineOperand::CreateImm(Imm.getSExtValue());
          tryAddToFoldList(FoldList, UseMI, Use.getOperandNo(), &ImmOp, TII);
          continue;
        }

        tryAddToFoldList(FoldList, UseMI, Use.getOperandNo(), &OpToFold, TII);

        // FIXME: We could try to change the instruction from 64-bit to 32-bit
        // to enable more folding opportunites.  The shrink operands pass
        // already does this.
      }

      for (FoldCandidate &Fold : FoldList) {
        if (updateOperand(Fold, TRI)) {
          // Clear kill flags.
          if (!Fold.isImm()) {
            assert(Fold.OpToFold && Fold.OpToFold->isReg());
            Fold.OpToFold->setIsKill(false);
          }
          DEBUG(dbgs() << "Folded source from " << MI << " into OpNo " <<
                Fold.UseOpNo << " of " << *Fold.UseMI << '\n');
        }
      }
    }
  }
  return false;
}