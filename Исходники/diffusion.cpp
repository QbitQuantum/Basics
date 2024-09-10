//////////////////////////////////////////////////////////////////////////////////////////
// Function name: readInputs.
// Description: Reads parameters from the configuration file, overwrites their default 
//		values.
// Inputs:	Name of configuration file plus all parameters in config file (passed by 
//		reference).
//////////////////////////////////////////////////////////////////////////////////////////
void readInputs(int argc, char** argv, char *configFilename, int *pstepsPerUpdate, bool *puseGpu, bool *puseDisplay, bool *pwriteOut, uint *psearchMethod, uint *pnumSpins, 
		float *pgyroMagneticRatio, float *ptimeStep, float *pextraAdc, float *pintraAdc, float *pmyelinAdc, float *pextraT2, float *pintraT2, 
		float *pmyelinT2, float *pspaceScale, float *ppermeability, float *pstartBoxSize, char *& outFileName){
	using namespace libconfig;
	using namespace std;

	////////////////////////////////////////////////////////////////////////
	// Note: Usage of cfg commands gives errors of type "Undefined reference to..." if -lconfig++ flag
	// is omitted from the compile command in the Makefile.
	// Errors in syntax in the sim.cfg file (such as omitted ;) can result in parse errors.
	////////////////////////////////////////////////////////////////////////
	Config cfg;
	try{
		cout << "Loading " << configFilename << "..." << endl;
		cfg.readFile(configFilename);
	} catch(FileIOException){
		cout << "File IO failed." << endl;
	} catch(ParseException){
		cout << "Parse failed." << endl;
	}

	//////////////////////////////////////////////////////////////////////
	// Read the app parameters from the cfg file
	//////////////////////////////////////////////////////////////////////
	cfg.lookupValue("app.stepsPerUpdate", *pstepsPerUpdate);
	cfg.lookupValue("app.useGpu", *puseGpu);
	cfg.lookupValue("app.useDisplay", *puseDisplay);
	cfg.lookupValue("app.writeOut", *pwriteOut);

	//////////////////////////////////////////////////////////////////////
	// Read the sim parameters from the cfg file
	//////////////////////////////////////////////////////////////////////
	cfg.lookupValue("sim.numSpins", *pnumSpins);
	cfg.lookupValue("sim.gyroMagneticRatio", *pgyroMagneticRatio);
	cfg.lookupValue("sim.timeStep", *ptimeStep);
	cfg.lookupValue("sim.extraAdc", *pextraAdc);
	cfg.lookupValue("sim.intraAdc", *pintraAdc);
	cfg.lookupValue("sim.myelinAdc", *pmyelinAdc);
	cfg.lookupValue("sim.extraT2", *pextraT2);
	cfg.lookupValue("sim.intraT2", *pintraT2);
	cfg.lookupValue("sim.myelinT2", *pmyelinT2);
	cfg.lookupValue("sim.spaceScale", *pspaceScale);
	cfg.lookupValue("sim.startBox", *pstartBoxSize);
	cfg.lookupValue("sim.permeability", *ppermeability);
	cfg.lookupValue("sim.searchMethod", *psearchMethod);
	const char *tempOutFileName;
	cfg.lookupValue("sim.outFile", tempOutFileName);
	outFileName = new char[strlen(tempOutFileName)];
	strcpy(outFileName, tempOutFileName);

	/////////////////////////////////////////////////////////////////////////
	// Read the gradient information from the gradient file specified in the config file
	/////////////////////////////////////////////////////////////////////////
	const char *gradsFile;
	if (cfg.lookupValue("sim.gradsFile", gradsFile)) {
		printf("Loading gradient sequence from %s.\n", gradsFile);
		FILE *gradsFilePtr = fopen(gradsFile,"r");
		float ld, bd, ro, gx, gy, gz;
		gradStruct *prevGrad = NULL, *curGrad = NULL;
		while (!feof(gradsFilePtr)){
			int nScan = fscanf(gradsFilePtr, "%g %g %g %g %g %g", &ld, &bd, &ro, &gx, &gy, &gz);	// nScan is the number of items successfully read
			if (nScan == 6){									// We have read a line that can specify a gradient
				numGrads++;
				curGrad = new gradStruct;
				curGrad->lDelta = ld;
				curGrad->bDelta = bd;
				curGrad->readOut = ro;
				curGrad->gx = gx;
				curGrad->gy = gy;
				curGrad->gz = gz;
				curGrad->next = NULL;
				if (prevGrad != NULL) prevGrad->next = curGrad;
				if (gGrads==NULL) gGrads = curGrad;
				prevGrad = curGrad;
			}
		}

		fclose(gradsFilePtr);
	}

	//////////////////////////////////////////////////////////////////////////
	// Read the fiber parameters from the cfg file
	//////////////////////////////////////////////////////////////////////////
	const char *fiberFileConst;
	cfg.lookupValue("fibers.fiberFile", fiberFileConst);
	fiberFile = (char *)malloc((strlen(fiberFileConst)+1)*sizeof(char));
	strcpy(fiberFile, fiberFileConst);
	//printf("(In readInputs): Reading fibers from file (%s)\n",fiberFile);


	///////////////////////////////////////////////////////////////////////////////////////
	// See if information in configuration file is overwritten by command line flags.
	///////////////////////////////////////////////////////////////////////////////////////
	
	// See if the command line specifies whether we should display graphics	
	if(checkCmdLineFlag(argc, (const char**) argv, "disp")){
		useDisplay = true;
	}	
	else if(checkCmdLineFlag(argc, (const char**) argv, "nodisp")){
		useDisplay = false;
	}

	if(checkCmdLineFlag(argc, (const char**) argv, "gpu")){
		useGpu = true;
	}	
	else if(checkCmdLineFlag(argc, (const char**) argv, "cpu")){
		useGpu = false;
	}

	if(checkCmdLineFlag(argc, (const char**) argv, "w")){
		writeOut = true;
	}	
	else if(checkCmdLineFlag(argc, (const char**) argv, "nw")){
		writeOut = false;
	}


	float cmdValf = NAN;
	int cmdVali = NAN;
	char *cmdVals;

        if(getCmdLineArgumentInt( argc, (const char**) argv, "stepsPerUpdate")){
		*pstepsPerUpdate = cmdVali;
        }

        if(getCmdLineArgumentInt( argc, (const char**) argv, "numSpins")){
		*pnumSpins = cmdVali;
        }

	if(getCmdLineArgumentInt( argc, (const char**) argv, "searchMethod")){
		*psearchMethod = cmdVali;
        }

        if(getCmdLineArgumentFloat( argc, (const char**) argv, "perm")){
		*ppermeability = cmdValf;
        }

	if(getCmdLineArgumentFloat( argc, (const char**) argv, "startBox")){
		*pstartBoxSize = cmdValf;
        }

	if(getCmdLineArgumentString( argc, (const char**) argv, "fiberFile", &cmdVals)){
		fiberFile = (char *)malloc((strlen(cmdVals)+1)*sizeof(char));
		strcpy(fiberFile, cmdVals);
	}
}