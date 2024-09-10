extern int
main(int argc, char* argv[]) {
    const char *encoding = NULL;
    const char *outputDir = NULL; /* NULL = no output directory, use current */
    const char *inputDir  = ".";
    int tostdout = 0;
    int prbom = 0;

    const char *pname;

    UResourceBundle *bundle = NULL;
    UErrorCode status = U_ZERO_ERROR;
    int32_t i = 0;

    UConverter *converter;

    const char* arg;

    /* Get the name of tool. */
    pname = uprv_strrchr(*argv, U_FILE_SEP_CHAR);
#if U_FILE_SEP_CHAR != U_FILE_ALT_SEP_CHAR
    if (!pname) {
        pname = uprv_strrchr(*argv, U_FILE_ALT_SEP_CHAR);
    }
#endif
    if (!pname) {
        pname = *argv;
    } else {
        ++pname;
    }

    /* error handling, printing usage message */
    argc=u_parseArgs(argc, argv, sizeof(options)/sizeof(options[0]), options);

    /* error handling, printing usage message */
    if(argc<0) {
        fprintf(stderr,
            "%s: error in command line argument \"%s\"\n", pname,
            argv[-argc]);
    }
    if(argc<0 || options[0].doesOccur || options[1].doesOccur) {
        fprintf(argc < 0 ? stderr : stdout,
            "%csage: %s [ -h, -?, --help ] [ -V, --version ]\n"
            " [ -v, --verbose ] [ -e, --encoding encoding ] [ --bom ]\n"
            " [ -t, --truncate [ size ] ]\n"
            " [ -s, --sourcedir source ] [ -d, --destdir destination ]\n"
            " [ -i, --icudatadir directory ] [ -c, --to-stdout ]\n"
            " [ -A, --suppressAliases]\n"
            " bundle ...\n", argc < 0 ? 'u' : 'U',
            pname);
        return argc<0 ? U_ILLEGAL_ARGUMENT_ERROR : U_ZERO_ERROR;
    }

    if(options[10].doesOccur) {
        fprintf(stderr,
                "%s version %s (ICU version %s).\n"
                "%s\n",
                pname, DERB_VERSION, U_ICU_VERSION, U_COPYRIGHT_STRING);
        return U_ZERO_ERROR;
    }
    if(options[2].doesOccur) {
        encoding = options[2].value;
    }

    if (options[3].doesOccur) {
        tostdout = 1;
    }

    if(options[4].doesOccur) {
        trunc = TRUE;
        if(options[4].value != NULL) {
            truncsize = atoi(options[4].value); /* user defined printable size */
        } else {
            truncsize = DERB_DEFAULT_TRUNC; /* we'll use default omitting size */
        }
    } else {
        trunc = FALSE;
    }

    if(options[5].doesOccur) {
        verbose = TRUE;
    }

    if (options[6].doesOccur) {
        outputDir = options[6].value;
    }

    if(options[7].doesOccur) {
        inputDir = options[7].value; /* we'll use users resources */
    }

    if (options[8].doesOccur) {
        prbom = 1;
    }

    if (options[9].doesOccur) {
        u_setDataDirectory(options[9].value);
    }

    if (options[11].doesOccur) {
      suppressAliases = TRUE;
    }

    converter = ucnv_open(encoding, &status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "%s: couldn't create %s converter for encoding\n", pname, encoding ? encoding : ucnv_getDefaultName());
        return 2;
    }
    ucnv_setFromUCallBack(converter, UCNV_FROM_U_CALLBACK_ESCAPE, UCNV_ESCAPE_C, 0, 0, &status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "%s: couldn't configure converter for encoding\n", pname);
        return 3;
    }

    defaultConverter = ucnv_open(0, &status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "%s: couldn't create %s converter for encoding\n", ucnv_getDefaultName(), pname);
        return 2;
    }

    for (i = 1; i < argc; ++i) {
        static const UChar sp[] = { 0x0020 }; /* " " */
        char infile[4096]; /* XXX Sloppy. */
        char locale[64];
        const char *thename = 0, *p, *q;
        UBool fromICUData = FALSE;

        arg = getLongPathname(argv[i]);

        if (verbose) {
            printf("processing bundle \"%s\"\n", argv[i]);
        }

        p = uprv_strrchr(arg, U_FILE_SEP_CHAR);
#if U_FILE_SEP_CHAR != U_FILE_ALT_SEP_CHAR
        if (p == NULL) {
            p = uprv_strrchr(arg, U_FILE_ALT_SEP_CHAR);
        }
#endif
        if (!p) {
            p = arg;
        } else {
            p++;
        }
        q = uprv_strrchr(p, '.');
        if (!q) {
            for (q = p; *q; ++q)
                ;
        }
        uprv_strncpy(locale, p, q - p);
        locale[q - p] = 0;

        if (!(fromICUData = !uprv_strcmp(inputDir, "-"))) {
            UBool absfilename = *arg == U_FILE_SEP_CHAR;
#ifdef U_WINDOWS
            if (!absfilename) {
                absfilename = (uprv_strlen(arg) > 2 && isalpha(arg[0])
                    && arg[1] == ':' && arg[2] == U_FILE_SEP_CHAR);
            }
#endif
            if (absfilename) {
                thename = arg;
            } else {
                q = uprv_strrchr(arg, U_FILE_SEP_CHAR);
#if U_FILE_SEP_CHAR != U_FILE_ALT_SEP_CHAR
                if (q == NULL) {
                    q = uprv_strrchr(arg, U_FILE_ALT_SEP_CHAR);
                }
#endif
                uprv_strcpy(infile, inputDir);
                if(q != NULL) {
                    uprv_strcat(infile, U_FILE_SEP_STRING);
                    strncat(infile, arg, q-arg);
                }
                thename = infile;
            }
        }
        status = U_ZERO_ERROR;
        if (thename) {
            bundle = ures_openDirect(thename, locale, &status);
        } else {
            bundle = ures_open(fromICUData ? 0 : inputDir, locale, &status);
        }
        if (status == U_ZERO_ERROR) {
            FILE *out;

            const char *filename = 0;
            const char *ext = 0;

            if (!locale || !tostdout) {
                filename = uprv_strrchr(arg, U_FILE_SEP_CHAR);

#if U_FILE_SEP_CHAR != U_FILE_ALT_SEP_CHAR
                if (!filename) {
                    filename = uprv_strrchr(arg, U_FILE_ALT_SEP_CHAR);
                }
#endif
                if (!filename) {
                    filename = arg;
                } else {
                    ++filename;
                }
                ext = uprv_strrchr(arg, '.');
                if (!ext) {
                    ext = filename + uprv_strlen(filename);
                }
            }

            if (tostdout) {
                out = stdout;
#if defined(U_WINDOWS) || defined(U_CYGWIN)
                if (setmode(fileno(out), O_BINARY) == -1) {
                    fprintf(stderr, "%s: couldn't set standard output to binary mode\n", pname);
                    return 4;
                }
#endif
            } else {
                char thefile[4096], *tp;
                int32_t len;

                if (outputDir) {
                    uprv_strcpy(thefile, outputDir);
                    uprv_strcat(thefile, U_FILE_SEP_STRING);
                } else {
                    *thefile = 0;
                }
                uprv_strcat(thefile, filename);
                tp = thefile + uprv_strlen(thefile);
                len = (int32_t)uprv_strlen(ext);
                if (len) {
                    tp -= len - 1;
                } else {
                    *tp++ = '.';
                }
                uprv_strcpy(tp, "txt");

                out = fopen(thefile, "w");
                if (!out) {
                    fprintf(stderr, "%s: couldn't create %s\n", pname, thefile);
                    return 4;
                }
            }

            if (prbom) { /* XXX: Should be done only for UTFs */
                static const UChar bom[] = { 0xFEFF };
                printString(out, converter, bom, (int32_t)(sizeof(bom)/sizeof(*bom)));
            }

            printCString(out, converter, "// -*- Coding: ", -1);
            printCString(out, converter, encoding ? encoding : getEncodingName(ucnv_getDefaultName()), -1);
            printCString(out, converter, "; -*-\n//\n", -1);
            printCString(out, converter, "// This file was dumped by derb(8) from ", -1);
            if (thename) {
                printCString(out, converter, thename, -1);
            } else if (fromICUData) {
                printCString(out, converter, "the ICU internal ", -1);
                printCString(out, converter, locale, -1);
                printCString(out, converter, " locale", -1);
            }

            printCString(out, converter, "\n// derb(8) by Vladimir Weinstein and Yves Arrouye\n\n", -1);

            if (locale) {
                printCString(out, converter, locale, -1);
            } else {
                printCString(out, converter, filename, (int32_t)(ext - filename));
                printString(out, converter, sp, (int32_t)(sizeof(sp)/sizeof(*sp)));
            }
            printOutBundle(out, converter, bundle, 0, pname, &status);

            if (out != stdout) {
                fclose(out);
            }
        }
        else {
            reportError(pname, &status, "opening resource file");
        }

        ures_close(bundle);
    }

    ucnv_close(defaultConverter);
    ucnv_close(converter);

    return 0;
}