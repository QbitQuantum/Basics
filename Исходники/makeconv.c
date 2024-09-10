int main(int argc, char* argv[])
{
    ConvData data;
    UErrorCode err = U_ZERO_ERROR, localError;
    char outFileName[UCNV_MAX_FULL_FILE_NAME_LENGTH];
    const char* destdir, *arg;
    size_t destdirlen;
    char* dot = NULL, *outBasename;
    char cnvName[UCNV_MAX_FULL_FILE_NAME_LENGTH];
    char cnvNameWithPkg[UCNV_MAX_FULL_FILE_NAME_LENGTH];
    UVersionInfo icuVersion;
    UBool printFilename;

    err = U_ZERO_ERROR;

    U_MAIN_INIT_ARGS(argc, argv);

    /* Set up the ICU version number */
    u_getVersion(icuVersion);
    uprv_memcpy(&dataInfo.dataVersion, &icuVersion, sizeof(UVersionInfo));

    /* preset then read command line options */
    options[OPT_DESTDIR].value=u_getDataDirectory();
    argc=u_parseArgs(argc, argv, LENGTHOF(options), options);

    /* error handling, printing usage message */
    if(argc<0) {
        fprintf(stderr,
            "error in command line argument \"%s\"\n",
            argv[-argc]);
    } else if(argc<2) {
        argc=-1;
    }
    if(argc<0 || options[OPT_HELP_H].doesOccur || options[OPT_HELP_QUESTION_MARK].doesOccur) {
        FILE *stdfile=argc<0 ? stderr : stdout;
        fprintf(stdfile,
            "usage: %s [-options] files...\n"
            "\tread .ucm codepage mapping files and write .cnv files\n"
            "options:\n"
            "\t-h or -? or --help  this usage text\n"
            "\t-V or --version     show a version message\n"
            "\t-c or --copyright   include a copyright notice\n"
            "\t-d or --destdir     destination directory, followed by the path\n"
            "\t-v or --verbose     Turn on verbose output\n",
            argv[0]);
        fprintf(stdfile,
            "\t      --small       Generate smaller .cnv files. They will be\n"
            "\t                    significantly smaller but may not be compatible with\n"
            "\t                    older versions of ICU and will require heap memory\n"
            "\t                    allocation when loaded.\n"
            "\t      --ignore-siso-check         Use SI/SO other than 0xf/0xe.\n");
        return argc<0 ? U_ILLEGAL_ARGUMENT_ERROR : U_ZERO_ERROR;
    }

    if(options[OPT_VERSION].doesOccur) {
        printf("makeconv version %hu.%hu, ICU tool to read .ucm codepage mapping files and write .cnv files\n",
               dataInfo.formatVersion[0], dataInfo.formatVersion[1]);
        printf("%s\n", U_COPYRIGHT_STRING);
        exit(0);
    }

    /* get the options values */
    haveCopyright = options[OPT_COPYRIGHT].doesOccur;
    destdir = options[OPT_DESTDIR].value;
    VERBOSE = options[OPT_VERBOSE].doesOccur;
    SMALL = options[OPT_SMALL].doesOccur;

    if (options[OPT_IGNORE_SISO_CHECK].doesOccur) {
        IGNORE_SISO_CHECK = TRUE;
    }

    if (destdir != NULL && *destdir != 0) {
        uprv_strcpy(outFileName, destdir);
        destdirlen = uprv_strlen(destdir);
        outBasename = outFileName + destdirlen;
        if (*(outBasename - 1) != U_FILE_SEP_CHAR) {
            *outBasename++ = U_FILE_SEP_CHAR;
            ++destdirlen;
        }
    } else {
        destdirlen = 0;
        outBasename = outFileName;
    }

#if DEBUG
    {
      int i;
      printf("makeconv: processing %d files...\n", argc - 1);
      for(i=1; i<argc; ++i) {
        printf("%s ", argv[i]);
      }
      printf("\n");
      fflush(stdout);
    }
#endif

    err = U_ZERO_ERROR;
    printFilename = (UBool) (argc > 2 || VERBOSE);
    for (++argv; --argc; ++argv)
    {
        arg = getLongPathname(*argv);

        /* Check for potential buffer overflow */
        if(strlen(arg) > UCNV_MAX_FULL_FILE_NAME_LENGTH)
        {
            fprintf(stderr, "%s\n", u_errorName(U_BUFFER_OVERFLOW_ERROR));
            return U_BUFFER_OVERFLOW_ERROR;
        }

        /*produces the right destination path for display*/
        if (destdirlen != 0)
        {
            const char *basename;

            /* find the last file sepator */
            basename = findBasename(arg);
            uprv_strcpy(outBasename, basename);
        }
        else
        {
            uprv_strcpy(outFileName, arg);
        }

        /*removes the extension if any is found*/
        dot = uprv_strrchr(outBasename, '.');
        if (dot)
        {
            *dot = '\0';
        }

        /* the basename without extension is the converter name */
        uprv_strcpy(cnvName, outBasename);

        /*Adds the target extension*/
        uprv_strcat(outBasename, CONVERTER_FILE_EXTENSION);

#if DEBUG
        printf("makeconv: processing %s  ...\n", arg);
        fflush(stdout);
#endif
        localError = U_ZERO_ERROR;
        initConvData(&data);
        createConverter(&data, arg, &localError);

        if (U_FAILURE(localError))
        {
            /* if an error is found, print out an error msg and keep going */
            fprintf(stderr, "Error creating converter for \"%s\" file for \"%s\" (%s)\n", outFileName, arg,
                u_errorName(localError));
            if(U_SUCCESS(err)) {
                err = localError;
            }
        }
        else
        {
            /* Insure the static data name matches the  file name */
            /* Changed to ignore directory and only compare base name
             LDH 1/2/08*/
            char *p;
            p = strrchr(cnvName, U_FILE_SEP_CHAR); /* Find last file separator */

            if(p == NULL)            /* OK, try alternate */
            {
                p = strrchr(cnvName, U_FILE_ALT_SEP_CHAR);
                if(p == NULL)
                {
                    p=cnvName; /* If no separators, no problem */
                }
            }
            else
            {
                p++;   /* If found separtor, don't include it in compare */
            }
            if(uprv_stricmp(p,data.staticData.name))
            {
                fprintf(stderr, "Warning: %s%s claims to be '%s'\n",
                    cnvName,  CONVERTER_FILE_EXTENSION,
                    data.staticData.name);
            }

            uprv_strcpy((char*)data.staticData.name, cnvName);

            if(!uprv_isInvariantString((char*)data.staticData.name, -1)) {
                fprintf(stderr,
                    "Error: A converter name must contain only invariant characters.\n"
                    "%s is not a valid converter name.\n",
                    data.staticData.name);
                if(U_SUCCESS(err)) {
                    err = U_INVALID_TABLE_FORMAT;
                }
            }

            uprv_strcpy(cnvNameWithPkg, cnvName);

            localError = U_ZERO_ERROR;
            writeConverterData(&data, cnvNameWithPkg, destdir, &localError);

            if(U_FAILURE(localError))
            {
                /* if an error is found, print out an error msg and keep going*/
                fprintf(stderr, "Error writing \"%s\" file for \"%s\" (%s)\n", outFileName, arg,
                    u_errorName(localError));
                if(U_SUCCESS(err)) {
                    err = localError;
                }
            }
            else if (printFilename)
            {
                puts(outBasename);
            }
        }
        fflush(stdout);
        fflush(stderr);

        cleanupConvData(&data);
    }

    return err;
}