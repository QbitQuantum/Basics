void HexagonVectorLoopCarriedReuse::findValueToReuse() {
  for (auto *D : Dependences) {
    LLVM_DEBUG(dbgs() << "Processing dependence " << *(D->front()) << "\n");
    if (D->iterations() > HexagonVLCRIterationLim) {
      LLVM_DEBUG(
          dbgs()
          << ".. Skipping because number of iterations > than the limit\n");
      continue;
    }

    PHINode *PN = cast<PHINode>(D->front());
    Instruction *BEInst = D->back();
    int Iters = D->iterations();
    BasicBlock *BB = PN->getParent();
    LLVM_DEBUG(dbgs() << "Checking if any uses of " << *PN
                      << " can be reused\n");

    SmallVector<Instruction *, 4> PNUsers;
    for (auto UI = PN->use_begin(), E = PN->use_end(); UI != E; ++UI) {
      Use &U = *UI;
      Instruction *User = cast<Instruction>(U.getUser());

      if (User->getParent() != BB)
        continue;
      if (ReplacedInsts.count(User)) {
        LLVM_DEBUG(dbgs() << *User
                          << " has already been replaced. Skipping...\n");
        continue;
      }
      if (isa<PHINode>(User))
        continue;
      if (User->mayHaveSideEffects())
        continue;
      if (!canReplace(User))
        continue;

      PNUsers.push_back(User);
    }
    LLVM_DEBUG(dbgs() << PNUsers.size() << " use(s) of the PHI in the block\n");

    // For each interesting use I of PN, find an Instruction BEUser that
    // performs the same operation as I on BEInst and whose other operands,
    // if any, can also be rematerialized in OtherBB. We stop when we find the
    // first such Instruction BEUser. This is because once BEUser is
    // rematerialized in OtherBB, we may find more such "fixup" opportunities
    // in this block. So, we'll start over again.
    for (Instruction *I : PNUsers) {
      for (auto UI = BEInst->use_begin(), E = BEInst->use_end(); UI != E;
           ++UI) {
        Use &U = *UI;
        Instruction *BEUser = cast<Instruction>(U.getUser());

        if (BEUser->getParent() != BB)
          continue;
        if (!isEquivalentOperation(I, BEUser))
          continue;

        int NumOperands = I->getNumOperands();

        for (int OpNo = 0; OpNo < NumOperands; ++OpNo) {
          Value *Op = I->getOperand(OpNo);
          Instruction *OpInst = dyn_cast<Instruction>(Op);
          if (!OpInst)
            continue;

          Value *BEOp = BEUser->getOperand(OpNo);
          Instruction *BEOpInst = dyn_cast<Instruction>(BEOp);

          if (!isDepChainBtwn(OpInst, BEOpInst, Iters)) {
            BEUser = nullptr;
            break;
          }
        }
        if (BEUser) {
          LLVM_DEBUG(dbgs() << "Found Value for reuse.\n");
          ReuseCandidate.Inst2Replace = I;
          ReuseCandidate.BackedgeInst = BEUser;
          return;
        } else
          ReuseCandidate.reset();
      }
    }
  }
  ReuseCandidate.reset();
}