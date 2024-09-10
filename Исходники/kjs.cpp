static ExitCode parseArgs(int argc, char **argv)
{
    JSLock lock;

    GlobalImp *global = new GlobalImp();

    // create interpreter
    RefPtr<Interpreter> interp = new Interpreter(global);

    // add some global extension functions
    ExecState *gexec = interp->globalExec();
    global->put(gexec, "print",
                new TestFunctionImp(TestFunctionImp::Print, 1));
    global->put(gexec, "quit",
                new TestFunctionImp(TestFunctionImp::Quit, 0));
    global->put(gexec, "load",
                new TestFunctionImp(TestFunctionImp::Load, 1));
    global->put(gexec, "gc",
                new TestFunctionImp(TestFunctionImp::GC, 0));

    // enable package support
    StandardGlobalPackage package;
    interp->setGlobalPackage(&package);

    const char *script = 0, *command = 0;
    int ai = 1;
    bool ranOtherScript = false;
    for (ai = 1; ai < argc; ++ai) {
        const char *a = argv[ai];
        if (strcmp(a, "-v") == 0 || strcmp(a, "-version") == 0 ||
                strcmp(a, "--version") == 0) {
            printf("KDE: %s\n", KJS_VERSION_STRING);
            return ErrorNone;
        } else if (strcmp(a, "-h") == 0 || strcmp(a, "-help") == 0 ||
                   strcmp(a, "--help") == 0) {
            printUsage(argv[0]);
            return ErrorNone;
        } else if (strcmp(a, "-e") == 0) {
            ++ai;
            if (argc <= ai) {
                fprintf(stderr, "Missing -e argument.\n");
                return ErrorMissingArg;
            }
            command = argv[ai];
            ++ai;
            break;
        } else if (strcmp(a, "-f") == 0) { // Compatibility mode, for SunSpider
            ++ai;
            if (argc <= ai) {
                fprintf(stderr, "Missing -f argument.\n");
                return ErrorMissingArg;
            }
            ExitCode result = evaluateFile(interp.get(), argv[ai]);
            if (result != ErrorNone) {
                return result;
            }
            ranOtherScript = true;
        } else if (a[0] == '-') {
            fprintf(stderr, "Unknown switch %s.\n", a);
            return ErrorUnknownSwitch;
        } else {
            script = a;
            ++ai;
            break;
        }
    }

    // ###
    if (argc > ai) {
        fprintf(stderr, "Warning: ignoring extra arguments\n");
    }

    if (script) {
        return evaluateFile(interp.get(), script);
    } else if (command) {
        return evaluateString(interp.get(), "(eval)", command);
    } else if (!ranOtherScript) {
        return evaluateInteractive(interp.get());
    }
    return ErrorNone;
}