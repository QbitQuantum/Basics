void CudaIntegrateRPMDStepKernel::initialize(const System& system, const RPMDIntegrator& integrator) {
    cu.getPlatformData().initializeContexts(system);
    numCopies = integrator.getNumCopies();
    numParticles = system.getNumParticles();
    workgroupSize = numCopies;
    if (numCopies != findFFTDimension(numCopies))
        throw OpenMMException("RPMDIntegrator: the number of copies must be a multiple of powers of 2, 3, and 5.");
    int paddedParticles = cu.getPaddedNumAtoms();
    bool useDoublePrecision = (cu.getUseDoublePrecision() || cu.getUseMixedPrecision());
    int elementSize = (useDoublePrecision ? sizeof(double4) : sizeof(float4));
    forces = CudaArray::create<long long>(cu, numCopies*paddedParticles*3, "rpmdForces");
    positions = new CudaArray(cu, numCopies*paddedParticles, elementSize, "rpmdPositions");
    velocities = new CudaArray(cu, numCopies*paddedParticles, elementSize, "rpmdVelocities");
    cu.getIntegrationUtilities().initRandomNumberGenerator((unsigned int) integrator.getRandomNumberSeed());
    
    // Fill in the posq and velm arrays with safe values to avoid a risk of nans.
    
    if (useDoublePrecision) {
        vector<double4> temp(positions->getSize());
        for (int i = 0; i < positions->getSize(); i++)
            temp[i] = make_double4(0, 0, 0, 0);
        positions->upload(temp);
        for (int i = 0; i < velocities->getSize(); i++)
            temp[i] = make_double4(0, 0, 0, 1);
        velocities->upload(temp);
    }
    else {
        vector<float4> temp(positions->getSize());
        for (int i = 0; i < positions->getSize(); i++)
            temp[i] = make_float4(0, 0, 0, 0);
        positions->upload(temp);
        for (int i = 0; i < velocities->getSize(); i++)
            temp[i] = make_float4(0, 0, 0, 1);
        velocities->upload(temp);
    }
    
    // Build a list of contractions.
    
    groupsNotContracted = -1;
    const map<int, int>& contractions = integrator.getContractions();
    int maxContractedCopies = 0;
    for (map<int, int>::const_iterator iter = contractions.begin(); iter != contractions.end(); ++iter) {
        int group = iter->first;
        int copies = iter->second;
        if (group < 0 || group > 31)
            throw OpenMMException("RPMDIntegrator: Force group must be between 0 and 31");
        if (copies < 0 || copies > numCopies)
            throw OpenMMException("RPMDIntegrator: Number of copies for contraction cannot be greater than the total number of copies being simulated");
        if (copies != findFFTDimension(copies))
            throw OpenMMException("RPMDIntegrator: Number of copies for contraction must be a multiple of powers of 2, 3, and 5.");
        if (copies != numCopies) {
            if (groupsByCopies.find(copies) == groupsByCopies.end()) {
                groupsByCopies[copies] = 1<<group;
                if (copies > maxContractedCopies)
                    maxContractedCopies = copies;
            }
            else
                groupsByCopies[copies] |= 1<<group;
            groupsNotContracted -= 1<<group;
        }
    }
    if (maxContractedCopies > 0) {
        contractedForces = CudaArray::create<long long>(cu, maxContractedCopies*paddedParticles*3, "rpmdContractedForces");
        contractedPositions = new CudaArray(cu, maxContractedCopies*paddedParticles, elementSize, "rpmdContractedPositions");
    }

    // Create kernels.
    
    map<string, string> defines;
    defines["NUM_ATOMS"] = cu.intToString(cu.getNumAtoms());
    defines["PADDED_NUM_ATOMS"] = cu.intToString(cu.getPaddedNumAtoms());
    defines["NUM_COPIES"] = cu.intToString(numCopies);
    defines["THREAD_BLOCK_SIZE"] = cu.intToString(workgroupSize);
    defines["HBAR"] = cu.doubleToString(1.054571628e-34*AVOGADRO/(1000*1e-12));
    defines["SCALE"] = cu.doubleToString(1.0/sqrt((double) numCopies));
    defines["M_PI"] = cu.doubleToString(M_PI);
    map<string, string> replacements;
    replacements["FFT_Q_FORWARD"] = createFFT(numCopies, "q", true);
    replacements["FFT_Q_BACKWARD"] = createFFT(numCopies, "q", false);
    replacements["FFT_V_FORWARD"] = createFFT(numCopies, "v", true);
    replacements["FFT_V_BACKWARD"] = createFFT(numCopies, "v", false);
    CUmodule module = cu.createModule(cu.replaceStrings(CudaKernelSources::vectorOps+CudaRpmdKernelSources::rpmd, replacements), defines, "");
    pileKernel = cu.getKernel(module, "applyPileThermostat");
    stepKernel = cu.getKernel(module, "integrateStep");
    velocitiesKernel = cu.getKernel(module, "advanceVelocities");
    copyToContextKernel = cu.getKernel(module, "copyDataToContext");
    copyFromContextKernel = cu.getKernel(module, "copyDataFromContext");
    translateKernel = cu.getKernel(module, "applyCellTranslations");
    
    // Create kernels for doing contractions.
    
    for (map<int, int>::const_iterator iter = groupsByCopies.begin(); iter != groupsByCopies.end(); ++iter) {
        int copies = iter->first;
        replacements.clear();
        replacements["NUM_CONTRACTED_COPIES"] = cu.intToString(copies);
        replacements["POS_SCALE"] = cu.doubleToString(1.0/numCopies);
        replacements["FORCE_SCALE"] = cu.doubleToString(0x100000000/(double) copies);
        replacements["FFT_Q_FORWARD"] = createFFT(numCopies, "q", true);
        replacements["FFT_Q_BACKWARD"] = createFFT(copies, "q", false);
        replacements["FFT_F_FORWARD"] = createFFT(copies, "f", true);
        replacements["FFT_F_BACKWARD"] = createFFT(numCopies, "f", false);
        module = cu.createModule(cu.replaceStrings(CudaKernelSources::vectorOps+CudaRpmdKernelSources::rpmdContraction, replacements), defines, "");
        positionContractionKernels[copies] = cu.getKernel(module, "contractPositions");
        forceContractionKernels[copies] = cu.getKernel(module, "contractForces");
    }
}