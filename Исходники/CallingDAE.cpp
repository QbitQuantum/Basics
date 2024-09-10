void insertCallToAccessFunctionSequential(Function *F, Function *cF) {
  CallInst *I;
  BasicBlock *b;

  Value::user_iterator i = F->user_begin(), e = F->user_end();
  while (i != e) {
    if (isa<CallInst>(*i)) {

      I = dyn_cast<CallInst>(*i);
      b = I->getParent();
      BasicBlock::iterator helper(I);
      CallInst *ci = dyn_cast<CallInst>(I->clone());
      ci->setCalledFunction(cF);
      b->getInstList().insertAfter(helper, ci);

      i++;
      I->replaceAllUsesWith(ci);

      insertCallToPAPI(I, ci);
    }
  }
}