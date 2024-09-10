bool llvm::expandAtomicRMWToCmpXchg(AtomicRMWInst *AI,
                                    CreateCmpXchgInstFun CreateCmpXchg) {
  assert(AI);

  AtomicOrdering MemOpOrder =
      AI->getOrdering() == Unordered ? Monotonic : AI->getOrdering();
  Value *Addr = AI->getPointerOperand();
  BasicBlock *BB = AI->getParent();
  Function *F = BB->getParent();
  LLVMContext &Ctx = F->getContext();

  // Given: atomicrmw some_op iN* %addr, iN %incr ordering
  //
  // The standard expansion we produce is:
  //     [...]
  //     %init_loaded = load atomic iN* %addr
  //     br label %loop
  // loop:
  //     %loaded = phi iN [ %init_loaded, %entry ], [ %new_loaded, %loop ]
  //     %new = some_op iN %loaded, %incr
  //     %pair = cmpxchg iN* %addr, iN %loaded, iN %new
  //     %new_loaded = extractvalue { iN, i1 } %pair, 0
  //     %success = extractvalue { iN, i1 } %pair, 1
  //     br i1 %success, label %atomicrmw.end, label %loop
  // atomicrmw.end:
  //     [...]
  BasicBlock *ExitBB = BB->splitBasicBlock(AI->getIterator(), "atomicrmw.end");
  BasicBlock *LoopBB = BasicBlock::Create(Ctx, "atomicrmw.start", F, ExitBB);

  // This grabs the DebugLoc from AI.
  IRBuilder<> Builder(AI);

  // The split call above "helpfully" added a branch at the end of BB (to the
  // wrong place), but we want a load. It's easiest to just remove
  // the branch entirely.
  std::prev(BB->end())->eraseFromParent();
  Builder.SetInsertPoint(BB);
  LoadInst *InitLoaded = Builder.CreateLoad(Addr);
  // Atomics require at least natural alignment.
  InitLoaded->setAlignment(AI->getType()->getPrimitiveSizeInBits() / 8);
  Builder.CreateBr(LoopBB);

  // Start the main loop block now that we've taken care of the preliminaries.
  Builder.SetInsertPoint(LoopBB);
  PHINode *Loaded = Builder.CreatePHI(AI->getType(), 2, "loaded");
  Loaded->addIncoming(InitLoaded, BB);

  Value *NewVal =
      performAtomicOp(AI->getOperation(), Builder, Loaded, AI->getValOperand());

  Value *NewLoaded = nullptr;
  Value *Success = nullptr;

  CreateCmpXchg(Builder, Addr, Loaded, NewVal, MemOpOrder,
                Success, NewLoaded);
  assert(Success && NewLoaded);

  Loaded->addIncoming(NewLoaded, LoopBB);

  Builder.CreateCondBr(Success, ExitBB, LoopBB);

  Builder.SetInsertPoint(ExitBB, ExitBB->begin());

  AI->replaceAllUsesWith(NewLoaded);
  AI->eraseFromParent();

  return true;
}