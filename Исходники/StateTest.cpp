void testCacheValidity() {
    const SubsystemIndex Sub0(0), Sub1(1);
    State s;
    s.setNumSubsystems(2);

    // Allocate a Model stage-invalidating state variable.
    const DiscreteVariableIndex dvxModel = s.allocateDiscreteVariable(Sub1, Stage::Model, new Value<Real>(2));

    // This cache entry depends on Model stage state and is guaranteed to be valid at Time stage.
    // In between (at Model or Instance stage) it *may* be valid if explicitly marked so.
    const CacheEntryIndex cx = s.allocateCacheEntry(Sub0, 
        Stage::Model, Stage::Time, new Value<int>(41));

    // "realize" Topology stage
    s.advanceSubsystemToStage(Sub0, Stage::Topology);
    s.advanceSubsystemToStage(Sub1, Stage::Topology);
    s.advanceSystemToStage(Stage::Topology);

    // Shouldn't be able to access cache entry here because this is less than its
    // "depends on" stage.
    SimTK_TEST_MUST_THROW(s.getCacheEntry(Sub0, cx));


    // "realize" Model stage
    s.advanceSubsystemToStage(Sub0, Stage::Model);
    s.advanceSubsystemToStage(Sub1, Stage::Model);
    s.advanceSystemToStage(Stage::Model);

    // "realize" Instance stage
    s.advanceSubsystemToStage(Sub0, Stage::Instance);
    s.advanceSubsystemToStage(Sub1, Stage::Instance);
    s.advanceSystemToStage(Stage::Instance);

    // Although the cache entry *could* be valid at this point,
    // no one has said so, so we expect it to throw.
    SimTK_TEST_MUST_THROW(s.getCacheEntry(Sub0, cx));

    // If we say it is valid, we should be able to obtain its value.
    s.markCacheValueRealized(Sub0, cx);
    SimTK_TEST(Value<int>::downcast(s.getCacheEntry(Sub0, cx)) == 41);

    // Now modify a Model-stage state variable and realize again. This
    // shoudl have invalidated the cache entry.
    Value<Real>::updDowncast(s.updDiscreteVariable(Sub1, dvxModel)) = 9;
    // "realize" Model stage
    s.advanceSubsystemToStage(Sub0, Stage::Model);
    s.advanceSubsystemToStage(Sub1, Stage::Model);
    s.advanceSystemToStage(Stage::Model);

    SimTK_TEST(!s.isCacheValueRealized(Sub0, cx));

    SimTK_TEST_MUST_THROW(s.getCacheEntry(Sub0, cx));

    // "calculate" the cache entry and mark it valid.
    Value<int>::updDowncast(s.updCacheEntry(Sub0,cx)) = 
        (int)(2 * Value<Real>::downcast(s.getDiscreteVariable(Sub1, dvxModel)));
    s.markCacheValueRealized(Sub0, cx);

    SimTK_TEST(Value<int>::downcast(s.getCacheEntry(Sub0, cx)) == 18);

    // Now modify the Model-stage variable again, but realize through
    // Time stage. We should be able to access the cache entry without
    // explicitly marking it valid.
    Value<Real>::updDowncast(s.updDiscreteVariable(Sub1, dvxModel)) = -100;
    s.advanceSubsystemToStage(Sub0, Stage::Model);
    s.advanceSubsystemToStage(Sub1, Stage::Model);
    s.advanceSystemToStage(Stage::Model);
    s.advanceSubsystemToStage(Sub0, Stage::Instance);
    s.advanceSubsystemToStage(Sub1, Stage::Instance);
    s.advanceSystemToStage(Stage::Instance);
    s.advanceSubsystemToStage(Sub0, Stage::Time);
    s.advanceSubsystemToStage(Sub1, Stage::Time);
    s.advanceSystemToStage(Stage::Time);

    SimTK_TEST(Value<int>::downcast(s.getCacheEntry(Sub0, cx)) == 18);

}