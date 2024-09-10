/// OptimizeInstr - If instruction is a copy-like instruction, i.e. it reads
/// a single register and writes a single register and it does not modify
/// the source, and if the source value is preserved as a sub-register of
/// the result, then replace all reachable uses of the source with the subreg
/// of the result.
/// Do not generate an EXTRACT that is used only in a debug use, as this
/// changes the code.  Since this code does not currently share EXTRACTs, just
/// ignore all debug uses.
bool OptimizeExts::OptimizeInstr(MachineInstr *MI, MachineBasicBlock *MBB,
                                 SmallPtrSet<MachineInstr*, 8> &LocalMIs) {
  bool Changed = false;
  LocalMIs.insert(MI);

  unsigned SrcReg, DstReg, SubIdx;
  if (TII->isCoalescableExtInstr(*MI, SrcReg, DstReg, SubIdx)) {
    if (TargetRegisterInfo::isPhysicalRegister(DstReg) ||
        TargetRegisterInfo::isPhysicalRegister(SrcReg))
      return false;

    MachineRegisterInfo::use_nodbg_iterator UI = MRI->use_nodbg_begin(SrcReg);
    if (++UI == MRI->use_nodbg_end())
      // No other uses.
      return false;

    // Ok, the source has other uses. See if we can replace the other uses
    // with use of the result of the extension.
    SmallPtrSet<MachineBasicBlock*, 4> ReachedBBs;
    UI = MRI->use_nodbg_begin(DstReg);
    for (MachineRegisterInfo::use_nodbg_iterator UE = MRI->use_nodbg_end();
         UI != UE; ++UI)
      ReachedBBs.insert(UI->getParent());

    bool ExtendLife = true;
    // Uses that are in the same BB of uses of the result of the instruction.
    SmallVector<MachineOperand*, 8> Uses;
    // Uses that the result of the instruction can reach.
    SmallVector<MachineOperand*, 8> ExtendedUses;

    UI = MRI->use_nodbg_begin(SrcReg);
    for (MachineRegisterInfo::use_nodbg_iterator UE = MRI->use_nodbg_end();
         UI != UE; ++UI) {
      MachineOperand &UseMO = UI.getOperand();
      MachineInstr *UseMI = &*UI;
      if (UseMI == MI)
        continue;
      if (UseMI->isPHI()) {
        ExtendLife = false;
        continue;
      }

      // It's an error to translate this:
      //
      //    %reg1025 = <sext> %reg1024
      //     ...
      //    %reg1026 = SUBREG_TO_REG 0, %reg1024, 4
      //
      // into this:
      //
      //    %reg1025 = <sext> %reg1024
      //     ...
      //    %reg1027 = COPY %reg1025:4
      //    %reg1026 = SUBREG_TO_REG 0, %reg1027, 4
      //
      // The problem here is that SUBREG_TO_REG is there to assert that an
      // implicit zext occurs. It doesn't insert a zext instruction. If we allow
      // the COPY here, it will give us the value after the <sext>,
      // not the original value of %reg1024 before <sext>.
      if (UseMI->getOpcode() == TargetOpcode::SUBREG_TO_REG)
        continue;

      MachineBasicBlock *UseMBB = UseMI->getParent();
      if (UseMBB == MBB) {
        // Local uses that come after the extension.
        if (!LocalMIs.count(UseMI))
          Uses.push_back(&UseMO);
      } else if (ReachedBBs.count(UseMBB))
        // Non-local uses where the result of extension is used. Always
        // replace these unless it's a PHI.
        Uses.push_back(&UseMO);
      else if (Aggressive && DT->dominates(MBB, UseMBB))
        // We may want to extend live range of the extension result in order
        // to replace these uses.
        ExtendedUses.push_back(&UseMO);
      else {
        // Both will be live out of the def MBB anyway. Don't extend live
        // range of the extension result.
        ExtendLife = false;
        break;
      }
    }

    if (ExtendLife && !ExtendedUses.empty())
      // Ok, we'll extend the liveness of the extension result.
      std::copy(ExtendedUses.begin(), ExtendedUses.end(),
                std::back_inserter(Uses));

    // Now replace all uses.
    if (!Uses.empty()) {
      SmallPtrSet<MachineBasicBlock*, 4> PHIBBs;
      // Look for PHI uses of the extended result, we don't want to extend the
      // liveness of a PHI input. It breaks all kinds of assumptions down
      // stream. A PHI use is expected to be the kill of its source values.
      UI = MRI->use_nodbg_begin(DstReg);
      for (MachineRegisterInfo::use_nodbg_iterator UE = MRI->use_nodbg_end();
           UI != UE; ++UI)
        if (UI->isPHI())
          PHIBBs.insert(UI->getParent());

      const TargetRegisterClass *RC = MRI->getRegClass(SrcReg);
      for (unsigned i = 0, e = Uses.size(); i != e; ++i) {
        MachineOperand *UseMO = Uses[i];
        MachineInstr *UseMI = UseMO->getParent();
        MachineBasicBlock *UseMBB = UseMI->getParent();
        if (PHIBBs.count(UseMBB))
          continue;
        unsigned NewVR = MRI->createVirtualRegister(RC);
        BuildMI(*UseMBB, UseMI, UseMI->getDebugLoc(),
                TII->get(TargetOpcode::COPY), NewVR)
          .addReg(DstReg, 0, SubIdx);
        UseMO->setReg(NewVR);
        ++NumReuse;
        Changed = true;
      }
    }
  }

  return Changed;
}