void testThole() {
    const double k = ONE_4PI_EPS0*1.5;
    const double charge = 0.1;
    const double alpha = ONE_4PI_EPS0*charge*charge/k;
    const double thole = 2.5;
    System system;
    system.addParticle(1.0);
    system.addParticle(1.0);
    system.addParticle(1.0);
    system.addParticle(1.0);
    DrudeForce* drude = new DrudeForce();
    drude->addParticle(1, 0, -1, -1, -1, charge, alpha, 1, 1);
    drude->addParticle(3, 2, -1, -1, -1, charge, alpha, 1, 1);
    drude->addScreenedPair(0, 1, thole);
    system.addForce(drude);
    vector<Vec3> positions(4);
    positions[0] = Vec3(0, 0, 0);
    positions[1] = Vec3(0, -0.5, 0);
    positions[2] = Vec3(1, 0, 0);
    positions[3] = Vec3(1, 0, 0.3);
    double energySpring1 = 0.5*k*0.5*0.5;
    double energySpring2 = 0.5*k*0.3*0.3;
    double energyDipole = 0.0;
    double q[] = {-charge, charge, -charge, charge};
    for (int i = 0; i < 2; i++)
        for (int j = 2; j < 4; j++) {
            Vec3 delta = positions[i]-positions[j];
            double r = sqrt(delta.dot(delta));
            energyDipole += ONE_4PI_EPS0*q[i]*q[j]*computeScreening(r, thole, alpha, alpha)/r;
        }
    validateForce(system, positions, energySpring1+energySpring2+energyDipole);
}