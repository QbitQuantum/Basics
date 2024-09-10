Real HuntCrossleyContactRep::calcPotentialEnergy(const State& state) const {
    return Value<Real>::downcast(state.getCacheEntry(getMySubsystemIndex(), energyCacheIndex)).get();
}