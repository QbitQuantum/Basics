/// Splits a MachineBasicBlock to branch before \p SplitBefore. The original
/// branch is \p OrigBranch. The target of the new branch can either be the same
/// as the target of the original branch or the fallthrough successor of the
/// original block as determined by \p BranchToFallThrough. The branch
/// conditions will be inverted according to \p InvertNewBranch and
/// \p InvertOrigBranch. If an instruction that previously fed the branch is to
/// be deleted, it is provided in \p MIToDelete and \p NewCond will be used as
/// the branch condition. The branch probabilities will be set if the
/// MachineBranchProbabilityInfo isn't null.
static bool splitMBB(BlockSplitInfo &BSI) {
  assert(BSI.allInstrsInSameMBB() &&
         "All instructions must be in the same block.");

  MachineBasicBlock *ThisMBB = BSI.OrigBranch->getParent();
  MachineFunction *MF = ThisMBB->getParent();
  MachineRegisterInfo *MRI = &MF->getRegInfo();
  assert(MRI->isSSA() && "Can only do this while the function is in SSA form.");
  if (ThisMBB->succ_size() != 2) {
    LLVM_DEBUG(
        dbgs() << "Don't know how to handle blocks that don't have exactly"
               << " two succesors.\n");
    return false;
  }

  const PPCInstrInfo *TII = MF->getSubtarget<PPCSubtarget>().getInstrInfo();
  unsigned OrigBROpcode = BSI.OrigBranch->getOpcode();
  unsigned InvertedOpcode =
      OrigBROpcode == PPC::BC
          ? PPC::BCn
          : OrigBROpcode == PPC::BCn
                ? PPC::BC
                : OrigBROpcode == PPC::BCLR ? PPC::BCLRn : PPC::BCLR;
  unsigned NewBROpcode = BSI.InvertNewBranch ? InvertedOpcode : OrigBROpcode;
  MachineBasicBlock *OrigTarget = BSI.OrigBranch->getOperand(1).getMBB();
  MachineBasicBlock *OrigFallThrough = OrigTarget == *ThisMBB->succ_begin()
                                           ? *ThisMBB->succ_rbegin()
                                           : *ThisMBB->succ_begin();
  MachineBasicBlock *NewBRTarget =
      BSI.BranchToFallThrough ? OrigFallThrough : OrigTarget;
  BranchProbability ProbToNewTarget =
      !BSI.MBPI ? BranchProbability::getUnknown()
                : BSI.MBPI->getEdgeProbability(ThisMBB, NewBRTarget);

  // Create a new basic block.
  MachineBasicBlock::iterator InsertPoint = BSI.SplitBefore;
  const BasicBlock *LLVM_BB = ThisMBB->getBasicBlock();
  MachineFunction::iterator It = ThisMBB->getIterator();
  MachineBasicBlock *NewMBB = MF->CreateMachineBasicBlock(LLVM_BB);
  MF->insert(++It, NewMBB);

  // Move everything after SplitBefore into the new block.
  NewMBB->splice(NewMBB->end(), ThisMBB, InsertPoint, ThisMBB->end());
  NewMBB->transferSuccessors(ThisMBB);

  // Add the two successors to ThisMBB. The probabilities come from the
  // existing blocks if available.
  ThisMBB->addSuccessor(NewBRTarget, ProbToNewTarget);
  ThisMBB->addSuccessor(NewMBB, ProbToNewTarget.getCompl());

  // Add the branches to ThisMBB.
  BuildMI(*ThisMBB, ThisMBB->end(), BSI.SplitBefore->getDebugLoc(),
          TII->get(NewBROpcode))
      .addReg(BSI.SplitCond->getOperand(0).getReg())
      .addMBB(NewBRTarget);
  BuildMI(*ThisMBB, ThisMBB->end(), BSI.SplitBefore->getDebugLoc(),
          TII->get(PPC::B))
      .addMBB(NewMBB);
  if (BSI.MIToDelete)
    BSI.MIToDelete->eraseFromParent();

  // Change the condition on the original branch and invert it if requested.
  auto FirstTerminator = NewMBB->getFirstTerminator();
  if (BSI.NewCond) {
    assert(FirstTerminator->getOperand(0).isReg() &&
           "Can't update condition of unconditional branch.");
    FirstTerminator->getOperand(0).setReg(BSI.NewCond->getOperand(0).getReg());
  }
  if (BSI.InvertOrigBranch)
    FirstTerminator->setDesc(TII->get(InvertedOpcode));

  // If any of the PHIs in the successors of NewMBB reference values that
  // now come from NewMBB, they need to be updated.
  for (auto *Succ : NewMBB->successors()) {
    updatePHIs(Succ, ThisMBB, NewMBB, MRI);
  }
  addIncomingValuesToPHIs(NewBRTarget, ThisMBB, NewMBB, MRI);

  LLVM_DEBUG(dbgs() << "After splitting, ThisMBB:\n"; ThisMBB->dump());
  LLVM_DEBUG(dbgs() << "NewMBB:\n"; NewMBB->dump());
  LLVM_DEBUG(dbgs() << "New branch-to block:\n"; NewBRTarget->dump());
  return true;
}