bool AtomicExpandLoadLinked::expandAtomicCmpXchg(AtomicCmpXchgInst *CI) {
  AtomicOrdering SuccessOrder = CI->getSuccessOrdering();
  AtomicOrdering FailureOrder = CI->getFailureOrdering();
  Value *Addr = CI->getPointerOperand();
  BasicBlock *BB = CI->getParent();
  Function *F = BB->getParent();
  LLVMContext &Ctx = F->getContext();

  // Given: cmpxchg some_op iN* %addr, iN %desired, iN %new success_ord fail_ord
  //
  // The full expansion we produce is:
  //     [...]
  //     fence?
  // cmpxchg.start:
  //     %loaded = @load.linked(%addr)
  //     %should_store = icmp eq %loaded, %desired
  //     br i1 %should_store, label %cmpxchg.trystore,
  //                          label %cmpxchg.end/%cmpxchg.barrier
  // cmpxchg.trystore:
  //     %stored = @store_conditional(%new, %addr)
  //     %try_again = icmp i32 ne %stored, 0
  //     br i1 %try_again, label %loop, label %cmpxchg.end
  // cmpxchg.barrier:
  //     fence?
  //     br label %cmpxchg.end
  // cmpxchg.end:
  //     [...]
  BasicBlock *ExitBB = BB->splitBasicBlock(CI, "cmpxchg.end");
  auto BarrierBB = BasicBlock::Create(Ctx, "cmpxchg.barrier", F, ExitBB);
  auto TryStoreBB = BasicBlock::Create(Ctx, "cmpxchg.trystore", F, BarrierBB);
  auto LoopBB = BasicBlock::Create(Ctx, "cmpxchg.start", F, TryStoreBB);

  // This grabs the DebugLoc from CI
  IRBuilder<> Builder(CI);

  // The split call above "helpfully" added a branch at the end of BB (to the
  // wrong place), but we might want a fence too. It's easiest to just remove
  // the branch entirely.
  std::prev(BB->end())->eraseFromParent();
  Builder.SetInsertPoint(BB);
  AtomicOrdering MemOpOrder = insertLeadingFence(Builder, SuccessOrder);
  Builder.CreateBr(LoopBB);

  // Start the main loop block now that we've taken care of the preliminaries.
  Builder.SetInsertPoint(LoopBB);
  Value *Loaded = TLI->emitLoadLinked(Builder, Addr, MemOpOrder);
  Value *ShouldStore =
      Builder.CreateICmpEQ(Loaded, CI->getCompareOperand(), "should_store");

  // If the the cmpxchg doesn't actually need any ordering when it fails, we can
  // jump straight past that fence instruction (if it exists).
  BasicBlock *FailureBB = FailureOrder == Monotonic ? ExitBB : BarrierBB;
  Builder.CreateCondBr(ShouldStore, TryStoreBB, FailureBB);

  Builder.SetInsertPoint(TryStoreBB);
  Value *StoreSuccess = TLI->emitStoreConditional(
      Builder, CI->getNewValOperand(), Addr, MemOpOrder);
  Value *TryAgain = Builder.CreateICmpNE(
      StoreSuccess, ConstantInt::get(Type::getInt32Ty(Ctx), 0), "success");
  Builder.CreateCondBr(TryAgain, LoopBB, BarrierBB);

  // Make sure later instructions don't get reordered with a fence if necessary.
  Builder.SetInsertPoint(BarrierBB);
  insertTrailingFence(Builder, SuccessOrder);
  Builder.CreateBr(ExitBB);

  // Finally, we have control-flow based knowledge of whether the cmpxchg
  // succeeded or not. We expose this to later passes by converting any
  // subsequent "icmp eq/ne %loaded, %oldval" into a use of an appropriate PHI.

  // Setup the builder so we can create any PHIs we need.
  Builder.SetInsertPoint(FailureBB, FailureBB->begin());
  BasicBlock *SuccessBB = FailureOrder == Monotonic ? BarrierBB : TryStoreBB;
  PHINode *Success = 0, *Failure = 0;

  // Look for any users of the cmpxchg that are just comparing the loaded value
  // against the desired one, and replace them with the CFG-derived version.
  for (auto User : CI->users()) {
    ICmpInst *ICmp = dyn_cast<ICmpInst>(User);
    if (!ICmp)
      continue;

    // Because we know ICmp uses CI, we only need one operand to be the old
    // value.
    if (ICmp->getOperand(0) != CI->getCompareOperand() &&
        ICmp->getOperand(1) != CI->getCompareOperand())
      continue;

    if (ICmp->getPredicate() == CmpInst::ICMP_EQ) {
      if (!Success) {
        Success = Builder.CreatePHI(Type::getInt1Ty(Ctx), 2);
        Success->addIncoming(ConstantInt::getTrue(Ctx), SuccessBB);
        Success->addIncoming(ConstantInt::getFalse(Ctx), LoopBB);
      }
      ICmp->replaceAllUsesWith(Success);
    } else if (ICmp->getPredicate() == CmpInst::ICMP_NE) {
      if (!Failure) {
        Failure = Builder.CreatePHI(Type::getInt1Ty(Ctx), 2);
        Failure->addIncoming(ConstantInt::getFalse(Ctx), SuccessBB);
        Failure->addIncoming(ConstantInt::getTrue(Ctx), LoopBB);
      }
      ICmp->replaceAllUsesWith(Failure);
    }
  }

  CI->replaceAllUsesWith(Loaded);
  CI->eraseFromParent();

  return true;
}