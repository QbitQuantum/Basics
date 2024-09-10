bool WebAssemblyLowerEmscriptenEHSjLj::runSjLjOnFunction(Function &F) {
  Module &M = *F.getParent();
  LLVMContext &C = F.getContext();
  IRBuilder<> IRB(C);
  SmallVector<Instruction *, 64> ToErase;
  // Vector of %setjmpTable values
  std::vector<Instruction *> SetjmpTableInsts;
  // Vector of %setjmpTableSize values
  std::vector<Instruction *> SetjmpTableSizeInsts;

  // Setjmp preparation

  // This instruction effectively means %setjmpTableSize = 4.
  // We create this as an instruction intentionally, and we don't want to fold
  // this instruction to a constant 4, because this value will be used in
  // SSAUpdater.AddAvailableValue(...) later.
  BasicBlock &EntryBB = F.getEntryBlock();
  BinaryOperator *SetjmpTableSize = BinaryOperator::Create(
      Instruction::Add, IRB.getInt32(4), IRB.getInt32(0), "setjmpTableSize",
      &*EntryBB.getFirstInsertionPt());
  // setjmpTable = (int *) malloc(40);
  Instruction *SetjmpTable = CallInst::CreateMalloc(
      SetjmpTableSize, IRB.getInt32Ty(), IRB.getInt32Ty(), IRB.getInt32(40),
      nullptr, nullptr, "setjmpTable");
  // setjmpTable[0] = 0;
  IRB.SetInsertPoint(SetjmpTableSize);
  IRB.CreateStore(IRB.getInt32(0), SetjmpTable);
  SetjmpTableInsts.push_back(SetjmpTable);
  SetjmpTableSizeInsts.push_back(SetjmpTableSize);

  // Setjmp transformation
  std::vector<PHINode *> SetjmpRetPHIs;
  Function *SetjmpF = M.getFunction("setjmp");
  for (User *U : SetjmpF->users()) {
    auto *CI = dyn_cast<CallInst>(U);
    if (!CI)
      report_fatal_error("Does not support indirect calls to setjmp");

    BasicBlock *BB = CI->getParent();
    if (BB->getParent() != &F) // in other function
      continue;

    // The tail is everything right after the call, and will be reached once
    // when setjmp is called, and later when longjmp returns to the setjmp
    BasicBlock *Tail = SplitBlock(BB, CI->getNextNode());
    // Add a phi to the tail, which will be the output of setjmp, which
    // indicates if this is the first call or a longjmp back. The phi directly
    // uses the right value based on where we arrive from
    IRB.SetInsertPoint(Tail->getFirstNonPHI());
    PHINode *SetjmpRet = IRB.CreatePHI(IRB.getInt32Ty(), 2, "setjmp.ret");

    // setjmp initial call returns 0
    SetjmpRet->addIncoming(IRB.getInt32(0), BB);
    // The proper output is now this, not the setjmp call itself
    CI->replaceAllUsesWith(SetjmpRet);
    // longjmp returns to the setjmp will add themselves to this phi
    SetjmpRetPHIs.push_back(SetjmpRet);

    // Fix call target
    // Our index in the function is our place in the array + 1 to avoid index
    // 0, because index 0 means the longjmp is not ours to handle.
    IRB.SetInsertPoint(CI);
    Value *Args[] = {CI->getArgOperand(0), IRB.getInt32(SetjmpRetPHIs.size()),
                     SetjmpTable, SetjmpTableSize};
    Instruction *NewSetjmpTable =
        IRB.CreateCall(SaveSetjmpF, Args, "setjmpTable");
    Instruction *NewSetjmpTableSize =
        IRB.CreateLoad(TempRet0GV, "setjmpTableSize");
    SetjmpTableInsts.push_back(NewSetjmpTable);
    SetjmpTableSizeInsts.push_back(NewSetjmpTableSize);
    ToErase.push_back(CI);
  }

  // Update each call that can longjmp so it can return to a setjmp where
  // relevant.

  // Because we are creating new BBs while processing and don't want to make
  // all these newly created BBs candidates again for longjmp processing, we
  // first make the vector of candidate BBs.
  std::vector<BasicBlock *> BBs;
  for (BasicBlock &BB : F)
    BBs.push_back(&BB);

  // BBs.size() will change within the loop, so we query it every time
  for (unsigned i = 0; i < BBs.size(); i++) {
    BasicBlock *BB = BBs[i];
    for (Instruction &I : *BB) {
      assert(!isa<InvokeInst>(&I));
      auto *CI = dyn_cast<CallInst>(&I);
      if (!CI)
        continue;

      const Value *Callee = CI->getCalledValue();
      if (!canLongjmp(M, Callee))
        continue;

      Value *Threw = nullptr;
      BasicBlock *Tail;
      if (Callee->getName().startswith(InvokePrefix)) {
        // If invoke wrapper has already been generated for this call in
        // previous EH phase, search for the load instruction
        // %__THREW__.val = __THREW__;
        // in postamble after the invoke wrapper call
        LoadInst *ThrewLI = nullptr;
        StoreInst *ThrewResetSI = nullptr;
        for (auto I = std::next(BasicBlock::iterator(CI)), IE = BB->end();
             I != IE; ++I) {
          if (auto *LI = dyn_cast<LoadInst>(I))
            if (auto *GV = dyn_cast<GlobalVariable>(LI->getPointerOperand()))
              if (GV == ThrewGV) {
                Threw = ThrewLI = LI;
                break;
              }
        }
        // Search for the store instruction after the load above
        // __THREW__ = 0;
        for (auto I = std::next(BasicBlock::iterator(ThrewLI)), IE = BB->end();
             I != IE; ++I) {
          if (auto *SI = dyn_cast<StoreInst>(I))
            if (auto *GV = dyn_cast<GlobalVariable>(SI->getPointerOperand()))
              if (GV == ThrewGV && SI->getValueOperand() == IRB.getInt32(0)) {
                ThrewResetSI = SI;
                break;
              }
        }
        assert(Threw && ThrewLI && "Cannot find __THREW__ load after invoke");
        assert(ThrewResetSI && "Cannot find __THREW__ store after invoke");
        Tail = SplitBlock(BB, ThrewResetSI->getNextNode());

      } else {
        // Wrap call with invoke wrapper and generate preamble/postamble
        Threw = wrapInvoke(CI);
        ToErase.push_back(CI);
        Tail = SplitBlock(BB, CI->getNextNode());
      }

      // We need to replace the terminator in Tail - SplitBlock makes BB go
      // straight to Tail, we need to check if a longjmp occurred, and go to the
      // right setjmp-tail if so
      ToErase.push_back(BB->getTerminator());

      // Generate a function call to testSetjmp function and preamble/postamble
      // code to figure out (1) whether longjmp occurred (2) if longjmp
      // occurred, which setjmp it corresponds to
      Value *Label = nullptr;
      Value *LongjmpResult = nullptr;
      BasicBlock *EndBB = nullptr;
      wrapTestSetjmp(BB, CI, Threw, SetjmpTable, SetjmpTableSize, Label,
                     LongjmpResult, EndBB);
      assert(Label && LongjmpResult && EndBB);

      // Create switch instruction
      IRB.SetInsertPoint(EndBB);
      SwitchInst *SI = IRB.CreateSwitch(Label, Tail, SetjmpRetPHIs.size());
      // -1 means no longjmp happened, continue normally (will hit the default
      // switch case). 0 means a longjmp that is not ours to handle, needs a
      // rethrow. Otherwise the index is the same as the index in P+1 (to avoid
      // 0).
      for (unsigned i = 0; i < SetjmpRetPHIs.size(); i++) {
        SI->addCase(IRB.getInt32(i + 1), SetjmpRetPHIs[i]->getParent());
        SetjmpRetPHIs[i]->addIncoming(LongjmpResult, EndBB);
      }

      // We are splitting the block here, and must continue to find other calls
      // in the block - which is now split. so continue to traverse in the Tail
      BBs.push_back(Tail);
    }
  }

  // Erase everything we no longer need in this function
  for (Instruction *I : ToErase)
    I->eraseFromParent();

  // Free setjmpTable buffer before each return instruction
  for (BasicBlock &BB : F) {
    TerminatorInst *TI = BB.getTerminator();
    if (isa<ReturnInst>(TI))
      CallInst::CreateFree(SetjmpTable, TI);
  }

  // Every call to saveSetjmp can change setjmpTable and setjmpTableSize
  // (when buffer reallocation occurs)
  // entry:
  //   setjmpTableSize = 4;
  //   setjmpTable = (int *) malloc(40);
  //   setjmpTable[0] = 0;
  // ...
  // somebb:
  //   setjmpTable = saveSetjmp(buf, label, setjmpTable, setjmpTableSize);
  //   setjmpTableSize = __tempRet0;
  // So we need to make sure the SSA for these variables is valid so that every
  // saveSetjmp and testSetjmp calls have the correct arguments.
  SSAUpdater SetjmpTableSSA;
  SSAUpdater SetjmpTableSizeSSA;
  SetjmpTableSSA.Initialize(Type::getInt32PtrTy(C), "setjmpTable");
  SetjmpTableSizeSSA.Initialize(Type::getInt32Ty(C), "setjmpTableSize");
  for (Instruction *I : SetjmpTableInsts)
    SetjmpTableSSA.AddAvailableValue(I->getParent(), I);
  for (Instruction *I : SetjmpTableSizeInsts)
    SetjmpTableSizeSSA.AddAvailableValue(I->getParent(), I);

  for (auto UI = SetjmpTable->use_begin(), UE = SetjmpTable->use_end();
       UI != UE;) {
    // Grab the use before incrementing the iterator.
    Use &U = *UI;
    // Increment the iterator before removing the use from the list.
    ++UI;
    if (Instruction *I = dyn_cast<Instruction>(U.getUser()))
      if (I->getParent() != &EntryBB)
        SetjmpTableSSA.RewriteUse(U);
  }
  for (auto UI = SetjmpTableSize->use_begin(), UE = SetjmpTableSize->use_end();
       UI != UE;) {
    Use &U = *UI;
    ++UI;
    if (Instruction *I = dyn_cast<Instruction>(U.getUser()))
      if (I->getParent() != &EntryBB)
        SetjmpTableSizeSSA.RewriteUse(U);
  }

  // Finally, our modifications to the cfg can break dominance of SSA variables.
  // For example, in this code,
  // if (x()) { .. setjmp() .. }
  // if (y()) { .. longjmp() .. }
  // We must split the longjmp block, and it can jump into the block splitted
  // from setjmp one. But that means that when we split the setjmp block, it's
  // first part no longer dominates its second part - there is a theoretically
  // possible control flow path where x() is false, then y() is true and we
  // reach the second part of the setjmp block, without ever reaching the first
  // part. So, we rebuild SSA form here.
  rebuildSSA(F);
  return true;
}