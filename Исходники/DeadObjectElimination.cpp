// At each release point, release the reaching values that have been stored to
// this address.
//
// The caller has already determined that all Stores are to the same element
// within an otherwise dead object.
static void insertReleases(ArrayRef<StoreInst*> Stores,
                           ArrayRef<SILInstruction*> ReleasePoints,
                           SILSSAUpdater &SSAUp) {
  assert(!Stores.empty());
  SILValue StVal = Stores.front()->getSrc();

  SSAUp.Initialize(StVal->getType());

  for (auto *Store : Stores)
    SSAUp.AddAvailableValue(Store->getParent(), Store->getSrc());

  SILLocation Loc = Stores[0]->getLoc();
  for (auto *RelPoint : ReleasePoints) {
    SILBuilder B(RelPoint);
    // This does not use the SSAUpdater::RewriteUse API because it does not do
    // the right thing for local uses. We have already ensured a single store
    // per block, and all release points occur after all stores. Therefore we
    // can simply ask SSAUpdater for the reaching store.
    SILValue RelVal = SSAUp.GetValueAtEndOfBlock(RelPoint->getParent());
    if (StVal->getType().isReferenceCounted(RelPoint->getModule()))
      B.createStrongRelease(Loc, RelVal, Atomicity::Atomic);
    else
      B.createReleaseValue(Loc, RelVal, Atomicity::Atomic);
  }
}