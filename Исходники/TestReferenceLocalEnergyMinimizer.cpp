void testLargeSystem() {
    const int numMolecules = 50;
    const int numParticles = numMolecules*2;
    const double cutoff = 2.0;
    const double boxSize = 5.0;
    const double tolerance = 5;
    System system;
    system.setDefaultPeriodicBoxVectors(Vec3(boxSize, 0, 0), Vec3(0, boxSize, 0), Vec3(0, 0, boxSize));
    NonbondedForce* nonbonded = new NonbondedForce();
    nonbonded->setCutoffDistance(cutoff);
    nonbonded->setNonbondedMethod(NonbondedForce::CutoffPeriodic);
    system.addForce(nonbonded);

    // Create a cloud of molecules.

    OpenMM_SFMT::SFMT sfmt;
    init_gen_rand(0, sfmt);
    vector<Vec3> positions(numParticles);
    for (int i = 0; i < numMolecules; i++) {
        system.addParticle(1.0);
        system.addParticle(1.0);
        nonbonded->addParticle(-1.0, 0.2, 0.2);
        nonbonded->addParticle(1.0, 0.2, 0.2);
        positions[2*i] = Vec3(boxSize*genrand_real2(sfmt), boxSize*genrand_real2(sfmt), boxSize*genrand_real2(sfmt));
        positions[2*i+1] = Vec3(positions[2*i][0]+1.0, positions[2*i][1], positions[2*i][2]);
        system.addConstraint(2*i, 2*i+1, 1.0);
    }

    // Minimize it and verify that the energy has decreased.
    
    ReferencePlatform platform;
    VerletIntegrator integrator(0.01);
    Context context(system, integrator, platform);
    context.setPositions(positions);
    State initialState = context.getState(State::Forces | State::Energy);
    LocalEnergyMinimizer::minimize(context, tolerance);
    State finalState = context.getState(State::Forces | State::Energy | State::Positions);
    ASSERT(finalState.getPotentialEnergy() < initialState.getPotentialEnergy());

    // Compute the force magnitude, subtracting off any component parallel to a constraint, and
    // check that it satisfies the requested tolerance.

    double forceNorm = 0.0;
    for (int i = 0; i < numParticles; i += 2) {
        Vec3 dir = finalState.getPositions()[i+1]-finalState.getPositions()[i];
        double distance = sqrt(dir.dot(dir));
        dir *= 1.0/distance;
        Vec3 f = finalState.getForces()[i];
        f -= dir*dir.dot(f);
        forceNorm += f.dot(f);
        f = finalState.getForces()[i+1];
        f -= dir*dir.dot(f);
        forceNorm += f.dot(f);
    }
    forceNorm = sqrt(forceNorm/(4*numMolecules));
    ASSERT(forceNorm < 3*tolerance);
}