/// rewriteExpensiveInvoke - Insert code and hack the function to replace the
/// specified invoke instruction with a call.
void LowerInvoke::rewriteExpensiveInvoke(InvokeInst *II, unsigned InvokeNo,
                                         AllocaInst *InvokeNum,
                                         SwitchInst *CatchSwitch) {
  ConstantInt *InvokeNoC = ConstantInt::get(Type::getInt32Ty(II->getContext()),
                                            InvokeNo);

  // If the unwind edge has phi nodes, split the edge.
  if (isa<PHINode>(II->getUnwindDest()->begin())) {
    SplitCriticalEdge(II, 1, this);

    // If there are any phi nodes left, they must have a single predecessor.
    while (PHINode *PN = dyn_cast<PHINode>(II->getUnwindDest()->begin())) {
      PN->replaceAllUsesWith(PN->getIncomingValue(0));
      PN->eraseFromParent();
    }
  }

  // Insert a store of the invoke num before the invoke and store zero into the
  // location afterward.
  new StoreInst(InvokeNoC, InvokeNum, true, II);  // volatile

  BasicBlock::iterator NI = II->getNormalDest()->getFirstNonPHI();
  // nonvolatile.
  new StoreInst(Constant::getNullValue(Type::getInt32Ty(II->getContext())), 
                InvokeNum, false, NI);

  // Add a switch case to our unwind block.
  CatchSwitch->addCase(InvokeNoC, II->getUnwindDest());

  // Insert a normal call instruction.
  std::vector<Value*> CallArgs(II->op_begin()+3, II->op_end());
  CallInst *NewCall = CallInst::Create(II->getCalledValue(),
                                       CallArgs.begin(), CallArgs.end(), "",
                                       II);
  NewCall->takeName(II);
  NewCall->setCallingConv(II->getCallingConv());
  NewCall->setAttributes(II->getAttributes());
  II->replaceAllUsesWith(NewCall);

  // Replace the invoke with an uncond branch.
  BranchInst::Create(II->getNormalDest(), NewCall->getParent());
  II->eraseFromParent();
}