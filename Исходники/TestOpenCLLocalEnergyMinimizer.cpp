void testHarmonicBonds() {
    const int numParticles = 10;
    System system;
    HarmonicBondForce* bonds = new HarmonicBondForce();
    system.addForce(bonds);

    // Create a chain of particles connected by harmonic bonds.

    vector<Vec3> positions(numParticles);
    for (int i = 0; i < numParticles; i++) {
        system.addParticle(1.0);
        positions[i] = Vec3(i, 0, 0);
        if (i > 0)
            bonds->addBond(i-1, i, 1+0.1*i, 1);
    }

    // Minimize it and check that all bonds are at their equilibrium distances.

    VerletIntegrator integrator(0.01);
    Context context(system, integrator, platform);
    context.setPositions(positions);
    LocalEnergyMinimizer::minimize(context, 1e-5);
    State state = context.getState(State::Positions);
    for (int i = 1; i < numParticles; i++) {
        Vec3 delta = state.getPositions()[i]-state.getPositions()[i-1];
        ASSERT_EQUAL_TOL(1+0.1*i, sqrt(delta.dot(delta)), 1e-4);
    }
}