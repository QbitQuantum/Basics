void testFreeParticles() {
    const int numParticles = 100;
    const int numCopies = 30;
    const double temperature = 300.0;
    const double mass = 1.0;
    System system;
    for (int i = 0; i < numParticles; i++)
        system.addParticle(mass);
    RPMDIntegrator integ(numCopies, temperature, 10.0, 0.001);
    Platform& platform = Platform::getPlatformByName("Reference");
    Context context(system, integ, platform);
    OpenMM_SFMT::SFMT sfmt;
    init_gen_rand(0, sfmt);
    vector<Vec3> positions(numParticles);
    for (int i = 0; i < numCopies; i++)
    {
        for (int j = 0; j < numParticles; j++)
            positions[j] = Vec3(0.02*genrand_real2(sfmt), 0.02*genrand_real2(sfmt), 0.02*genrand_real2(sfmt));
        integ.setPositions(i, positions);
    }
    const int numSteps = 1000;
    integ.step(1000);
    vector<double> ke(numCopies, 0.0);
    vector<double> rg(numParticles, 0.0);
    const RealOpenMM hbar = 1.054571628e-34*AVOGADRO/(1000*1e-12);
    for (int i = 0; i < numSteps; i++) {
        integ.step(1);
        vector<State> state(numCopies);
        for (int j = 0; j < numCopies; j++)
            state[j] = integ.getState(j, State::Positions | State::Velocities, true);
        for (int j = 0; j < numParticles; j++) {
            double rg2 = 0.0;
            for (int k = 0; k < numCopies; k++) {
                Vec3 v = state[k].getVelocities()[j];
                ke[k] += 0.5*mass*v.dot(v);
                for (int m = 0; m < numCopies; m++) {
                    Vec3 delta = state[k].getPositions()[j]-state[m].getPositions()[j];
                    rg2 += delta.dot(delta);
                }
            }
            rg[j] += rg2/(2*numCopies*numCopies);
        }
    }
    double meanKE = 0.0;
    for (int i = 0; i < numCopies; i++)
        meanKE += ke[i];
    meanKE /= numSteps*numCopies;
    double expectedKE = 0.5*numCopies*numParticles*3*BOLTZ*temperature;
    ASSERT_USUALLY_EQUAL_TOL(expectedKE, meanKE, 1e-2);
    double meanRg2 = 0.0;
    for (int i = 0; i < numParticles; i++)
        meanRg2 += rg[i];
    meanRg2 /= numSteps*numParticles;
    double expectedRg = hbar/(2*sqrt(mass*BOLTZ*temperature));
    ASSERT_USUALLY_EQUAL_TOL(expectedRg, sqrt(meanRg2), 1e-3);
}