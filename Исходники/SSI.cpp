/// When there is a phi node that is created in a BasicBlock and it is used
/// as an operand of another phi function used in the same BasicBlock,
/// LLVM looks this as an error. So on the second phi, the first phi is called
/// P and the BasicBlock it incomes is B. This P will be replaced by the value
/// it has for BasicBlock B. It also includes undef values for predecessors
/// that were not included in the phi.
///
void SSI::fixPhis() {
  for (SmallPtrSet<PHINode *, 1>::iterator begin = phisToFix.begin(),
       end = phisToFix.end(); begin != end; ++begin) {
    PHINode *PN = *begin;
    for (unsigned i = 0, e = PN->getNumIncomingValues(); i < e; ++i) {
      PHINode *PN_father = dyn_cast<PHINode>(PN->getIncomingValue(i));
      if (PN_father && PN->getParent() == PN_father->getParent() &&
          !DT_->dominates(PN->getParent(), PN->getIncomingBlock(i))) {
        BasicBlock *BB = PN->getIncomingBlock(i);
        int pos = PN_father->getBasicBlockIndex(BB);
        PN->setIncomingValue(i, PN_father->getIncomingValue(pos));
      }
    }
  }

  for (DenseMapIterator<PHINode *, Instruction*> begin = phis.begin(),
       end = phis.end(); begin != end; ++begin) {
    PHINode *PN = begin->first;
    BasicBlock *BB = PN->getParent();
    pred_iterator PI = pred_begin(BB), PE = pred_end(BB);
    SmallVector<BasicBlock*, 8> Preds(PI, PE);
    for (unsigned size = Preds.size();
         PI != PE && PN->getNumIncomingValues() != size; ++PI) {
      bool found = false;
      for (unsigned i = 0, pn_end = PN->getNumIncomingValues();
           i < pn_end; ++i) {
        if (PN->getIncomingBlock(i) == *PI) {
          found = true;
          break;
        }
      }
      if (!found) {
        PN->addIncoming(UndefValue::get(PN->getType()), *PI);
      }
    }
  }
}