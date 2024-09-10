void AAEvaluator::runInternal(Function &F, AAResults &AA) {
  const DataLayout &DL = F.getParent()->getDataLayout();

  ++FunctionCount;

  SetVector<Value *> Pointers;
  SmallSetVector<CallBase *, 16> Calls;
  SetVector<Value *> Loads;
  SetVector<Value *> Stores;

  for (auto &I : F.args())
    if (I.getType()->isPointerTy())    // Add all pointer arguments.
      Pointers.insert(&I);

  for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
    if (I->getType()->isPointerTy()) // Add all pointer instructions.
      Pointers.insert(&*I);
    if (EvalAAMD && isa<LoadInst>(&*I))
      Loads.insert(&*I);
    if (EvalAAMD && isa<StoreInst>(&*I))
      Stores.insert(&*I);
    Instruction &Inst = *I;
    if (auto *Call = dyn_cast<CallBase>(&Inst)) {
      Value *Callee = Call->getCalledValue();
      // Skip actual functions for direct function calls.
      if (!isa<Function>(Callee) && isInterestingPointer(Callee))
        Pointers.insert(Callee);
      // Consider formals.
      for (Use &DataOp : Call->data_ops())
        if (isInterestingPointer(DataOp))
          Pointers.insert(DataOp);
      Calls.insert(Call);
    } else {
      // Consider all operands.
      for (Instruction::op_iterator OI = Inst.op_begin(), OE = Inst.op_end();
           OI != OE; ++OI)
        if (isInterestingPointer(*OI))
          Pointers.insert(*OI);
    }
  }

  if (PrintAll || PrintNoAlias || PrintMayAlias || PrintPartialAlias ||
      PrintMustAlias || PrintNoModRef || PrintMod || PrintRef || PrintModRef)
    errs() << "Function: " << F.getName() << ": " << Pointers.size()
           << " pointers, " << Calls.size() << " call sites\n";

  // iterate over the worklist, and run the full (n^2)/2 disambiguations
  for (SetVector<Value *>::iterator I1 = Pointers.begin(), E = Pointers.end();
       I1 != E; ++I1) {
    auto I1Size = LocationSize::unknown();
    Type *I1ElTy = cast<PointerType>((*I1)->getType())->getElementType();
    if (I1ElTy->isSized())
      I1Size = LocationSize::precise(DL.getTypeStoreSize(I1ElTy));

    for (SetVector<Value *>::iterator I2 = Pointers.begin(); I2 != I1; ++I2) {
      auto I2Size = LocationSize::unknown();
      Type *I2ElTy = cast<PointerType>((*I2)->getType())->getElementType();
      if (I2ElTy->isSized())
        I2Size = LocationSize::precise(DL.getTypeStoreSize(I2ElTy));

      AliasResult AR = AA.alias(*I1, I1Size, *I2, I2Size);
      switch (AR) {
      case NoAlias:
        PrintResults(AR, PrintNoAlias, *I1, *I2, F.getParent());
        ++NoAliasCount;
        break;
      case MayAlias:
        PrintResults(AR, PrintMayAlias, *I1, *I2, F.getParent());
        ++MayAliasCount;
        break;
      case PartialAlias:
        PrintResults(AR, PrintPartialAlias, *I1, *I2, F.getParent());
        ++PartialAliasCount;
        break;
      case MustAlias:
        PrintResults(AR, PrintMustAlias, *I1, *I2, F.getParent());
        ++MustAliasCount;
        break;
      }
    }
  }

  if (EvalAAMD) {
    // iterate over all pairs of load, store
    for (Value *Load : Loads) {
      for (Value *Store : Stores) {
        AliasResult AR = AA.alias(MemoryLocation::get(cast<LoadInst>(Load)),
                                  MemoryLocation::get(cast<StoreInst>(Store)));
        switch (AR) {
        case NoAlias:
          PrintLoadStoreResults(AR, PrintNoAlias, Load, Store, F.getParent());
          ++NoAliasCount;
          break;
        case MayAlias:
          PrintLoadStoreResults(AR, PrintMayAlias, Load, Store, F.getParent());
          ++MayAliasCount;
          break;
        case PartialAlias:
          PrintLoadStoreResults(AR, PrintPartialAlias, Load, Store, F.getParent());
          ++PartialAliasCount;
          break;
        case MustAlias:
          PrintLoadStoreResults(AR, PrintMustAlias, Load, Store, F.getParent());
          ++MustAliasCount;
          break;
        }
      }
    }

    // iterate over all pairs of store, store
    for (SetVector<Value *>::iterator I1 = Stores.begin(), E = Stores.end();
         I1 != E; ++I1) {
      for (SetVector<Value *>::iterator I2 = Stores.begin(); I2 != I1; ++I2) {
        AliasResult AR = AA.alias(MemoryLocation::get(cast<StoreInst>(*I1)),
                                  MemoryLocation::get(cast<StoreInst>(*I2)));
        switch (AR) {
        case NoAlias:
          PrintLoadStoreResults(AR, PrintNoAlias, *I1, *I2, F.getParent());
          ++NoAliasCount;
          break;
        case MayAlias:
          PrintLoadStoreResults(AR, PrintMayAlias, *I1, *I2, F.getParent());
          ++MayAliasCount;
          break;
        case PartialAlias:
          PrintLoadStoreResults(AR, PrintPartialAlias, *I1, *I2, F.getParent());
          ++PartialAliasCount;
          break;
        case MustAlias:
          PrintLoadStoreResults(AR, PrintMustAlias, *I1, *I2, F.getParent());
          ++MustAliasCount;
          break;
        }
      }
    }
  }

  // Mod/ref alias analysis: compare all pairs of calls and values
  for (CallBase *Call : Calls) {
    for (auto Pointer : Pointers) {
      auto Size = LocationSize::unknown();
      Type *ElTy = cast<PointerType>(Pointer->getType())->getElementType();
      if (ElTy->isSized())
        Size = LocationSize::precise(DL.getTypeStoreSize(ElTy));

      switch (AA.getModRefInfo(Call, Pointer, Size)) {
      case ModRefInfo::NoModRef:
        PrintModRefResults("NoModRef", PrintNoModRef, Call, Pointer,
                           F.getParent());
        ++NoModRefCount;
        break;
      case ModRefInfo::Mod:
        PrintModRefResults("Just Mod", PrintMod, Call, Pointer, F.getParent());
        ++ModCount;
        break;
      case ModRefInfo::Ref:
        PrintModRefResults("Just Ref", PrintRef, Call, Pointer, F.getParent());
        ++RefCount;
        break;
      case ModRefInfo::ModRef:
        PrintModRefResults("Both ModRef", PrintModRef, Call, Pointer,
                           F.getParent());
        ++ModRefCount;
        break;
      case ModRefInfo::Must:
        PrintModRefResults("Must", PrintMust, Call, Pointer, F.getParent());
        ++MustCount;
        break;
      case ModRefInfo::MustMod:
        PrintModRefResults("Just Mod (MustAlias)", PrintMustMod, Call, Pointer,
                           F.getParent());
        ++MustModCount;
        break;
      case ModRefInfo::MustRef:
        PrintModRefResults("Just Ref (MustAlias)", PrintMustRef, Call, Pointer,
                           F.getParent());
        ++MustRefCount;
        break;
      case ModRefInfo::MustModRef:
        PrintModRefResults("Both ModRef (MustAlias)", PrintMustModRef, Call,
                           Pointer, F.getParent());
        ++MustModRefCount;
        break;
      }
    }
  }

  // Mod/ref alias analysis: compare all pairs of calls
  for (CallBase *CallA : Calls) {
    for (CallBase *CallB : Calls) {
      if (CallA == CallB)
        continue;
      switch (AA.getModRefInfo(CallA, CallB)) {
      case ModRefInfo::NoModRef:
        PrintModRefResults("NoModRef", PrintNoModRef, CallA, CallB,
                           F.getParent());
        ++NoModRefCount;
        break;
      case ModRefInfo::Mod:
        PrintModRefResults("Just Mod", PrintMod, CallA, CallB, F.getParent());
        ++ModCount;
        break;
      case ModRefInfo::Ref:
        PrintModRefResults("Just Ref", PrintRef, CallA, CallB, F.getParent());
        ++RefCount;
        break;
      case ModRefInfo::ModRef:
        PrintModRefResults("Both ModRef", PrintModRef, CallA, CallB,
                           F.getParent());
        ++ModRefCount;
        break;
      case ModRefInfo::Must:
        PrintModRefResults("Must", PrintMust, CallA, CallB, F.getParent());
        ++MustCount;
        break;
      case ModRefInfo::MustMod:
        PrintModRefResults("Just Mod (MustAlias)", PrintMustMod, CallA, CallB,
                           F.getParent());
        ++MustModCount;
        break;
      case ModRefInfo::MustRef:
        PrintModRefResults("Just Ref (MustAlias)", PrintMustRef, CallA, CallB,
                           F.getParent());
        ++MustRefCount;
        break;
      case ModRefInfo::MustModRef:
        PrintModRefResults("Both ModRef (MustAlias)", PrintMustModRef, CallA,
                           CallB, F.getParent());
        ++MustModRefCount;
        break;
      }
    }
  }
}