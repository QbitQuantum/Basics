int main(int argc, char* argv[]) 
{
	xsCreation creation_mc = {
		25*1024,	/* initial chunk size */
		2048,		/* incremental chunk size */
		50*1024/16,	/* initial heap count	-- will be calculated later */
		128,		/* incremental heap count	-- wasting 16 bytes / allocation */
		548,		/* stack count */
		2048+512,	/* key count */
		97,		/* name modulo */
		127,		/* symbol modulo */
	};
	xsCreation creation_tool = {
		128 * 1024 * 1024, 	/* initialChunkSize */
		16 * 1024 * 1024, 	/* incrementalChunkSize */
		8 * 1024 * 1024, 		/* initialHeapCount */
		1 * 1024 * 1024, 		/* incrementalHeapCount */
		4096, 		/* stackCount */
		4096*3, 		/* keyCount */
		1993, 		/* nameModulo */
		127 		/* symbolModulo */
	};
	xsCreation* creation = &creation_tool;
	int error = 0;
	int argi = 1;
	void* archive = NULL;
	xsBooleanValue program = 0;
	xsBooleanValue xsbug = 0;
	xsMachine* machine;
	char path[PATH_MAX];
	char modulePath[PATH_MAX];
	xsStringValue extension;
	xsStringValue slash;
	xsStringValue name;
	int size;
	if (argi < argc) {
		if (!strcmp(argv[argi], "-a")) {
			argi++;
			if (argi < argc) {
                if (realpath(argv[argi], path)) {
                	archive = fxMapArchive(path, NULL);
                    if (!archive) {
                        fprintf(stderr, "# invalid archive: %s\n", path);
                        return 1;
                    }
                    if (strstr(path, "mc.xsa")) {
                  		creation = &creation_mc;
                    }
                }
				else {
					fprintf(stderr, "# archive not found: %s\n", argv[argi]);
					return 1;
				}
				argi++;
			}
		}
	}
	while (argi < argc) {
		if (!strcmp(argv[argi], "-p")) {
			program = 1;
			argi++;
		}
		else if (!strcmp(argv[argi], "-x")) {
			xsbug = 1;
			argi++;
		}
		else
			break;
	}
	gargc = argc;
	gargi = argi;
	gargv = argv;
	machine = xsCreateMachine(creation, archive, "xsr6", NULL);
	xsBeginHost(machine);
	{
		xsVars(2);
		//xsStartProfiling();
		{
			xsTry {
				xsVar(0) = xsNewInstanceOf(xsObjectPrototype);
				if (xsbug)
					xsVar(1) = xsNewHostFunction(console_log_xsbug, 0);
				else
					xsVar(1) = xsNewHostFunction(console_log, 0);
				xsSet(xsVar(0), xsID("log"), xsVar(1));
				xsSet(xsGlobal, xsID("console"), xsVar(0));

				xsVar(0) = xsNewHostObject(weakTest);
				xsVar(1) = xsNewHostConstructor(WeakTest, 1, xsVar(0));
				xsSet(xsGlobal, xsID("WeakTest"), xsVar(1));
				xsVar(1) = xsNewHostFunction(gc, 0);
				xsSet(xsGlobal, xsID("gc"), xsVar(1));

				xsResult = xsModulePaths();
				if (archive) {
					slash = strrchr(path, mxSeparator);
					if (slash) {
						*(slash + 1) = 0;
						xsCall1(xsResult, xsID("add"), xsString(path));
					}
				}
				realpath(argv[0], modulePath);
				slash = strrchr(modulePath, mxSeparator);
				if (slash) {
					strcpy(slash + 1, "modules");
					size = c_strlen(modulePath);
					modulePath[size++] = mxSeparator;
					modulePath[size] = 0;
					xsCall1(xsResult, xsID("add"), xsString(modulePath));
				}

				if (argi == argc) {
					fprintf(stderr, "# no module, no program\n");
					error = 1;
				}	
				else if (program) {
					xsVar(0) = xsNewHostFunction(print, 0);
					xsSet(xsGlobal, xsID("print"), xsVar(0));
					xsStartProfiling();
					while (argi < argc) {
						if (argv[argi][0] != '-') {
							xsElseError(realpath(argv[argi], path));
							strcpy(modulePath, path);
							slash = strrchr(modulePath, mxSeparator);
							*(slash + 1) = 0;
							xsCall1(xsResult, xsID("add"), xsString(modulePath));
							strcat(modulePath, "modules/");
							xsCall1(xsResult, xsID("add"), xsString(modulePath));
							fxRunProgram(the, path);
						}
						argi++;
					}
					fxRunLoop(the);
					xsStopProfiling();
				}
				else {
					xsVar(0) = xsNewInstanceOf(xsObjectPrototype);
					xsVar(1) = xsNewHostFunction(process_cwd, 0);
					xsSet(xsVar(0), xsID("cwd"), xsVar(1));
				#ifdef mxDebug
					xsSet(xsVar(0), xsID("debug"), xsTrue);
				#else
					xsSet(xsVar(0), xsID("debug"), xsFalse);
				#endif
					xsVar(1) = xsNewHostFunction(process_execArgv, 0);
					xsSet(xsVar(0), xsID("execArgv"), xsVar(1));
					xsVar(1) = xsNewHostFunction(process_getenv, 0);
					xsSet(xsVar(0), xsID("getenv"), xsVar(1));
					xsVar(1) = xsNewHostFunction(process_then, 1);
					xsSet(xsVar(0), xsID("then"), xsVar(1));
					xsSet(xsVar(0), xsID("platform"), xsString("darwin"));
					xsSet(xsGlobal, xsID("process"), xsVar(0));
		
					strcpy(path, argv[argi]);
					slash = strrchr(path, mxSeparator);
					if (slash) {
						*slash = 0;
						realpath(path, modulePath);
						size = c_strlen(modulePath);
						modulePath[size++] = mxSeparator;
						modulePath[size] = 0;
						xsCall1(xsResult, xsID("add"), xsString(modulePath));
						strcat(modulePath, "modules");
						size = c_strlen(modulePath);
						modulePath[size++] = mxSeparator;
						modulePath[size] = 0;
						xsCall1(xsResult, xsID("add"), xsString(modulePath));
						name = slash + 1;
					
					}
					else {
						realpath(".", modulePath);
						size = c_strlen(modulePath);
						modulePath[size++] = mxSeparator;
						modulePath[size] = 0;
						xsCall1(xsResult, xsID("add"), xsString(modulePath));
						strcat(modulePath, "modules");
						size = c_strlen(modulePath);
						modulePath[size++] = mxSeparator;
						modulePath[size] = 0;
						xsCall1(xsResult, xsID("add"), xsString(modulePath));
						name = path;
					}
					extension = strrchr(name, '.');
					if (extension)
						*extension = 0;
					xsStartProfiling();
					fxRunModule(the, name);
					xsStopProfiling();
				}
			}
			xsCatch {
				xsStringValue message = xsToString(xsException);
				fprintf(stderr, "### %s\n", message);
				error = 1;
			}
		}
		//xsStopProfiling();
	}
	xsEndHost(the);
	xsDeleteMachine(machine);
	fxUnmapArchive(archive);
	if (!error && process_then_parameters) {
	#if mxWindows
		if (_spawnvp(_P_WAIT, process_then_parameters[0], process_then_parameters) < 0)
			fprintf(stderr, "### Cannot execute %s!\n", process_then_parameters[0]);
	#else
		execvp(process_then_parameters[0], process_then_parameters);
	#endif
	}
	return error;
}