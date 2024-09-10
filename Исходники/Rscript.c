int main(int argc, char *argv[])
{
#ifdef HAVE_EXECV
    char cmd[PATH_MAX+1], buf[PATH_MAX+8], buf2[1100], *p;
    int i, i0 = 0, ac = 0, res = 0, e_mode = 0, set_dp = 0;
    char **av;

    if(argc <= 1) {
        usage();
        exit(1);
    }
    av = (char **) malloc((size_t) (argc+4)*sizeof(char *));
    if(!av) {
        fprintf(stderr, "malloc failure\n");
        exit(1);
    }

    p = getenv("RHOME");
#ifdef _WIN32
    if(p && *p)
        snprintf(cmd, PATH_MAX+1, "%s\\%s\\Rterm.exe",  p, BINDIR);
    else {
        char rhome[MAX_PATH];
        GetModuleFileName(NULL, rhome, MAX_PATH);
        p = strrchr(rhome,'\\');
        if(!p) {
            fprintf(stderr, "installation problem\n");
            exit(1);
        }
        *p = '\0';
        snprintf(cmd, PATH_MAX+1, "%s\\Rterm.exe",  rhome);
    }
#else
    if(!(p && *p)) p = rhome;
    /* avoid snprintf here */
    if(strlen(p) + 6 > PATH_MAX) {
        fprintf(stderr, "impossibly long path for RHOME\n");
        exit(1);
    }
    snprintf(cmd, PATH_MAX+1, "%s/bin/R", p);
#endif
    av[ac++] = cmd;
    av[ac++] = "--slave";
    av[ac++] = "--no-restore";

    if(argc == 2) {
        if(strcmp(argv[1], "--help") == 0) {
            usage();
            exit(0);
        }
        if(strcmp(argv[1], "--version") == 0) {
            if(strlen(R_STATUS) == 0)
                fprintf(stderr, "R scripting front-end version %s.%s (%s-%s-%s)\n",
                        R_MAJOR, R_MINOR, R_YEAR, R_MONTH, R_DAY);
            else
                fprintf(stderr, "R scripting front-end version %s.%s %s (%s-%s-%s r%s)\n",
                        R_MAJOR, R_MINOR, R_STATUS, R_YEAR, R_MONTH, R_DAY,
                        R_GIT_REVISION);
            exit(0);
        }
    }

    /* first copy over any -e or --foo args */
    for(i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-e") == 0) {
            e_mode = 1;
            av[ac++] = argv[i];
            if(!argv[++i]) {
                fprintf(stderr, "-e not followed by an expression\n");
                exit(1);
            }
            av[ac++] = argv[i];
            i0 = i;
            continue;
        }
        if(strncmp(argv[i], "--", 2) != 0) break;
        if(strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
            i0 = i;
            continue;
        }
        if(strncmp(argv[i], "--default-packages=", 18) == 0) {
            set_dp = 1;
            if(strlen(argv[i]) > 1000) {
                fprintf(stderr, "unable to set R_DEFAULT_PACKAGES\n");
                exit(1);
            }
            snprintf(buf2, 1100, "R_DEFAULT_PACKAGES=%s", argv[i]+19);
            if(verbose)
                fprintf(stderr, "setting '%s'\n", buf2);
#ifdef HAVE_PUTENV
            if(putenv(buf2))
#endif
            {
                fprintf(stderr, "unable to set R_DEFAULT_PACKAGES\n");
                exit(1);
            }
            i0 = i;
            continue;
        }
        av[ac++] = argv[i];
        i0 = i;
    }

    if(!e_mode) {
        if(++i0 >= argc) {
            fprintf(stderr, "file name is missing\n");
            exit(1);
        }
        if(strlen(argv[i0]) > PATH_MAX) {
            fprintf(stderr, "file name is too long\n");
            exit(1);
        }
        snprintf(buf, PATH_MAX+8, "--file=%s", argv[i0]);
        av[ac++] = buf;
    }
    // copy any user arguments, preceded by "--args"
    i = i0+1;
    if (i < argc) {
        av[ac++] = "--args";
        for(; i < argc; i++)
            av[ac++] = argv[i];
    }
    av[ac] = (char *) NULL;
#ifdef HAVE_PUTENV
    if(!set_dp && !getenv("R_DEFAULT_PACKAGES"))
        putenv("R_DEFAULT_PACKAGES=datasets,utils,grDevices,graphics,stats");

#ifndef _WIN32
    /* pass on r_arch from this binary to R as a default */
    if (!getenv("R_ARCH") && *rarch) {
        /* we have to prefix / so we may as well use putenv */
        if (strlen(rarch) + 9 > sizeof(buf2)) {
            fprintf(stderr, "impossibly long string for R_ARCH\n");
            exit(1);
        }
        strcpy(buf2, "R_ARCH=/");
        strcat(buf2, rarch);
        putenv(buf2);
    }
#endif
#endif
    if(verbose) {
        fprintf(stderr, "running\n  '%s", cmd);
        for(i = 1; i < ac; i++) fprintf(stderr, " %s", av[i]);
        fprintf(stderr, "'\n\n");
    }
#ifndef _WIN32
    res = execv(cmd, av); /* will not return if R is launched */
    perror("Rscript execution error");
#else
    AppMain(ac, av);
#endif
    return res;
#else /* No execv*/
    fprintf(stderr, "Rscript is not supported on this system");
    exit(1);
#endif
}