/**
 * Sparse configuration file using libconfig++
 * to define all parameters of the case.
 */
void
readConfig(const char *cfgFileName)
{
  Config cfg;
  size_t degree;
  char cpyBuffer[256];

  // Read the file. If there is an error, report it and exit.
  std::cout << "Reading config file " << cfgFileName << std::endl;
  try {
    cfg.readFile(cfgFileName);

    std::cout.precision(6);
    std::cout << "Settings:" << std::endl;

    
    /** Get paths */
    std::cout << std::endl << "---general---" << std::endl;
    strcpy(resDir, (const char *) cfg.lookup("general.resDir"));
    std::cout << "Results directory: " << resDir << std::endl;
        
    /** Get model settings */
    std::cout << std::endl << "---model---" << std::endl;
    
    // Case name
    strcpy(caseName, (const char *) cfg.lookup("model.caseName"));
    std::cout << "Case name: " << caseName << std::endl;
    
    // Dimension
    dim = cfg.lookup("model.dim");
    std::cout << "dim = " << dim << std::endl;

    // Get delays in days and the number of delays
    const Setting &delaysSetting = cfg.lookup("model.delaysDays");
    nDelays = (size_t) delaysSetting.getLength();
    delaysDays = gsl_vector_alloc(nDelays);
    std::cout << "delays (days) = [";
    sprintf(delayName, "");
    for (size_t d = 0; d < nDelays; d++)
      {
	gsl_vector_set(delaysDays, d, delaysSetting[d]);
	std::cout << gsl_vector_get(delaysDays, d) << " ";
	strcpy(cpyBuffer, delayName);
	sprintf(delayName, "%s_d%d", cpyBuffer, (int) gsl_vector_get(delaysDays, d));
      }
    std::cout << "]" << std::endl;

    // Get drift polynomials
    const Setting &driftSetting = cfg.lookup("model.drift");
    driftPolynomials = new std::vector<gsl_vector *>(nDelays);
    for (size_t d = 0; d < nDelays; d++)
      {
	degree = driftSetting[d].getLength() - 1;
	driftPolynomials->at(d) = gsl_vector_alloc(degree + 1);
	// Print matrices
	std::cout << "Field polynomial coefficients at delay "
		  << d << " = [";
	for (size_t c = 0; c < degree + 1; c++)
	  {
	    gsl_vector_set(driftPolynomials->at(d), c, driftSetting[d][c]);
	    std::cout << gsl_vector_get(driftPolynomials->at(d), c) << " ";
	  }
	std::cout << "]" << std::endl;
      }

    // Get name of diffusion and its read matrix from file
    Q = gsl_matrix_alloc(dim, dim);
    const Setting &diffusionSetting = cfg.lookup("model.diffusion");
    std::cout << "Diffusion matrix Q = [";
    for (size_t i = 0; i < (size_t) dim; i++)
      {
	std::cout << "[";
	for (size_t j = 0; j < (size_t) dim; j++)
	  {
	    gsl_matrix_set(Q, i, j, diffusionSetting[j + i * dim]);
	    std::cout << gsl_matrix_get(Q, i, j) << " ";
	  }
	std::cout << "]";
      }
    std::cout << "]" << std::endl;

    /** Get simulation settings */
    std::cout << "\n" << "---simulation---" << std::endl;

    // Initial state
    const Setting &initStateSetting = cfg.lookup("simulation.initStateCst");
    initStateCst = gsl_vector_alloc(dim);
    std::cout << "Constant initial state: [";
    for (size_t i = 0; i < (size_t) dim; i++)
      {
	gsl_vector_set(initStateCst, i, initStateSetting[i]);
	std::cout << gsl_vector_get(initStateCst, i) << " ";
      }
    std::cout << "]" << std::endl;

    // Simulation length without spinup
    LCut = cfg.lookup("simulation.LCut");
    std::cout << "LCut = " << LCut << std::endl;

    // Time step
    dt = cfg.lookup("simulation.dt");
    std::cout << "dt = " << dt << std::endl;

    // Get delays in time-steps
    delays = gsl_vector_uint_alloc(nDelays);
    for (size_t d = 0; d < nDelays; d++)
      {
	gsl_vector_uint_set(delays, d,
			    (unsigned int) (gsl_vector_get(delaysDays, d) / 365 / dt));
      }

    // Spinup period to remove
    spinup = cfg.lookup("simulation.spinup");
    std::cout << "spinup = " << spinup << std::endl;

    // Sub-sampling for recording
    printStep = cfg.lookup("simulation.printStep");
    std::cout << "printStep = " << printStep << std::endl;

    // Output format
    strcpy(fileFormat, (const char *) cfg.lookup("simulation.fileFormat"));
    std::cout << "Output file format: " << fileFormat << std::endl;

    std::cout << std::endl;
    
    // Define some parameters
    L = LCut + spinup;
    printStepNum = (size_t) (printStep / dt);
    
    // Define destination file name
    sprintf(dstFileName, "%s/simulation/sim%s.%s", resDir, postfix, fileFormat);

  }
  catch(const FileIOException &fioex) {
    std::cerr << "I/O error while reading configuration file." << std::endl;
    throw fioex;
  }
  catch(const ParseException &pex) {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    throw pex;
  }
  catch(const SettingNotFoundException &nfex) {
    std::cerr << "Setting " << nfex.getPath() << " not found." << std::endl;
    throw nfex;
  }
  catch(const SettingTypeException &stex) {
    std::cerr << "Setting type exception." << std::endl;
    throw stex;
  }

  return;
}