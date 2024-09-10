int
main(int argc, char *argv[], char *envp[])
{
#ifdef LISP_FEATURE_WIN32
    /* Exception handling support structure. Evil Win32 hack. */
    struct lisp_exception_frame exception_frame;
#endif

    /* the name of the core file we're to execute. Note that this is
     * a malloc'ed string which should be freed eventually. */
    char *core = 0;
    char **sbcl_argv = 0;
    os_vm_offset_t embedded_core_offset = 0;
    char *runtime_path = 0;

    /* other command line options */
    boolean noinform = 0;
    boolean end_runtime_options = 0;
    boolean disable_lossage_handler_p = 0;

    lispobj initial_function;
    const char *sbcl_home = getenv("SBCL_HOME");

    interrupt_init();
    block_blockable_signals(0, 0);

    setlocale(LC_ALL, "");

    runtime_options = NULL;

    /* Check early to see if this executable has an embedded core,
     * which also populates runtime_options if the core has runtime
     * options */
    runtime_path = os_get_runtime_executable_path();
    if (runtime_path) {
        os_vm_offset_t offset = search_for_embedded_core(runtime_path);
        if (offset != -1) {
            embedded_core_offset = offset;
            core = runtime_path;
        } else {
            free(runtime_path);
        }
    }


    /* Parse our part of the command line (aka "runtime options"),
     * stripping out those options that we handle. */
    if (runtime_options != NULL) {
        dynamic_space_size = runtime_options->dynamic_space_size;
        thread_control_stack_size = runtime_options->thread_control_stack_size;
        sbcl_argv = argv;
    } else {
        int argi = 1;

        runtime_options = successful_malloc(sizeof(struct runtime_options));

        while (argi < argc) {
            char *arg = argv[argi];
            if (0 == strcmp(arg, "--script")) {
                /* This is both a runtime and a toplevel option. As a
                 * runtime option, it is equivalent to --noinform.
                 * This exits, and does not increment argi, so that
                 * TOPLEVEL-INIT sees the option. */
                noinform = 1;
                end_runtime_options = 1;
                disable_lossage_handler_p = 1;
                lose_on_corruption_p = 1;
                break;
            } else if (0 == strcmp(arg, "--noinform")) {
                noinform = 1;
                ++argi;
            } else if (0 == strcmp(arg, "--core")) {
                if (core) {
                    lose("more than one core file specified\n");
                } else {
                    ++argi;
                    if (argi >= argc) {
                        lose("missing filename for --core argument\n");
                    }
                    core = copied_string(argv[argi]);
                    ++argi;
                }
            } else if (0 == strcmp(arg, "--help")) {
                /* I think this is the (or a) usual convention: upon
                 * seeing "--help" we immediately print our help
                 * string and exit, ignoring everything else. */
                print_help();
                exit(0);
            } else if (0 == strcmp(arg, "--version")) {
                /* As in "--help" case, I think this is expected. */
                print_version();
                exit(0);
            } else if (0 == strcmp(arg, "--dynamic-space-size")) {
                ++argi;
                if (argi >= argc)
                    lose("missing argument for --dynamic-space-size");
                errno = 0;
                dynamic_space_size = strtol(argv[argi++], 0, 0) << 20;
                if (errno)
                    lose("argument to --dynamic-space-size is not a number");
#               ifdef MAX_DYNAMIC_SPACE_END
                if (!((DYNAMIC_SPACE_START <
                       DYNAMIC_SPACE_START+dynamic_space_size) &&
                      (DYNAMIC_SPACE_START+dynamic_space_size <=
                       MAX_DYNAMIC_SPACE_END)))
                    lose("specified --dynamic-space-size too large");
#               endif
            } else if (0 == strcmp(arg, "--control-stack-size")) {
                ++argi;
                if (argi >= argc)
                    lose("missing argument for --control-stack-size");
                errno = 0;
                thread_control_stack_size = strtol(argv[argi++], 0, 0) << 20;
                if (errno)
                    lose("argument to --control-stack-size is not a number");
            } else if (0 == strcmp(arg, "--debug-environment")) {
                int n = 0;
                printf("; Commandline arguments:\n");
                while (n < argc) {
                    printf(";  %2d: \"%s\"\n", n, argv[n]);
                    ++n;
                }
                n = 0;
                printf(";\n; Environment:\n");
                while (ENVIRON[n]) {
                    printf(";  %2d: \"%s\"\n", n, ENVIRON[n]);
                    ++n;
                }
                ++argi;
            } else if (0 == strcmp(arg, "--disable-ldb")) {
                disable_lossage_handler_p = 1;
                ++argi;
            } else if (0 == strcmp(arg, "--lose-on-corruption")) {
                lose_on_corruption_p = 1;
                ++argi;
            } else if (0 == strcmp(arg, "--end-runtime-options")) {
                end_runtime_options = 1;
                ++argi;
                break;
            } else {
                /* This option was unrecognized as a runtime option,
                 * so it must be a toplevel option or a user option,
                 * so we must be past the end of the runtime option
                 * section. */
                break;
            }
        }
        /* This is where we strip out those options that we handle. We
         * also take this opportunity to make sure that we don't find
         * an out-of-place "--end-runtime-options" option. */
        {
            char *argi0 = argv[argi];
            int argj = 1;
            /* (argc - argi) for the arguments, one for the binary,
               and one for the terminating NULL. */
            sbcl_argv = successful_malloc((2 + argc - argi) * sizeof(char *));
            sbcl_argv[0] = argv[0];
            while (argi < argc) {
                char *arg = argv[argi++];
                /* If we encounter --end-runtime-options for the first
                 * time after the point where we had to give up on
                 * runtime options, then the point where we had to
                 * give up on runtime options must've been a user
                 * error. */
                if (!end_runtime_options &&
                    0 == strcmp(arg, "--end-runtime-options")) {
                    lose("bad runtime option \"%s\"\n", argi0);
                }
                sbcl_argv[argj++] = arg;
            }
            sbcl_argv[argj] = 0;
        }
    }

    /* Align down to multiple of page_table page size, and to the appropriate
     * stack alignment. */
    dynamic_space_size &= ~(PAGE_BYTES-1);
    thread_control_stack_size &= ~(CONTROL_STACK_ALIGNMENT_BYTES-1);

    /* Preserve the runtime options for possible future core saving */
    runtime_options->dynamic_space_size = dynamic_space_size;
    runtime_options->thread_control_stack_size = thread_control_stack_size;

    /* KLUDGE: os_vm_page_size is set by os_init(), and on some
     * systems (e.g. Alpha) arch_init() needs need os_vm_page_size, so
     * it must follow os_init(). -- WHN 2000-01-26 */
    os_init(argv, envp);
    arch_init();
    gc_init();
    validate();

    /* If no core file was specified, look for one. */
    if (!core) {
        core = search_for_core();
    }

    /* Make sure that SBCL_HOME is set and not the empty string,
       unless loading an embedded core. */
    if (!(sbcl_home && *sbcl_home) && embedded_core_offset == 0) {
        char *envstring, *copied_core, *dir;
        char *stem = "SBCL_HOME=";
        copied_core = copied_string(core);
        dir = dirname(copied_core);
        envstring = (char *) calloc(strlen(stem) +
                                    strlen(dir) +
                                    1,
                                    sizeof(char));
        sprintf(envstring, "%s%s", stem, dir);
        putenv(envstring);
        free(copied_core);
    }

    if (!noinform && embedded_core_offset == 0) {
        print_banner();
        fflush(stdout);
    }

#if defined(SVR4) || defined(__linux__)
    tzset();
#endif

    define_var("nil", NIL, 1);
    define_var("t", T, 1);

    if (!disable_lossage_handler_p)
        enable_lossage_handler();

    globals_init();

    initial_function = load_core_file(core, embedded_core_offset);
    if (initial_function == NIL) {
        lose("couldn't find initial function\n");
    }
#ifdef LISP_FEATURE_HPUX
    /* -1 = CLOSURE_FUN_OFFSET, 23 = SIMPLE_FUN_CODE_OFFSET, we are
     * not in LANGUAGE_ASSEMBLY so we cant reach them. */
    return_from_lisp_stub = (void *) ((char *)*((unsigned long *)
                 ((char *)initial_function + -1)) + 23);
#endif

    gc_initialize_pointers();

    arch_install_interrupt_handlers();
#ifndef LISP_FEATURE_WIN32
    os_install_interrupt_handlers();
#else
/*     wos_install_interrupt_handlers(handler); */
    wos_install_interrupt_handlers(&exception_frame);
#endif

    /* Pass core filename and the processed argv into Lisp. They'll
     * need to be processed further there, to do locale conversion.
     */
    core_string = core;
    posix_argv = sbcl_argv;

    FSHOW((stderr, "/funcalling initial_function=0x%lx\n",
          (unsigned long)initial_function));
#ifdef LISP_FEATURE_WIN32
    fprintf(stderr, "\n\
This is experimental prerelease support for the Windows platform: use\n\
at your own risk.  \"Your Kitten of Death awaits!\"\n");
    fflush(stdout);
    fflush(stderr);
#endif
    create_initial_thread(initial_function);
    lose("CATS.  CATS ARE NICE.\n");
    return 0;
}