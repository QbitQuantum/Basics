/// \brief Lower copy_addr into loads/stores/retain/release if we have a
/// non-address only type. We do this here so we can process the resulting
/// loads/stores.
///
/// This peephole implements the following optimizations:
///
/// copy_addr %0 to %1 : $*T
/// ->
///     %new = load %0 : $*T        // Load the new value from the source
///     %old = load %1 : $*T        // Load the old value from the destination
///     strong_retain %new : $T     // Retain the new value
///     strong_release %old : $T    // Release the old
///     store %new to %1 : $*T      // Store the new value to the destination
///
/// copy_addr [take] %0 to %1 : $*T
/// ->
///     %new = load %0 : $*T
///     %old = load %1 : $*T
///     // no retain of %new!
///     strong_release %old : $T
///     store %new to %1 : $*T
///
/// copy_addr %0 to [initialization] %1 : $*T
/// ->
///     %new = load %0 : $*T
///     strong_retain %new : $T
///     // no load/release of %old!
///     store %new to %1 : $*T
///
/// copy_addr [take] %0 to [initialization] %1 : $*T
/// ->
///     %new = load %0 : $*T
///     // no retain of %new!
///     // no load/release of %old!
///     store %new to %1 : $*T
static bool expandCopyAddr(CopyAddrInst *CA) {
  SILModule &M = CA->getModule();
  SILValue Source = CA->getSrc();

  // If we have an address only type don't do anything.
  SILType SrcType = Source->getType();
  if (SrcType.isAddressOnly(M))
    return false;

  bool expand = shouldExpand(M, SrcType.getObjectType());

  SILBuilderWithScope Builder(CA);

  // %new = load %0 : $*T
  LoadInst *New = Builder.createLoad(CA->getLoc(), Source,
                                     LoadOwnershipQualifier::Unqualified);

  SILValue Destination = CA->getDest();

  // If our object type is not trivial, we may need to release the old value and
  // retain the new one.

  auto &TL = M.getTypeLowering(SrcType);

  // If we have a non-trivial type...
  if (!TL.isTrivial()) {

    // If we are not initializing:
    // %old = load %1 : $*T
    IsInitialization_t IsInit = CA->isInitializationOfDest();
    LoadInst *Old = nullptr;
    if (IsInitialization_t::IsNotInitialization == IsInit) {
      Old = Builder.createLoad(CA->getLoc(), Destination,
                               LoadOwnershipQualifier::Unqualified);
    }

    // If we are not taking and have a reference type:
    //   strong_retain %new : $*T
    // or if we have a non-trivial non-reference type.
    //   retain_value %new : $*T
    IsTake_t IsTake = CA->isTakeOfSrc();
    if (IsTake_t::IsNotTake == IsTake) {
      TL.emitLoweredCopyValue(Builder, CA->getLoc(), New,
                              TypeLowering::getLoweringStyle(expand));
    }

    // If we are not initializing:
    // strong_release %old : $*T
    //   *or*
    // release_value %old : $*T
    if (Old) {
      TL.emitLoweredDestroyValue(Builder, CA->getLoc(), Old,
                                 TypeLowering::getLoweringStyle(expand));
    }
  }

  // Create the store.
  Builder.createStore(CA->getLoc(), New, Destination,
                      StoreOwnershipQualifier::Unqualified);

  ++NumExpand;
  return true;
}