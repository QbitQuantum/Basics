/// setupFunctionContext - Allocate the function context on the stack and fill
/// it with all of the data that we know at this point.
Value *SjLjEHPass::
setupFunctionContext(Function &F, ArrayRef<LandingPadInst*> LPads) {
  BasicBlock *EntryBB = F.begin();

  // Create an alloca for the incoming jump buffer ptr and the new jump buffer
  // that needs to be restored on all exits from the function. This is an alloca
  // because the value needs to be added to the global context list.
  unsigned Align =
    TLI->getTargetData()->getPrefTypeAlignment(FunctionContextTy);
  FuncCtx =
    new AllocaInst(FunctionContextTy, 0, Align, "fn_context", EntryBB->begin());

  // Fill in the function context structure.
  Type *Int32Ty = Type::getInt32Ty(F.getContext());
  Value *Zero = ConstantInt::get(Int32Ty, 0);
  Value *One = ConstantInt::get(Int32Ty, 1);
  Value *Two = ConstantInt::get(Int32Ty, 2);
  Value *Three = ConstantInt::get(Int32Ty, 3);
  Value *Four = ConstantInt::get(Int32Ty, 4);

  Value *Idxs[2] = { Zero, 0 };

  for (unsigned I = 0, E = LPads.size(); I != E; ++I) {
    LandingPadInst *LPI = LPads[I];
    IRBuilder<> Builder(LPI->getParent()->getFirstInsertionPt());

    // Reference the __data field.
    Idxs[1] = Two;
    Value *FCData = Builder.CreateGEP(FuncCtx, Idxs, "__data");

    // The exception values come back in context->__data[0].
    Idxs[1] = Zero;
    Value *ExceptionAddr = Builder.CreateGEP(FCData, Idxs, "exception_gep");
    Value *ExnVal = Builder.CreateLoad(ExceptionAddr, true, "exn_val");
    ExnVal = Builder.CreateIntToPtr(ExnVal, Type::getInt8PtrTy(F.getContext()));

    Idxs[1] = One;
    Value *SelectorAddr = Builder.CreateGEP(FCData, Idxs, "exn_selector_gep");
    Value *SelVal = Builder.CreateLoad(SelectorAddr, true, "exn_selector_val");

    substituteLPadValues(LPI, ExnVal, SelVal);
  }

  // Personality function
  Idxs[1] = Three;
  if (!PersonalityFn)
    PersonalityFn = LPads[0]->getPersonalityFn();
  Value *PersonalityFieldPtr =
    GetElementPtrInst::Create(FuncCtx, Idxs, "pers_fn_gep",
                              EntryBB->getTerminator());
  new StoreInst(PersonalityFn, PersonalityFieldPtr, true,
                EntryBB->getTerminator());

  // LSDA address
  Value *LSDA = CallInst::Create(LSDAAddrFn, "lsda_addr",
                                 EntryBB->getTerminator());
  Idxs[1] = Four;
  Value *LSDAFieldPtr = GetElementPtrInst::Create(FuncCtx, Idxs, "lsda_gep",
                                                  EntryBB->getTerminator());
  new StoreInst(LSDA, LSDAFieldPtr, true, EntryBB->getTerminator());

  return FuncCtx;
}