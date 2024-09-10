void testOBC(GBSAOBCForce::NonbondedMethod obcMethod, CustomGBForce::NonbondedMethod customMethod) {
    const int numMolecules = 70;
    const int numParticles = numMolecules*2;
    const double boxSize = 10.0;
    const double cutoff = 2.0;
    ReferencePlatform platform;

    // Create two systems: one with a GBSAOBCForce, and one using a CustomGBForce to implement the same interaction.

    System standardSystem;
    System customSystem;
    for (int i = 0; i < numParticles; i++) {
        standardSystem.addParticle(1.0);
        customSystem.addParticle(1.0);
    }
    standardSystem.setDefaultPeriodicBoxVectors(Vec3(boxSize, 0.0, 0.0), Vec3(0.0, boxSize, 0.0), Vec3(0.0, 0.0, boxSize));
    customSystem.setDefaultPeriodicBoxVectors(Vec3(boxSize, 0.0, 0.0), Vec3(0.0, boxSize, 0.0), Vec3(0.0, 0.0, boxSize));
    GBSAOBCForce* obc = new GBSAOBCForce();
    CustomGBForce* custom = new CustomGBForce();
    obc->setCutoffDistance(cutoff);
    custom->setCutoffDistance(cutoff);
    custom->addPerParticleParameter("q");
    custom->addPerParticleParameter("radius");
    custom->addPerParticleParameter("scale");
    custom->addGlobalParameter("solventDielectric", obc->getSolventDielectric());
    custom->addGlobalParameter("soluteDielectric", obc->getSoluteDielectric());
    custom->addComputedValue("I", "step(r+sr2-or1)*0.5*(1/L-1/U+0.25*(1/U^2-1/L^2)*(r-sr2*sr2/r)+0.5*log(L/U)/r+C);"
                                  "U=r+sr2;"
                                  "C=2*(1/or1-1/L)*step(sr2-r-or1);"
                                  "L=max(or1, D);"
                                  "D=abs(r-sr2);"
                                  "sr2 = scale2*or2;"
                                  "or1 = radius1-0.009; or2 = radius2-0.009", CustomGBForce::ParticlePairNoExclusions);
    custom->addComputedValue("B", "1/(1/or-tanh(1*psi-0.8*psi^2+4.85*psi^3)/radius);"
                                  "psi=I*or; or=radius-0.009", CustomGBForce::SingleParticle);
    custom->addEnergyTerm("28.3919551*(radius+0.14)^2*(radius/B)^6-0.5*138.935485*(1/soluteDielectric-1/solventDielectric)*q^2/B", CustomGBForce::SingleParticle);
    string invCutoffString = "";
    if (obcMethod != GBSAOBCForce::NoCutoff) {
        stringstream s;
        s<<(1.0/cutoff);
        invCutoffString = s.str();
    }
    custom->addEnergyTerm("138.935485*(1/soluteDielectric-1/solventDielectric)*q1*q2*("+invCutoffString+"-1/f);"
                          "f=sqrt(r^2+B1*B2*exp(-r^2/(4*B1*B2)))", CustomGBForce::ParticlePairNoExclusions);
    vector<Vec3> positions(numParticles);
    vector<Vec3> velocities(numParticles);
    OpenMM_SFMT::SFMT sfmt;
    init_gen_rand(0, sfmt);

    vector<double> params(3);
    for (int i = 0; i < numMolecules; i++) {
        if (i < numMolecules/2) {
            obc->addParticle(1.0, 0.2, 0.5);
            params[0] = 1.0;
            params[1] = 0.2;
            params[2] = 0.5;
            custom->addParticle(params);
            obc->addParticle(-1.0, 0.1, 0.5);
            params[0] = -1.0;
            params[1] = 0.1;
            custom->addParticle(params);
        }
        else {
            obc->addParticle(1.0, 0.2, 0.8);
            params[0] = 1.0;
            params[1] = 0.2;
            params[2] = 0.8;
            custom->addParticle(params);
            obc->addParticle(-1.0, 0.1, 0.8);
            params[0] = -1.0;
            params[1] = 0.1;
            custom->addParticle(params);
        }
        positions[2*i] = Vec3(boxSize*genrand_real2(sfmt), boxSize*genrand_real2(sfmt), boxSize*genrand_real2(sfmt));
        positions[2*i+1] = Vec3(positions[2*i][0]+1.0, positions[2*i][1], positions[2*i][2]);
        velocities[2*i] = Vec3(genrand_real2(sfmt), genrand_real2(sfmt), genrand_real2(sfmt));
        velocities[2*i+1] = Vec3(genrand_real2(sfmt), genrand_real2(sfmt), genrand_real2(sfmt));
    }
    obc->setNonbondedMethod(obcMethod);
    custom->setNonbondedMethod(customMethod);
    standardSystem.addForce(obc);
    customSystem.addForce(custom);
    VerletIntegrator integrator1(0.01);
    VerletIntegrator integrator2(0.01);
    Context context1(standardSystem, integrator1, platform);
    context1.setPositions(positions);
    context1.setVelocities(velocities);
    State state1 = context1.getState(State::Forces | State::Energy);
    Context context2(customSystem, integrator2, platform);
    context2.setPositions(positions);
    context2.setVelocities(velocities);
    State state2 = context2.getState(State::Forces | State::Energy);
    ASSERT_EQUAL_TOL(state1.getPotentialEnergy(), state2.getPotentialEnergy(), 1e-4);
    for (int i = 0; i < numParticles; i++) {
        ASSERT_EQUAL_VEC(state1.getForces()[i], state2.getForces()[i], 1e-4);
    }
    
    // Try changing the particle parameters and make sure it's still correct.
    
    for (int i = 0; i < numMolecules/2; i++) {
        obc->setParticleParameters(2*i, 1.1, 0.3, 0.6);
        params[0] = 1.1;
        params[1] = 0.3;
        params[2] = 0.6;
        custom->setParticleParameters(2*i, params);
        obc->setParticleParameters(2*i+1, -1.1, 0.2, 0.4);
        params[0] = -1.1;
        params[1] = 0.2;
        params[2] = 0.4;
        custom->setParticleParameters(2*i+1, params);
    }
    obc->updateParametersInContext(context1);
    custom->updateParametersInContext(context2);
    state1 = context1.getState(State::Forces | State::Energy);
    state2 = context2.getState(State::Forces | State::Energy);
    ASSERT_EQUAL_TOL(state1.getPotentialEnergy(), state2.getPotentialEnergy(), 1e-4);
    for (int i = 0; i < numParticles; i++) {
        ASSERT_EQUAL_VEC(state1.getForces()[i], state2.getForces()[i], 1e-4);
    }
}