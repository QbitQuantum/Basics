static void
updateSSA(SILModule &M, SILLoop *Loop,
          DenseMap<SILValue, SmallVector<SILValue, 8>> &LoopLiveOutValues) {
  SILSSAUpdater SSAUp;
  for (auto &MapEntry : LoopLiveOutValues) {
    // Collect out of loop uses of this value.
    auto OrigValue = MapEntry.first;
    SmallVector<UseWrapper, 16> UseList;
    for (auto Use : OrigValue->getUses())
      if (!Loop->contains(Use->getUser()->getParent()))
        UseList.push_back(UseWrapper(Use));
    // Update SSA of use with the available values.
    SSAUp.Initialize(OrigValue->getType());
    SSAUp.AddAvailableValue(OrigValue->getParentBlock(), OrigValue);
    for (auto NewValue : MapEntry.second)
      SSAUp.AddAvailableValue(NewValue->getParentBlock(), NewValue);
    for (auto U : UseList) {
      Operand *Use = U;
      SSAUp.RewriteUse(*Use);
    }
  }
}