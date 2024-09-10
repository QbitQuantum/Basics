    int realizeSubsystemDynamicsImpl(const State& s) const override {
        const MultibodySystem&        mbs    = getMultibodySystem();
        const SimbodyMatterSubsystem& matter = mbs.getMatterSubsystem();

        // Get access to the discrete state variable that records whether each
        // force element is enabled.
        const Array_<bool>& forceEnabled = Value< Array_<bool> >::downcast
                                    (getDiscreteVariable(s, forceEnabledIndex));
        const Array_<Force*>& enabledNonParallelForces = Value<Array_<Force*>>::
                      downcast(getCacheEntry(s, enabledNonParallelForcesIndex));
        const Array_<Force*>& enabledParallelForces = Value<Array_<Force*>>::
                         downcast(getCacheEntry(s, enabledParallelForcesIndex));

        // Get access to System-global force cache arrays.
        Vector_<SpatialVec>&   rigidBodyForces =
                                    mbs.updRigidBodyForces(s, Stage::Dynamics);
        Vector_<Vec3>&         particleForces  =
                                    mbs.updParticleForces (s, Stage::Dynamics);
        Vector&                mobilityForces  =
                                    mbs.updMobilityForces (s, Stage::Dynamics);

        // Short circuit if we're not doing any caching here. Note that we're
        // checking whether the *index* is valid (i.e. does the cache entry
        // exist?), not the contents.
        if (!cachedForcesAreValidCacheIndex.isValid()) {
            // Call calcForce() on all Forces, in parallel.
            calcForcesTask->initializeAll(s,
                    enabledNonParallelForces, enabledParallelForces,
                    rigidBodyForces, particleForces, mobilityForces);
            calcForcesExecutor->execute(calcForcesTask.updRef(),
                          enabledParallelForces.size() + NumNonParallelThreads);

            // Allow forces to do their own realization, but wait until all
            // forces have executed calcForce(). TODO: not sure if that is
            // necessary (sherm 20130716).
            for (int i = 0; i < (int)forces.size(); ++i)
                if (forceEnabled[i])
                    forces[i]->getImpl().realizeDynamics(s);
            return 0;
        }

        // OK, we're doing some caching. This is a little messier.
        // Get access to subsystem force cache entries.
        bool& cachedForcesAreValid = Value<bool>::updDowncast
                          (updCacheEntry(s, cachedForcesAreValidCacheIndex));

        Vector_<SpatialVec>&
            rigidBodyForceCache = Value<Vector_<SpatialVec> >::updDowncast
                                 (updCacheEntry(s, rigidBodyForceCacheIndex));
        Vector_<Vec3>&
            particleForceCache  = Value<Vector_<Vec3> >::updDowncast
                                 (updCacheEntry(s, particleForceCacheIndex));
        Vector&
            mobilityForceCache  = Value<Vector>::updDowncast
                                 (updCacheEntry(s, mobilityForceCacheIndex));


        if (!cachedForcesAreValid) {
            // We need to calculate the velocity independent forces.
            rigidBodyForceCache.resize(matter.getNumBodies());
            rigidBodyForceCache = SpatialVec(Vec3(0), Vec3(0));
            particleForceCache.resize(matter.getNumParticles());
            particleForceCache = Vec3(0);
            mobilityForceCache.resize(matter.getNumMobilities());
            mobilityForceCache = 0;

            // Run through all the forces, accumulating directly into the
            // force arrays or indirectly into the cache as appropriate.
            calcForcesTask->initializeCachedAndNonCached(s,
                                enabledNonParallelForces, enabledParallelForces,
                                rigidBodyForces, particleForces, mobilityForces,
                                rigidBodyForceCache, particleForceCache,
                                mobilityForceCache);
            calcForcesExecutor->execute(calcForcesTask.updRef(),
                          enabledParallelForces.size() + NumNonParallelThreads);
            cachedForcesAreValid = true;
        } else {
            // Cache already valid; just need to do the non-cached ones (the
            // ones for which dependsOnlyOnPositions is false).
            calcForcesTask->initializeNonCached(s,
                               enabledNonParallelForces, enabledParallelForces,
                               rigidBodyForces, particleForces, mobilityForces);
            calcForcesExecutor->execute(calcForcesTask.updRef(),
                          enabledParallelForces.size() + NumNonParallelThreads);
        }

        // Accumulate the values from the cache into the global arrays.
        rigidBodyForces += rigidBodyForceCache;
        particleForces += particleForceCache;
        mobilityForces += mobilityForceCache;

        // Allow forces to do their own Dynamics-stage realization. Note that
        // this *follows* all the calcForce() calls.
        for (int i = 0; i < (int) forces.size(); ++i)
            if (forceEnabled[i]) forces[i]->getImpl().realizeDynamics(s);
        return 0;
    }