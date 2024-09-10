bool ThreadSanitizer::runOnFunction(Function &F) {
  if (!TD) return false;
  if (BL->isIn(F)) return false;
  initializeCallbacks(*F.getParent());
  SmallVector<Instruction*, 8> RetVec;
  SmallVector<Instruction*, 8> AllLoadsAndStores;
  SmallVector<Instruction*, 8> LocalLoadsAndStores;
  SmallVector<Instruction*, 8> AtomicAccesses;
  SmallVector<Instruction*, 8> MemIntrinCalls;
  bool Res = false;
  bool HasCalls = false;

  // Traverse all instructions, collect loads/stores/returns, check for calls.
  for (Function::iterator FI = F.begin(), FE = F.end();
       FI != FE; ++FI) {
    BasicBlock &BB = *FI;
    for (BasicBlock::iterator BI = BB.begin(), BE = BB.end();
         BI != BE; ++BI) {
      if (isAtomic(BI))
        AtomicAccesses.push_back(BI);
      else if (isa<LoadInst>(BI) || isa<StoreInst>(BI))
        LocalLoadsAndStores.push_back(BI);
      else if (isa<ReturnInst>(BI))
        RetVec.push_back(BI);
      else if (isa<CallInst>(BI) || isa<InvokeInst>(BI)) {
        if (isa<MemIntrinsic>(BI))
          MemIntrinCalls.push_back(BI);
        HasCalls = true;
        chooseInstructionsToInstrument(LocalLoadsAndStores, AllLoadsAndStores);
      }
    }
    chooseInstructionsToInstrument(LocalLoadsAndStores, AllLoadsAndStores);
  }

  // We have collected all loads and stores.
  // FIXME: many of these accesses do not need to be checked for races
  // (e.g. variables that do not escape, etc).

  // Instrument memory accesses.
  if (ClInstrumentMemoryAccesses)
    for (size_t i = 0, n = AllLoadsAndStores.size(); i < n; ++i) {
      Res |= instrumentLoadOrStore(AllLoadsAndStores[i]);
    }

  // Instrument atomic memory accesses.
  if (ClInstrumentAtomics)
    for (size_t i = 0, n = AtomicAccesses.size(); i < n; ++i) {
      Res |= instrumentAtomic(AtomicAccesses[i]);
    }

  if (ClInstrumentMemIntrinsics)
    for (size_t i = 0, n = MemIntrinCalls.size(); i < n; ++i) {
      Res |= instrumentMemIntrinsic(MemIntrinCalls[i]);
    }

  // Instrument function entry/exit points if there were instrumented accesses.
  if ((Res || HasCalls) && ClInstrumentFuncEntryExit) {
    IRBuilder<> IRB(F.getEntryBlock().getFirstNonPHI());
    Value *ReturnAddress = IRB.CreateCall(
        Intrinsic::getDeclaration(F.getParent(), Intrinsic::returnaddress),
        IRB.getInt32(0));
    IRB.CreateCall(TsanFuncEntry, ReturnAddress);
    for (size_t i = 0, n = RetVec.size(); i < n; ++i) {
      IRBuilder<> IRBRet(RetVec[i]);
      IRBRet.CreateCall(TsanFuncExit);
    }
    Res = true;
  }
  return Res;
}