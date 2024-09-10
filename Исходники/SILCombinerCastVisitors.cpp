SILInstruction *
SILCombiner::visitUncheckedAddrCastInst(UncheckedAddrCastInst *UADCI) {
  Builder.setCurrentDebugScope(UADCI->getDebugScope());
  SILModule &Mod = UADCI->getModule();

  // (unchecked-addr-cast (unchecked-addr-cast x X->Y) Y->Z)
  //   ->
  // (unchecked-addr-cast x X->Z)
  if (auto *OtherUADCI = dyn_cast<UncheckedAddrCastInst>(UADCI->getOperand()))
    return Builder.createUncheckedAddrCast(UADCI->getLoc(),
                                           OtherUADCI->getOperand(),
                                           UADCI->getType());

  // (unchecked-addr-cast cls->superclass) -> (upcast cls->superclass)
  if (UADCI->getType() != UADCI->getOperand().getType() &&
      UADCI->getType().isSuperclassOf(UADCI->getOperand().getType()))
    return Builder.createUpcast(UADCI->getLoc(), UADCI->getOperand(),
                                UADCI->getType());

  // See if we have all loads from this unchecked_addr_cast. If we do, load the
  // original type and create the appropriate bitcast.

  // First if our UADCI has not users, bail. This will be eliminated by DCE.
  if (UADCI->use_empty())
    return nullptr;

  SILType InputTy = UADCI->getOperand().getType();
  SILType OutputTy = UADCI->getType();

  // If either type is address only, do not do anything here.
  if (InputTy.isAddressOnly(Mod) || OutputTy.isAddressOnly(Mod))
    return nullptr;

  bool InputIsTrivial = InputTy.isTrivial(Mod);
  bool OutputIsTrivial = OutputTy.isTrivial(Mod);

  // If our input is trivial and our output type is not, do not do
  // anything. This is to ensure that we do not change any types reference
  // semantics from trivial -> reference counted.
  if (InputIsTrivial && !OutputIsTrivial)
    return nullptr;

  // Check that the input type can be value cast to the output type.  It is
  // possible to cast the address of a smaller InputType to the address of a
  // larger OutputType (the actual memory object must be large enough to hold
  // both types). However, such address casts cannot be converted to value
  // casts.
  if (!SILType::canUnsafeCastValue(InputTy, OutputTy, UADCI->getModule()))
    return nullptr;

  // For each user U of the unchecked_addr_cast...
  for (auto U : getNonDebugUses(*UADCI))
    // Check if it is load. If it is not a load, bail...
    if (!isa<LoadInst>(U->getUser()))
      return nullptr;

  SILValue Op = UADCI->getOperand();
  SILLocation Loc = UADCI->getLoc();

  // Ok, we have all loads. Lets simplify this. Go back through the loads a
  // second time, rewriting them into a load + bitcast from our source.
  auto UsesRange = getNonDebugUses(*UADCI);
  for (auto UI = UsesRange.begin(), E = UsesRange.end(); UI != E;) {
    // Grab the original load.
    LoadInst *L = cast<LoadInst>(UI->getUser());
    UI++;

    // Insert a new load from our source and bitcast that as appropriate.
    LoadInst *NewLoad = Builder.createLoad(Loc, Op);
    auto *BitCast = Builder.createUncheckedBitCast(Loc, NewLoad,
                                                    OutputTy.getObjectType());
    // Replace all uses of the old load with the new bitcasted result and erase
    // the old load.
    replaceInstUsesWith(*L, BitCast, 0);
    eraseInstFromFunction(*L);
  }

  // Delete the old cast.
  return eraseInstFromFunction(*UADCI);
}