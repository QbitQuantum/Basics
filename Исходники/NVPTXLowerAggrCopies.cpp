bool NVPTXLowerAggrCopies::runOnFunction(Function &F) {
  SmallVector<LoadInst *, 4> aggrLoads;
  SmallVector<MemTransferInst *, 4> aggrMemcpys;
  SmallVector<MemSetInst *, 4> aggrMemsets;

  DataLayout *TD = &getAnalysis<DataLayout>();
  LLVMContext &Context = F.getParent()->getContext();

  //
  // Collect all the aggrLoads, aggrMemcpys and addrMemsets.
  //
  //const BasicBlock *firstBB = &F.front();  // first BB in F
  for (Function::iterator BI = F.begin(), BE = F.end(); BI != BE; ++BI) {
    //BasicBlock *bb = BI;
    for (BasicBlock::iterator II = BI->begin(), IE = BI->end(); II != IE;
        ++II) {
      if (LoadInst * load = dyn_cast<LoadInst>(II)) {

        if (load->hasOneUse() == false) continue;

        if (TD->getTypeStoreSize(load->getType()) < MaxAggrCopySize) continue;

        User *use = *(load->use_begin());
        if (StoreInst * store = dyn_cast<StoreInst>(use)) {
          if (store->getOperand(0) != load) //getValueOperand
          continue;
          aggrLoads.push_back(load);
        }
      } else if (MemTransferInst * intr = dyn_cast<MemTransferInst>(II)) {
        Value *len = intr->getLength();
        // If the number of elements being copied is greater
        // than MaxAggrCopySize, lower it to a loop
        if (ConstantInt * len_int = dyn_cast < ConstantInt > (len)) {
          if (len_int->getZExtValue() >= MaxAggrCopySize) {
            aggrMemcpys.push_back(intr);
          }
        } else {
          // turn variable length memcpy/memmov into loop
          aggrMemcpys.push_back(intr);
        }
      } else if (MemSetInst * memsetintr = dyn_cast<MemSetInst>(II)) {
        Value *len = memsetintr->getLength();
        if (ConstantInt * len_int = dyn_cast<ConstantInt>(len)) {
          if (len_int->getZExtValue() >= MaxAggrCopySize) {
            aggrMemsets.push_back(memsetintr);
          }
        } else {
          // turn variable length memset into loop
          aggrMemsets.push_back(memsetintr);
        }
      }
    }
  }
  if ((aggrLoads.size() == 0) && (aggrMemcpys.size() == 0)
      && (aggrMemsets.size() == 0)) return false;

  //
  // Do the transformation of an aggr load/copy/set to a loop
  //
  for (unsigned i = 0, e = aggrLoads.size(); i != e; ++i) {
    LoadInst *load = aggrLoads[i];
    StoreInst *store = dyn_cast<StoreInst>(*load->use_begin());
    Value *srcAddr = load->getOperand(0);
    Value *dstAddr = store->getOperand(1);
    unsigned numLoads = TD->getTypeStoreSize(load->getType());
    Value *len = ConstantInt::get(Type::getInt32Ty(Context), numLoads);

    convertTransferToLoop(store, srcAddr, dstAddr, len, load->isVolatile(),
                          store->isVolatile(), Context, F);

    store->eraseFromParent();
    load->eraseFromParent();
  }

  for (unsigned i = 0, e = aggrMemcpys.size(); i != e; ++i) {
    MemTransferInst *cpy = aggrMemcpys[i];
    Value *len = cpy->getLength();
    // llvm 2.7 version of memcpy does not have volatile
    // operand yet. So always making it non-volatile
    // optimistically, so that we don't see unnecessary
    // st.volatile in ptx
    convertTransferToLoop(cpy, cpy->getSource(), cpy->getDest(), len, false,
                          false, Context, F);
    cpy->eraseFromParent();
  }

  for (unsigned i = 0, e = aggrMemsets.size(); i != e; ++i) {
    MemSetInst *memsetinst = aggrMemsets[i];
    Value *len = memsetinst->getLength();
    Value *val = memsetinst->getValue();
    convertMemSetToLoop(memsetinst, memsetinst->getDest(), len, val, Context,
                        F);
    memsetinst->eraseFromParent();
  }

  return true;
}