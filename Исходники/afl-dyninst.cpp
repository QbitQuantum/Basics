int main(int argc, char **argv) {
  if (argc < 3 || strncmp(argv[1], "-h", 2) == 0 || strncmp(argv[1], "--h", 3) == 0) {
    cout << "Usage: " << argv[0] << USAGE;
    return false;
  }

  if (!parseOptions(argc, argv)) {
    return EXIT_FAILURE;
  }
  
  if (do_bb == true) {
    if (DYNINST_MAJOR_VERSION < 9 || (DYNINST_MAJOR_VERSION == 9 && DYNINST_MINOR_VERSION < 3) || (DYNINST_MAJOR_VERSION == 9 && DYNINST_MINOR_VERSION == 3 && DYNINST_PATCH_VERSION <= 2)) {
      if (dynfix == false)
        fprintf(stderr, "Warning: your dyninst version does not include a critical fix, you should use the -f option!\n");
    } else {
      if (dynfix == true)
        fprintf(stderr, "Notice: your dyninst version is fixed, the -f option should not be necessary.\n");
    }
  }

  BPatch bpatch;
  BPatch_binaryEdit *appBin = bpatch.openBinary(originalBinary, instrumentLibraries.size() != 1);

  if (appBin == NULL) {
    cerr << "Failed to open binary" << endl;
    return EXIT_FAILURE;
  }

  BPatch_image *appImage = appBin->getImage();

  //get and iterate over all modules, instrumenting only the default and manually specified ones
  vector < BPatch_module * >*modules = appImage->getModules();
  vector < BPatch_module * >::iterator moduleIter;
  vector < BPatch_function * >*funcsInModule;
  BPatch_module *defaultModule = NULL;
  string defaultModuleName;

  // look for _init
  if (defaultModuleName.empty()) {
    for (moduleIter = modules->begin(); moduleIter != modules->end(); ++moduleIter) {
      funcsInModule = (*moduleIter)->getProcedures();
      vector < BPatch_function * >::iterator funcsIterator;
      for (funcsIterator = funcsInModule->begin(); funcsIterator != funcsInModule->end(); ++funcsIterator) {
        char funcName[1024];

        (*funcsIterator)->getName(funcName, 1024);
        if (string(funcName) == string("_init")) {
          char moduleName[1024];

          (*moduleIter)->getName(moduleName, 1024);
          defaultModuleName = string(moduleName);
          if (verbose) {
            cout << "Found _init in " << moduleName << endl;
          }
          break;
        }
      }
      if (!defaultModuleName.empty())
        break;
    }
  }
  // last resort, by name of the binary
  if (defaultModuleName.empty())
    defaultModuleName = string(originalBinary).substr(string(originalBinary).find_last_of("\\/") + 1);

  if (!appBin->loadLibrary(instLibrary)) {
    cerr << "Failed to open instrumentation library " << instLibrary << endl;
    cerr << "It needs to be located in the current working directory." << endl;
    return EXIT_FAILURE;
  }

  appImage = appBin->getImage();

  /* Find code coverage functions in the instrumentation library */
  BPatch_function *initAflForkServer;
  save_rdi = findFuncByName(appImage, (char *) "save_rdi");
  restore_rdi = findFuncByName(appImage, (char *) "restore_rdi");
  BPatch_function *bbCallback = findFuncByName(appImage, (char *) "bbCallback");
  BPatch_function *forceCleanExit = findFuncByName(appImage, (char *) "forceCleanExit");

  if (do_bb == true)
    initAflForkServer = findFuncByName(appImage, (char *) "initAflForkServer");
  else
    initAflForkServer = findFuncByName(appImage, (char *) "initOnlyAflForkServer");

  if (!initAflForkServer || !bbCallback || !save_rdi || !restore_rdi || !forceCleanExit) {
    cerr << "Instrumentation library lacks callbacks!" << endl;
    return EXIT_FAILURE;
  }

  int bbIndex = 0;

  // instrument all shared libraries:
  for (moduleIter = modules->begin(); moduleIter != modules->end(); ++moduleIter) {
    char moduleName[1024];

    (*moduleIter)->getName(moduleName, 1024);

    if ((*moduleIter)->isSharedLib()) {
      if (instrumentLibraries.find(moduleName) == instrumentLibraries.end()) {
        cout << "Skipping library: " << moduleName << endl;
        continue;
      }
    }

    if (string(moduleName).find(defaultModuleName) != string::npos) {
      defaultModule = (*moduleIter);
      if (skipMainModule)
        continue;
    }
    
    if (do_bb == true) {
      cout << "Instrumenting module: " << moduleName << endl;
      vector < BPatch_function * >*allFunctions = (*moduleIter)->getProcedures();
      vector < BPatch_function * >::iterator funcIter;

      // iterate over all functions in the module
      for (funcIter = allFunctions->begin(); funcIter != allFunctions->end(); ++funcIter) {
        BPatch_function *curFunc = *funcIter;
        char funcName[1024];
        int do_patch = 1;

        curFunc->getName(funcName, 1024);
        if (string(funcName) == string("_start"))
          continue;               // here's a bug on hlt // XXX: check what happens if removed
        
        if (!skipAddresses.empty()) {
          set < string >::iterator saiter;
          for (saiter = skipAddresses.begin(); saiter != skipAddresses.end() && do_patch == 1; saiter++)
            if (*saiter == string(funcName))
              do_patch = 0;
          if (do_patch == 0) {
            cout << "Skipping instrumenting function " << funcName << endl;
            continue;
          }
        }
        insertBBCallback(appBin, curFunc, funcName, bbCallback, &bbIndex);
      }
    }
  }

  // if an entrypoint was set then find function, else find _init
  BPatch_function *funcToPatch = NULL;

  if (!entryPoint) {
    BPatch_Vector < BPatch_function * >funcs;
    defaultModule->findFunction("_init", funcs);
    if (!funcs.size()) {
      cerr << "Couldn't locate _init, specify entry point manually with -e 0xaddr" << endl;
      return EXIT_FAILURE;
    }
    // there should really be only one
    funcToPatch = funcs[0];
  } else {
    funcToPatch = defaultModule->findFunctionByEntry(entryPoint);
  }
  if (!funcToPatch) {
    cerr << "Couldn't locate function at given entry point. " << endl;
    return EXIT_FAILURE;
  }
  if (!insertCallToInit(appBin, initAflForkServer, defaultModule, funcToPatch)) {
    cerr << "Could not insert init callback at given entry point." << endl;
    return EXIT_FAILURE;
  }

  if (!exitAddresses.empty()) {
    cout << "Instrumenting forced exit addresses." << endl;
    set < unsigned long >::iterator uliter;
    for (uliter = exitAddresses.begin(); uliter != exitAddresses.end(); uliter++) {
      if (*uliter > 0 && (signed long)*uliter != -1) {
        funcToPatch = defaultModule->findFunctionByEntry(*uliter);
        if (!funcToPatch) {
          cerr << "Could not find enty point 0x" << hex << *uliter << " (continuing)" << endl;
        } else {
          if (!insertCallToInit(appBin, forceCleanExit, defaultModule, funcToPatch))
            cerr << "Could not insert force clean exit callback at 0x" << hex << *uliter << " (continuing)" << endl;
        }
      }
    }
  }

  cout << "Saving the instrumented binary to " << instrumentedBinary << " ..." << endl;
  // Output the instrumented binary
  if (!appBin->writeFile(instrumentedBinary)) {
    cerr << "Failed to write output file: " << instrumentedBinary << endl;
    return EXIT_FAILURE;
  }

  if (!runtimeLibraries.empty()) {
    cout << "Instrumenting runtime libraries." << endl;
    set < string >::iterator rtLibIter;
    for (rtLibIter = runtimeLibraries.begin(); rtLibIter != runtimeLibraries.end(); rtLibIter++) {
      BPatch_binaryEdit *libBin = bpatch.openBinary((*rtLibIter).c_str(), false);

      if (libBin == NULL) {
        cerr << "Failed to open binary " << *rtLibIter << endl;
        return EXIT_FAILURE;
      }
      BPatch_image *libImg = libBin->getImage();

      vector < BPatch_module * >*modules = libImg->getModules();
      moduleIter = modules->begin();

      for (; moduleIter != modules->end(); ++moduleIter) {
        char moduleName[1024];

        (*moduleIter)->getName(moduleName, 1024);
        cout << "Instrumenting module: " << moduleName << endl;
        vector < BPatch_function * >*allFunctions = (*moduleIter)->getProcedures();
        vector < BPatch_function * >::iterator funcIter;
        // iterate over all functions in the module
        for (funcIter = allFunctions->begin(); funcIter != allFunctions->end(); ++funcIter) {
          BPatch_function *curFunc = *funcIter;
          char funcName[1024];

          curFunc->getName(funcName, 1024);
          if (string(funcName) == string("_start"))
            continue;
          insertBBCallback(libBin, curFunc, funcName, bbCallback, &bbIndex);
        }
      }
      if (!libBin->writeFile((*rtLibIter + ".ins").c_str())) {
        cerr << "Failed to write output file: " << (*rtLibIter + ".ins").c_str() << endl;
        return EXIT_FAILURE;
      } else {
        cout << "Saved the instrumented library to " << (*rtLibIter + ".ins").c_str() << "." << endl;
      }
    }
  }

  cout << "All done! Happy fuzzing!" << endl;
  return EXIT_SUCCESS;
}