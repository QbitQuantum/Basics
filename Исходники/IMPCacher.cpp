CallSite GNUstep::IMPCacher::SplitSend(CallSite msgSend)
{
    BasicBlock *lookupBB = msgSend->getParent();
    Function *F = lookupBB->getParent();
    Module *M = F->getParent();
    Function *send = M->getFunction("objc_msgSend");
    Function *send_stret = M->getFunction("objc_msgSend_stret");
    Function *send_fpret = M->getFunction("objc_msgSend_fpret");
    Value *self;
    Value *cmd;
    int selfIndex = 0;
    if ((msgSend.getCalledFunction() == send) ||
            (msgSend.getCalledFunction() == send_fpret)) {
        self = msgSend.getArgument(0);
        cmd = msgSend.getArgument(1);
    } else if (msgSend.getCalledFunction() == send_stret) {
        selfIndex = 1;
        self = msgSend.getArgument(1);
        cmd = msgSend.getArgument(2);
    } else {
        abort();
        return CallSite();
    }
    CGBuilder B(&F->getEntryBlock(), F->getEntryBlock().begin());
    Value *selfPtr = B.CreateAlloca(self->getType());
    B.SetInsertPoint(msgSend.getInstruction());
    B.CreateStore(self, selfPtr, true);
    LLVMType *impTy = msgSend.getCalledValue()->getType();
    LLVMType *slotTy = PointerType::getUnqual(StructType::get(PtrTy, PtrTy, PtrTy,
                       IntTy, impTy, PtrTy, NULL));
    Value *slot;
    Constant *lookupFn = M->getOrInsertFunction("objc_msg_lookup_sender",
                         slotTy, selfPtr->getType(), cmd->getType(), PtrTy, NULL);
    if (msgSend.isCall()) {
        slot = B.CreateCall3(lookupFn, selfPtr, cmd, Constant::getNullValue(PtrTy));
    } else {
        InvokeInst *inv = cast<InvokeInst>(msgSend.getInstruction());
        BasicBlock *callBB = SplitBlock(lookupBB, msgSend.getInstruction(), Owner);
        removeTerminator(lookupBB);
        B.SetInsertPoint(lookupBB);
        slot = B.CreateInvoke3(lookupFn, callBB, inv->getUnwindDest(), selfPtr, cmd,
                               Constant::getNullValue(PtrTy));
        addPredecssor(inv->getUnwindDest(), msgSend->getParent(), lookupBB);
        B.SetInsertPoint(msgSend.getInstruction());
    }
    Value *imp = B.CreateLoad(B.CreateStructGEP(slot, 4));
    msgSend.setArgument(selfIndex, B.CreateLoad(selfPtr, true));
    msgSend.setCalledFunction(imp);
    return CallSite(slot);
}