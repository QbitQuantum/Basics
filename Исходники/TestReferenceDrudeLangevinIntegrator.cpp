void testSinglePair() {
    const double temperature = 300.0;
    const double temperatureDrude = 10.0;
    const double k = ONE_4PI_EPS0*1.5;
    const double charge = 0.1;
    const double alpha = ONE_4PI_EPS0*charge*charge/k;
    const double mass1 = 1.0;
    const double mass2 = 0.1;
    const double totalMass = mass1+mass2;
    const double reducedMass = (mass1*mass2)/(mass1+mass2);
    const double maxDistance = 0.05;
    System system;
    system.addParticle(mass1);
    system.addParticle(mass2);
    DrudeForce* drude = new DrudeForce();
    drude->addParticle(1, 0, -1, -1, -1, charge, alpha, 1, 1);
    system.addForce(drude);
    vector<Vec3> positions(2);
    positions[0] = Vec3(0, 0, 0);
    positions[1] = Vec3(0, 0, 0);
    DrudeLangevinIntegrator integ(temperature, 20.0, temperatureDrude, 20.0, 0.003);
    integ.setMaxDrudeDistance(maxDistance);
    Platform& platform = Platform::getPlatformByName("Reference");
    Context context(system, integ, platform);
    context.setPositions(positions);
    
    // Equilibrate.
    
    integ.step(1000);
    
    // Compute the internal and center of mass temperatures.
    
    double keCM = 0, keInternal = 0;
    int numSteps = 10000;
    for (int i = 0; i < numSteps; i++) {
        integ.step(10);
        State state = context.getState(State::Velocities | State::Positions);
        const vector<Vec3>& vel = state.getVelocities();
        Vec3 velCM = vel[0]*(mass1/totalMass) + vel[1]*(mass2/totalMass);
        keCM += 0.5*totalMass*velCM.dot(velCM);
        Vec3 velInternal = vel[0]-vel[1];
        keInternal += 0.5*reducedMass*velInternal.dot(velInternal);
        Vec3 delta = state.getPositions()[0]-state.getPositions()[1];
        double distance = sqrt(delta.dot(delta));
        ASSERT(distance <= maxDistance*(1+1e-6));
    }
    ASSERT_USUALLY_EQUAL_TOL(3*0.5*BOLTZ*temperature, keCM/numSteps, 0.1);
    ASSERT_USUALLY_EQUAL_TOL(3*0.5*BOLTZ*temperatureDrude, keInternal/numSteps, 0.01);
}