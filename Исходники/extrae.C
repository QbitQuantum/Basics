int main (int argc, char *argv[])
{
	set<string> UserFunctions;
	set<string> ParallelFunctions;
    map<string, vector<string> > LoopLevels;
	char *env_var;

	int index;

	if (getenv("EXTRAE_HOME") == NULL)
	{
		cerr << PACKAGE_NAME << ": Environment variable EXTRAE_HOME is undefined" << endl;
		exit (-1);
	}

	if ((env_var = getenv ("DYNINSTAPI_RT_LIB")) == NULL)
	{
		env_var = (char*) malloc ((1+strlen("DYNINSTAPI_RT_LIB=")+strlen(DYNINST_RT_LIB))*sizeof(char));
		if (env_var == NULL)
		{
			cerr << PACKAGE_NAME << ": Cannot allocate memory to define DYNINSTAPI_RT_LIB!" << endl;
			exit (-1);
		}
		sprintf (env_var, "DYNINSTAPI_RT_LIB=%s", DYNINST_RT_LIB);
		putenv (env_var);
	}
	else
		cout << PACKAGE_NAME << ": Warning, DYNINSTAPI_RT_LIB already set and pointing to " << 
		  env_var << endl;

	/* Parse the params */
	index = processParams (argc, argv);

	char * envvar_dyn = (char *) malloc ((strlen("EXTRAE_DYNINST_RUN=yes")+1)*sizeof (char));
	if (NULL == envvar_dyn)
	{
		cerr << PACKAGE_NAME << ": Error! Unable to allocate memory for EXTRAE_DYNINST_RUN environment variable" << endl;
		exit (-1);
	}
	sprintf (envvar_dyn, "EXTRAE_DYNINST_RUN=yes");
	putenv (envvar_dyn);

	if (!ListFunctions)
	{
		if (configXML != NULL)
		{
			char * envvar = (char *) malloc ((strlen(configXML)+strlen("EXTRAE_CONFIG_FILE=")+1)*sizeof (char));
			if (NULL == envvar)
			{
				cerr << PACKAGE_NAME << ": Error! Unable to allocate memory for EXTRAE_CONFIG_FILE environment variable" << endl;
				exit (-1);
			}
			sprintf (envvar, "EXTRAE_CONFIG_FILE=%s", configXML);
			putenv (envvar);
		}
		else
		{
			if (getenv ("EXTRAE_CONFIG_FILE") == NULL)
			{
				cerr << PACKAGE_NAME << ": Error! You have to provide a configuration file using the -config parameter or set the EXTRAE_CONFIG_FILE" << endl;
				exit (-1);
			}
			configXML = getenv ("EXTRAE_CONFIG_FILE");
		}

		if (!file_exists(configXML))
		{
			cerr << PACKAGE_NAME << ": Error! Unable to locate " << configXML << endl;	
			exit (-1);
		}

		::Parse_XML_File (0, 0, configXML);
	}

	/* Does the binary exists? */
	if (!file_exists(argv[index]))
	{
		cout << PACKAGE_NAME << ": Executable " << argv[index] << " cannot be found!" << endl;
		exit (-1);
	}

	/* Create an instance of the BPatch library */
	bpatch = new BPatch;

	/* Register a callback function that prints any error messages */
	bpatch->registerErrorCallback (errorFunc);

	/* Don't check recursion in snippets */
	bpatch->setTrampRecursive (true);

	cout << "Welcome to " << PACKAGE_STRING << " launcher using DynInst "
	  << DYNINST_MAJOR << "." << DYNINST_MINOR << "." << DYNINST_SUBMINOR << endl;

	int i = 1;
	while (argv[index+i] != NULL)
	{
		cout << PACKAGE_NAME << ": Argument " << i <<  " - " << argv[index+i] << endl;
		i++;
	}

	BPatch_process *appProcess = NULL;
	BPatch_binaryEdit *appBin = NULL;
	BPatch_addressSpace *appAddrSpace = NULL;

	if (!BinaryRewrite)
	{
		cout << PACKAGE_NAME << ": Creating process for image binary " << argv[index];
		cout.flush ();
		appProcess = bpatch->processCreate ((const char*) argv[index], (const char**) &argv[index], (const char**) environ);
		if (appProcess == NULL)
		{
			cerr << endl << PACKAGE_NAME << ": Error creating the target application process" << endl;
			exit (-1);
		}
		cout << " PID(" << appProcess->getPid() << ")" << endl;

		/* Stop the execution in order to load the instrumentation library */
		cout << PACKAGE_NAME << ": Stopping mutatee execution" << endl;
		if (!appProcess->stopExecution())
		{
			cerr << PACKAGE_NAME << ": Cannot stop execution of the target application" << endl;
			exit (-1);
		}
		appAddrSpace = appProcess;
	}
	else
	{
		cout << PACKAGE_NAME << ": Rewriting binary " << argv[index] << endl;
		appBin = bpatch->openBinary ((const char*) argv[index], false); /* passed true to instrument libraries before !? */
		if (appBin == NULL)
		{
			cerr << PACKAGE_NAME << ": Error opening binary for rewriting" << endl;
			exit (-1);
		}
		appAddrSpace = appBin;
	}

	BPatch_image *appImage = appAddrSpace->getImage();
	if (appImage == NULL)
	{
		cerr << PACKAGE_NAME << ": Error while acquiring application image" << endl;
		exit (-1);
	}

	/* The user asks for the list of functions, simply show it */
	if (ListFunctions)
	{
		ShowFunctions (appImage);
		if (!BinaryRewrite)		
			appProcess->terminateExecution();
		exit (-1);
	}

	/* Read files */
	if (::XML_have_UFlist())
	{
		if (VerboseLevel)
			cout << PACKAGE_NAME << ": Reading instrumented user functions from " << ::XML_UFlist() << endl;
		ReadFileIntoList (::XML_UFlist(), UserFunctions);
        discoverInstrumentationLevel(UserFunctions, LoopLevels);
	}

    if (DecodeBasicBlock)
    {
        std::set<string>::iterator f_begin = UserFunctions.begin();
        std::set<string>::iterator f_end = UserFunctions.end();
        while (f_begin != f_end)
        {
            BPatch_function *f = getRoutine ((*f_begin).c_str(), appImage);
            if (f == NULL)
            {
                cerr << PACKAGE_NAME << ": Unable to find " << *f_begin << " function!" << endl;
            }
            else
            {
                cout<<decodeBasicBlocks(f, *f_begin);
            }
            f_begin++;
        }
		if (!BinaryRewrite)	{	
			appProcess->terminateExecution();
            }
        exit(-1);
    }

	if (::XML_CheckTraceEnabled())
	{
		ApplicationType *appType = new ApplicationType ();

		extrae_detecting_application_type = true;

		cout << PACKAGE_NAME << ": Detecting application type " << endl;
		appType->detectApplicationType (appImage);
		appType->dumpApplicationType ();

		cout << PACKAGE_NAME << ": Detecting whether the application has been already linked with Extrae : ";
		BPatch_function *extrae_init = getRoutine ("Extrae_init", appImage, false);
		BinaryLinkedWithInstrumentation = extrae_init != NULL;
		cout << (BinaryLinkedWithInstrumentation?"yes":"no") << endl;

		extrae_detecting_application_type = false;

		/* If the application has not been linked with instrumentation library, load the
		   appropriate module */
		if (!BinaryLinkedWithInstrumentation)
		{
			char buffer[1024]; /* will hold the library to load */

			/* Check for the correct library to be loaded */
			if (appType->get_isMPI())
			{
				if (appType->get_isOpenMP())
				{
					if (appType->get_MPI_type() == ApplicationType::MPI_C)
						sprintf (buffer, "%s/lib/lib_dyn_ompitracec-%s.so", getenv("EXTRAE_HOME"), PACKAGE_VERSION);
					else
						sprintf (buffer, "%s/lib/lib_dyn_ompitracef-%s.so", getenv("EXTRAE_HOME"), PACKAGE_VERSION);
				}
				else if (appType->get_isCUDA())
				{
					if (appType->get_MPI_type() == ApplicationType::MPI_C)
						sprintf (buffer, "%s/lib/lib_dyn_cudampitracec-%s.so", getenv("EXTRAE_HOME"), PACKAGE_VERSION);
					else
						sprintf (buffer, "%s/lib/lib_dyn_cudampitracef-%s.so", getenv("EXTRAE_HOME"), PACKAGE_VERSION);
				}
				else
				{
					if (appType->get_MPI_type() == ApplicationType::MPI_C)
						sprintf (buffer, "%s/lib/lib_dyn_mpitracec-%s.so", getenv("EXTRAE_HOME"), PACKAGE_VERSION);
					else
						sprintf (buffer, "%s/lib/lib_dyn_mpitracef-%s.so", getenv("EXTRAE_HOME"), PACKAGE_VERSION);
				}
			}
			else
			{
				if (appType->get_isOpenMP())
				{
					sprintf (buffer, "%s/lib/libomptrace-%s.so", getenv("EXTRAE_HOME"), PACKAGE_VERSION);
				}
				else
				{
					if (appType->get_isCUDA())
						sprintf (buffer, "%s/lib/libcudatrace-%s.so", getenv("EXTRAE_HOME"), PACKAGE_VERSION);
					else
						sprintf (buffer, "%s/lib/libseqtrace-%s.so", getenv("EXTRAE_HOME"), PACKAGE_VERSION);
				}
			}

			loadedModule = buffer;

			/* Load the module into the mutattee */
			cout << PACKAGE_NAME << ": Loading " << loadedModule << " into the target application" << endl;
	
			if (!file_exists (buffer))
			{
				/* If the library does not exist, terminate the mutatee and exit */
				cerr << PACKAGE_NAME << ": Cannot find the module. It must be under $EXTRAE_HOME/lib" << endl;
				appProcess->terminateExecution();
				exit (-1);
			}
			if (!appAddrSpace->loadLibrary (loadedModule.c_str()))
			{
				/* If the library cannot be loaded, terminate the mutatee and exit */
				cerr << PACKAGE_NAME << ": Cannot load library! Retry using -v to gather more information on this error!" << endl;
				appProcess->terminateExecution();
				exit (-1);
			}
		} /* ! BinaryLinkedWithInstrumentation */
		else
			cout << PACKAGE_NAME << ": The application seems to be linked with Extrae libraries. Won't load additional libraries..." << endl;

		/* Load instrumentation API patches */
		loadAPIPatches (appImage);
		if (appType->get_isMPI() && ::XML_GetTraceMPI())
			loadMPIPatches (appImage);

		/* Instrument fork, wait, waitpid and exec calls */
		InstrumentForks (appImage);

		/* Apply instrumentation of runtimes only if not linked with Extrae */
		if (!BinaryLinkedWithInstrumentation && appType->get_isOpenMP())
		{
			if (appType->get_OpenMP_rte() == ApplicationType::Intel_v11)
			{
				cout << PACKAGE_NAME << ": Gathering information for Intel v11 OpenMP runtime" << endl;
# warning "Aixo nomes es per !BinaryRewriting!"
				InstrumentOMPruntime_Intel (appImage, appProcess);
			}
			cout << PACKAGE_NAME << ": Instrumenting OpenMP runtime" << endl;
			InstrumentOMPruntime (::XML_GetTraceOMP_locks(), appType, appImage);
		}

		/* Apply instrumentation of runtimes only if not linked with Extrae */
		if (!BinaryLinkedWithInstrumentation && appType->get_isCUDA())
		{
			cout << PACKAGE_NAME << ": Instrumenting CUDA runtime" << endl;
			InstrumentCUDAruntime (appType, appImage);
		}

		/* If the application is NOT MPI, instrument the MAIN symbol in order to
 		   initialize and finalize the instrumentation */
		/* Apply instrumentation of runtimes only if not linked with Extrae */
		if (!appType->get_isMPI())
		{
			/* Typical main entry & exit */
			wrapRoutine (appImage, "main", "Extrae_init", "Extrae_fini");
		}
		else
		{
			/* Cover those cases that MPI apps do not call MPI_Finalize */
			wrapRoutine (appImage, "main", "", "Extrae_fini_last_chance_Wrapper");
		}

		{
			/* Special cases (e.g., fortran stop call) */
			string exit_calls[] =
			{
				  "exit", /* C */
				  "_xlfExit", /* Fortran IBM XL */
				  "_gfortran_stop_numeric", /* Fortran GNU */
				  "for_stop_core", /* Fortran Intel */
				  ""
			};

			/* bypass error messages given if these routines are not found */
			int i = 0;
			extrae_detecting_application_type = true;
			while (exit_calls[i].length() > 0)
			{
				BPatch_function *special_exit = getRoutine (exit_calls[i].c_str(), appImage, false);
				if (NULL != special_exit)
					wrapRoutine (appImage, exit_calls[i], "Extrae_fini_last_chance_Wrapper", "");
				i++;
			}
			extrae_detecting_application_type = false;
		}

		InstrumentCalls (appImage, appAddrSpace, appType, ParallelFunctions,
		  UserFunctions, LoopLevels, ::XML_GetTraceMPI(), ::XML_GetTraceOMP(), true);

		GenerateSymFile (ParallelFunctions, UserFunctions, appImage,
		  appAddrSpace);
	}

	// bpatch->registerExecCallback(ExecCallback);

	if (!BinaryRewrite)
	{
		cout << PACKAGE_NAME << ": Starting program execution" << endl;
		if (!appProcess->continueExecution())
		{
			/* If the application cannot continue, terminate the mutatee and exit */
			cerr << PACKAGE_NAME << ": Cannot continue execution of the target application" << endl;
			appProcess->terminateExecution();
			exit (-1);
		}

		while (!appProcess->isTerminated())
			bpatch->waitForStatusChange();

		if (appProcess->terminationStatus() == ExitedNormally)
			appProcess->getExitCode();
		else if(appProcess->terminationStatus() == ExitedViaSignal)
			appProcess->getExitSignal();

		delete appProcess;
	}
	else
	{
		string newfile = string(argv[index])+".extrae";
		cout << PACKAGE_NAME << ": Generating the instrumented binary" << endl;
		if (appBin->writeFile (newfile.c_str()))
			cout << PACKAGE_NAME << ": Congratulations " << newfile << " has been generated" << endl;
		else
			cout << PACKAGE_NAME << ": Error! Could not generate " << newfile << endl;
		
		delete appBin;
	}

	return 0;
}