/**
 * Make sure random numbers are computed correctly when steps get merged.
 */
void testMergedRandoms() {
    const int numParticles = 10;
    const int numSteps = 10;
    System system;
    for (int i = 0; i < numParticles; i++)
        system.addParticle(1.0);
    CustomIntegrator integrator(0.1);
    integrator.addPerDofVariable("dofUniform1", 0);
    integrator.addPerDofVariable("dofUniform2", 0);
    integrator.addPerDofVariable("dofGaussian1", 0);
    integrator.addPerDofVariable("dofGaussian2", 0);
    integrator.addGlobalVariable("globalUniform1", 0);
    integrator.addGlobalVariable("globalUniform2", 0);
    integrator.addGlobalVariable("globalGaussian1", 0);
    integrator.addGlobalVariable("globalGaussian2", 0);
    integrator.addComputePerDof("dofUniform1", "uniform");
    integrator.addComputePerDof("dofUniform2", "uniform");
    integrator.addComputePerDof("dofGaussian1", "gaussian");
    integrator.addComputePerDof("dofGaussian2", "gaussian");
    integrator.addComputeGlobal("globalUniform1", "uniform");
    integrator.addComputeGlobal("globalUniform2", "uniform");
    integrator.addComputeGlobal("globalGaussian1", "gaussian");
    integrator.addComputeGlobal("globalGaussian2", "gaussian");
    Context context(system, integrator, platform);
    
    // See if the random numbers are computed correctly.
    
    vector<Vec3> values1, values2;
    for (int i = 0; i < numSteps; i++) {
        integrator.step(1);
        integrator.getPerDofVariable(0, values1);
        integrator.getPerDofVariable(1, values2);
        for (int i = 0; i < numParticles; i++)
            for (int j = 0; j < 3; j++) {
                double v1 = values1[i][j];
                double v2 = values2[i][j];
                ASSERT(v1 >= 0 && v1 < 1);
                ASSERT(v2 >= 0 && v2 < 1);
                ASSERT(v1 != v2);
            }
        integrator.getPerDofVariable(2, values1);
        integrator.getPerDofVariable(3, values2);
        for (int i = 0; i < numParticles; i++)
            for (int j = 0; j < 3; j++) {
                double v1 = values1[i][j];
                double v2 = values2[i][j];
                ASSERT(v1 >= -10 && v1 < 10);
                ASSERT(v2 >= -10 && v2 < 10);
                ASSERT(v1 != v2);
            }
        double v1 = integrator.getGlobalVariable(0);
        double v2 = integrator.getGlobalVariable(1);
        ASSERT(v1 >= 0 && v1 < 1);
        ASSERT(v2 >= 0 && v2 < 1);
        ASSERT(v1 != v2);
        v1 = integrator.getGlobalVariable(2);
        v2 = integrator.getGlobalVariable(3);
        ASSERT(v1 >= -10 && v1 < 10);
        ASSERT(v2 >= -10 && v2 < 10);
        ASSERT(v1 != v2);
    }
}