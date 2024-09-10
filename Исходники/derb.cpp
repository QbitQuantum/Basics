extern int
main(int argc, char* argv[]) {
    const char *encoding = NULL;
    const char *outputDir = NULL; /* NULL = no output directory, use current */
    const char *inputDir  = ".";
    int tostdout = 0;
    int prbom = 0;

    const char *pname;

    UResourceBundle *bundle = NULL;
    int32_t i = 0;

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
    argc=u_parseArgs(argc, argv, UPRV_LENGTHOF(options), options);

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
      if(options[2].doesOccur) {
        fprintf(stderr, "%s: Error: don't specify an encoding (-e) when writing to stdout (-c).\n", pname);
        return 3;
      }
      tostdout = 1;
    }

    if(options[4].doesOccur) {
        opt_truncate = TRUE;
        if(options[4].value != NULL) {
            truncsize = atoi(options[4].value); /* user defined printable size */
        } else {
            truncsize = DERB_DEFAULT_TRUNC; /* we'll use default omitting size */
        }
    } else {
        opt_truncate = FALSE;
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

    fflush(stderr); // use ustderr now.
    ustderr = u_finit(stderr, NULL, NULL);

    for (i = 1; i < argc; ++i) {
        static const UChar sp[] = { 0x0020 }; /* " " */

        arg = getLongPathname(argv[i]);

        if (verbose) {
          u_fprintf(ustderr, "processing bundle \"%s\"\n", argv[i]);
        }

        icu::CharString locale;
        UErrorCode status = U_ZERO_ERROR;
        {
            const char *p = findBasename(arg);
            const char *q = uprv_strrchr(p, '.');
            if (q == NULL) {
                locale.append(p, status);
            } else {
                locale.append(p, (int32_t)(q - p), status);
            }
        }
        if (U_FAILURE(status)) {
            return status;
        }

        icu::CharString infile;
        const char *thename = NULL;
        UBool fromICUData = !uprv_strcmp(inputDir, "-");
        if (!fromICUData) {
            UBool absfilename = *arg == U_FILE_SEP_CHAR;
#if U_PLATFORM_HAS_WIN32_API
            if (!absfilename) {
                absfilename = (uprv_strlen(arg) > 2 && isalpha(arg[0])
                    && arg[1] == ':' && arg[2] == U_FILE_SEP_CHAR);
            }
#endif
            if (absfilename) {
                thename = arg;
            } else {
                const char *q = uprv_strrchr(arg, U_FILE_SEP_CHAR);
#if U_FILE_SEP_CHAR != U_FILE_ALT_SEP_CHAR
                if (q == NULL) {
                    q = uprv_strrchr(arg, U_FILE_ALT_SEP_CHAR);
                }
#endif
                infile.append(inputDir, status);
                if(q != NULL) {
                    infile.appendPathPart(icu::StringPiece(arg, (int32_t)(q - arg)), status);
                }
                if (U_FAILURE(status)) {
                    return status;
                }
                thename = infile.data();
            }
        }
        if (thename) {
            bundle = ures_openDirect(thename, locale.data(), &status);
        } else {
            bundle = ures_open(fromICUData ? 0 : inputDir, locale.data(), &status);
        }
        if (U_SUCCESS(status)) {
            UFILE *out = NULL;

            const char *filename = 0;
            const char *ext = 0;

            if (locale.isEmpty() || !tostdout) {
                filename = findBasename(arg);
                ext = uprv_strrchr(filename, '.');
                if (!ext) {
                    ext = uprv_strchr(filename, 0);
                }
            }

            if (tostdout) {
                out = u_get_stdout();
            } else {
                icu::CharString thefile;
                if (outputDir) {
                    thefile.append(outputDir, status);
                }
                thefile.appendPathPart(filename, status);
                if (*ext) {
                    thefile.truncate(thefile.length() - (int32_t)uprv_strlen(ext));
                }
                thefile.append(".txt", status);
                if (U_FAILURE(status)) {
                    return status;
                }

                out = u_fopen(thefile.data(), "w", NULL, encoding);
                if (!out) {
                  u_fprintf(ustderr, "%s: couldn't create %s\n", pname, thefile.data());
                  u_fclose(ustderr);
                  return 4;
                }
            }

            // now, set the callback.
            ucnv_setFromUCallBack(u_fgetConverter(out), UCNV_FROM_U_CALLBACK_ESCAPE, UCNV_ESCAPE_C, 0, 0, &status);
            if (U_FAILURE(status)) {
              u_fprintf(ustderr, "%s: couldn't configure converter for encoding\n", pname);
              u_fclose(ustderr);
              if(!tostdout) {
                u_fclose(out);
              }
              return 3;
            }

            if (prbom) { /* XXX: Should be done only for UTFs */
              u_fputc(0xFEFF, out);
            }
            u_fprintf(out, "// -*- Coding: %s; -*-\n//\n", encoding ? encoding : getEncodingName(ucnv_getDefaultName()));
            u_fprintf(out, "// This file was dumped by derb(8) from ");
            if (thename) {
              u_fprintf(out, "%s", thename);
            } else if (fromICUData) {
              u_fprintf(out, "the ICU internal %s locale", locale.data());
            }

            u_fprintf(out, "\n// derb(8) by Vladimir Weinstein and Yves Arrouye\n\n");

            if (!locale.isEmpty()) {
              u_fprintf(out, "%s", locale.data());
            } else {
              u_fprintf(out, "%.*s%.*S", (int32_t)(ext - filename),  filename, UPRV_LENGTHOF(sp), sp);
            }
            printOutBundle(out, bundle, 0, pname, &status);

            if (!tostdout) {
                u_fclose(out);
            }
        }
        else {
            reportError(pname, &status, "opening resource file");
        }

        ures_close(bundle);
    }

    return 0;
}