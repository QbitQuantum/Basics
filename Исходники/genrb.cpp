int
main(int argc,
     char* argv[])
{
    UErrorCode  status    = U_ZERO_ERROR;
    const char *arg       = NULL;
    const char *outputDir = NULL; /* NULL = no output directory, use current */
    const char *inputDir  = NULL;
    const char *encoding  = "";
    int         i;
    UBool illegalArg = FALSE;

    U_MAIN_INIT_ARGS(argc, argv);

    options[JAVA_PACKAGE].value = "com.ibm.icu.impl.data";
    options[BUNDLE_NAME].value = "LocaleElements";
    argc = u_parseArgs(argc, argv, UPRV_LENGTHOF(options), options);

    /* error handling, printing usage message */
    if(argc<0) {
        fprintf(stderr, "%s: error in command line argument \"%s\"\n", argv[0], argv[-argc]);
        illegalArg = TRUE;
    } else if(argc<2) {
        illegalArg = TRUE;
    }
    if(options[WRITE_POOL_BUNDLE].doesOccur && options[USE_POOL_BUNDLE].doesOccur) {
        fprintf(stderr, "%s: cannot combine --writePoolBundle and --usePoolBundle\n", argv[0]);
        illegalArg = TRUE;
    }
    if(options[FORMAT_VERSION].doesOccur) {
        const char *s = options[FORMAT_VERSION].value;
        if(uprv_strlen(s) != 1 || (s[0] < '1' && '3' < s[0])) {
            fprintf(stderr, "%s: unsupported --formatVersion %s\n", argv[0], s);
            illegalArg = TRUE;
        } else if(s[0] == '1' &&
                  (options[WRITE_POOL_BUNDLE].doesOccur || options[USE_POOL_BUNDLE].doesOccur)
        ) {
            fprintf(stderr, "%s: cannot combine --formatVersion 1 with --writePoolBundle or --usePoolBundle\n", argv[0]);
            illegalArg = TRUE;
        } else {
            setFormatVersion(s[0] - '0');
        }
    }

    if((options[JAVA_PACKAGE].doesOccur || options[BUNDLE_NAME].doesOccur) &&
            !options[WRITE_JAVA].doesOccur) {
        fprintf(stderr,
                "%s error: command line argument --java-package or --bundle-name "
                "without --write-java\n",
                argv[0]);
        illegalArg = TRUE;
    }

    if(options[VERSION].doesOccur) {
        fprintf(stderr,
                "%s version %s (ICU version %s).\n"
                "%s\n",
                argv[0], GENRB_VERSION, U_ICU_VERSION, U_COPYRIGHT_STRING);
        if(!illegalArg) {
            return U_ZERO_ERROR;
        }
    }

    if(illegalArg || options[HELP1].doesOccur || options[HELP2].doesOccur) {
        /*
         * Broken into chunks because the C89 standard says the minimum
         * required supported string length is 509 bytes.
         */
        fprintf(stderr,
                "Usage: %s [OPTIONS] [FILES]\n"
                "\tReads the list of resource bundle source files and creates\n"
                "\tbinary version of resource bundles (.res files)\n",
                argv[0]);
        fprintf(stderr,
                "Options:\n"
                "\t-h or -? or --help       this usage text\n"
                "\t-q or --quiet            do not display warnings\n"
                "\t-v or --verbose          print extra information when processing files\n"
                "\t-V or --version          prints out version number and exits\n"
                "\t-c or --copyright        include copyright notice\n");
        fprintf(stderr,
                "\t-e or --encoding         encoding of source files\n"
                "\t-d of --destdir          destination directory, followed by the path, defaults to %s\n"
                "\t-s or --sourcedir        source directory for files followed by path, defaults to %s\n"
                "\t-i or --icudatadir       directory for locating any needed intermediate data files,\n"
                "\t                         followed by path, defaults to %s\n",
                u_getDataDirectory(), u_getDataDirectory(), u_getDataDirectory());
        fprintf(stderr,
                "\t-j or --write-java       write a Java ListResourceBundle for ICU4J, followed by optional encoding\n"
                "\t                         defaults to ASCII and \\uXXXX format.\n"
                "\t      --java-package     For --write-java: package name for writing the ListResourceBundle,\n"
                "\t                         defaults to com.ibm.icu.impl.data\n");
        fprintf(stderr,
                "\t-b or --bundle-name      For --write-java: root resource bundle name for writing the ListResourceBundle,\n"
                "\t                         defaults to LocaleElements\n"
                "\t-x or --write-xliff      write an XLIFF file for the resource bundle. Followed by\n"
                "\t                         an optional output file name.\n"
                "\t-k or --strict           use pedantic parsing of syntax\n"
                /*added by Jing*/
                "\t-l or --language         for XLIFF: language code compliant with BCP 47.\n");
        fprintf(stderr,
                "\t-C or --noBinaryCollation  do not generate binary collation image;\n"
                "\t                           makes .res file smaller but collator instantiation much slower;\n"
                "\t                           maintains ability to get tailoring rules\n"
                "\t-R or --omitCollationRules do not include collation (tailoring) rules;\n"
                "\t                           makes .res file smaller and maintains collator instantiation speed\n"
                "\t                           but tailoring rules will not be available (they are rarely used)\n");
        fprintf(stderr,
                "\t      --formatVersion      write a .res file compatible with the requested formatVersion (single digit);\n"
                "\t                           for example, --formatVersion 1\n");
        fprintf(stderr,
                "\t      --writePoolBundle    write a pool.res file with all of the keys of all input bundles\n"
                "\t      --usePoolBundle [path-to-pool.res]  point to keys from the pool.res keys pool bundle if they are available there;\n"
                "\t                           makes .res files smaller but dependent on the pool bundle\n"
                "\t                           (--writePoolBundle and --usePoolBundle cannot be combined)\n");

        return illegalArg ? U_ILLEGAL_ARGUMENT_ERROR : U_ZERO_ERROR;
    }

    if(options[VERBOSE].doesOccur) {
        setVerbose(TRUE);
    }

    if(options[QUIET].doesOccur) {
        setShowWarning(FALSE);
    }
    if(options[STRICT].doesOccur) {
        setStrict(TRUE);
    }
    if(options[COPYRIGHT].doesOccur){
        setIncludeCopyright(TRUE);
    }

    if(options[SOURCEDIR].doesOccur) {
        inputDir = options[SOURCEDIR].value;
    }

    if(options[DESTDIR].doesOccur) {
        outputDir = options[DESTDIR].value;
    }

    if(options[ENCODING].doesOccur) {
        encoding = options[ENCODING].value;
    }

    if(options[ICUDATADIR].doesOccur) {
        u_setDataDirectory(options[ICUDATADIR].value);
    }
    /* Initialize ICU */
    u_init(&status);
    if (U_FAILURE(status) && status != U_FILE_ACCESS_ERROR) {
        /* Note: u_init() will try to open ICU property data.
         *       failures here are expected when building ICU from scratch.
         *       ignore them.
        */
        fprintf(stderr, "%s: can not initialize ICU.  status = %s\n",
            argv[0], u_errorName(status));
        exit(1);
    }
    status = U_ZERO_ERROR;
    if(options[WRITE_JAVA].doesOccur) {
        write_java = TRUE;
        outputEnc = options[WRITE_JAVA].value;
    }

    if(options[WRITE_XLIFF].doesOccur) {
        write_xliff = TRUE;
        if(options[WRITE_XLIFF].value != NULL){
            xliffOutputFileName = options[WRITE_XLIFF].value;
        }
    }

    initParser();

    /*added by Jing*/
    if(options[LANGUAGE].doesOccur) {
        language = options[LANGUAGE].value;
    }

    LocalPointer<SRBRoot> newPoolBundle;
    if(options[WRITE_POOL_BUNDLE].doesOccur) {
        newPoolBundle.adoptInsteadAndCheckErrorCode(new SRBRoot(NULL, TRUE, status), status);
        if(U_FAILURE(status)) {
            fprintf(stderr, "unable to create an empty bundle for the pool keys: %s\n", u_errorName(status));
            return status;
        } else {
            const char *poolResName = "pool.res";
            char *nameWithoutSuffix = static_cast<char *>(uprv_malloc(uprv_strlen(poolResName) + 1));
            if (nameWithoutSuffix == NULL) {
                fprintf(stderr, "out of memory error\n");
                return U_MEMORY_ALLOCATION_ERROR;
            }
            uprv_strcpy(nameWithoutSuffix, poolResName);
            *uprv_strrchr(nameWithoutSuffix, '.') = 0;
            newPoolBundle->fLocale = nameWithoutSuffix;
        }
    }

    if(options[USE_POOL_BUNDLE].doesOccur) {
        const char *poolResName = "pool.res";
        FileStream *poolFile;
        int32_t poolFileSize;
        int32_t indexLength;
        /*
         * TODO: Consolidate inputDir/filename handling from main() and processFile()
         * into a common function, and use it here as well.
         * Try to create toolutil functions for dealing with dir/filenames and
         * loading ICU data files without udata_open().
         * Share code with icupkg?
         * Also, make_res_filename() seems to be unused. Review and remove.
         */
        CharString poolFileName;
        if (options[USE_POOL_BUNDLE].value!=NULL) {
            poolFileName.append(options[USE_POOL_BUNDLE].value, status);
        } else if (inputDir) {
            poolFileName.append(inputDir, status);
        }
        poolFileName.appendPathPart(poolResName, status);
        if (U_FAILURE(status)) {
            return status;
        }
        poolFile = T_FileStream_open(poolFileName.data(), "rb");
        if (poolFile == NULL) {
            fprintf(stderr, "unable to open pool bundle file %s\n", poolFileName.data());
            return 1;
        }
        poolFileSize = T_FileStream_size(poolFile);
        if (poolFileSize < 32) {
            fprintf(stderr, "the pool bundle file %s is too small\n", poolFileName.data());
            return 1;
        }
        poolBundle.fBytes = new uint8_t[(poolFileSize + 15) & ~15];
        if (poolFileSize > 0 && poolBundle.fBytes == NULL) {
            fprintf(stderr, "unable to allocate memory for the pool bundle file %s\n", poolFileName.data());
            return U_MEMORY_ALLOCATION_ERROR;
        }

        UDataSwapper *ds;
        const DataHeader *header;
        int32_t bytesRead = T_FileStream_read(poolFile, poolBundle.fBytes, poolFileSize);
        if (bytesRead != poolFileSize) {
            fprintf(stderr, "unable to read the pool bundle file %s\n", poolFileName.data());
            return 1;
        }
        /*
         * Swap the pool bundle so that a single checked-in file can be used.
         * The swapper functions also test that the data looks like
         * a well-formed .res file.
         */
        ds = udata_openSwapperForInputData(poolBundle.fBytes, bytesRead,
                                           U_IS_BIG_ENDIAN, U_CHARSET_FAMILY, &status);
        if (U_FAILURE(status)) {
            fprintf(stderr, "udata_openSwapperForInputData(pool bundle %s) failed: %s\n",
                    poolFileName.data(), u_errorName(status));
            return status;
        }
        ures_swap(ds, poolBundle.fBytes, bytesRead, poolBundle.fBytes, &status);
        udata_closeSwapper(ds);
        if (U_FAILURE(status)) {
            fprintf(stderr, "ures_swap(pool bundle %s) failed: %s\n",
                    poolFileName.data(), u_errorName(status));
            return status;
        }
        header = (const DataHeader *)poolBundle.fBytes;
        if (header->info.formatVersion[0] < 2) {
            fprintf(stderr, "invalid format of pool bundle file %s\n", poolFileName.data());
            return U_INVALID_FORMAT_ERROR;
        }
        const int32_t *pRoot = (const int32_t *)(
                (const char *)header + header->dataHeader.headerSize);
        poolBundle.fIndexes = pRoot + 1;
        indexLength = poolBundle.fIndexes[URES_INDEX_LENGTH] & 0xff;
        if (indexLength <= URES_INDEX_POOL_CHECKSUM) {
            fprintf(stderr, "insufficient indexes[] in pool bundle file %s\n", poolFileName.data());
            return U_INVALID_FORMAT_ERROR;
        }
        int32_t keysBottom = 1 + indexLength;
        int32_t keysTop = poolBundle.fIndexes[URES_INDEX_KEYS_TOP];
        poolBundle.fKeys = (const char *)(pRoot + keysBottom);
        poolBundle.fKeysLength = (keysTop - keysBottom) * 4;
        poolBundle.fChecksum = poolBundle.fIndexes[URES_INDEX_POOL_CHECKSUM];

        for (i = 0; i < poolBundle.fKeysLength; ++i) {
            if (poolBundle.fKeys[i] == 0) {
                ++poolBundle.fKeysCount;
            }
        }

        // 16BitUnits[] begins with strings-v2.
        // The strings-v2 may optionally be terminated by what looks like
        // an explicit string length that exceeds the number of remaining 16-bit units.
        int32_t stringUnitsLength = (poolBundle.fIndexes[URES_INDEX_16BIT_TOP] - keysTop) * 2;
        if (stringUnitsLength >= 2 && getFormatVersion() >= 3) {
            poolBundle.fStrings = new PseudoListResource(NULL, status);
            if (poolBundle.fStrings == NULL) {
                fprintf(stderr, "unable to allocate memory for the pool bundle strings %s\n",
                        poolFileName.data());
                return U_MEMORY_ALLOCATION_ERROR;
            }
            // The PseudoListResource constructor call did not allocate further memory.
            assert(U_SUCCESS(status));
            const UChar *p = (const UChar *)(pRoot + keysTop);
            int32_t remaining = stringUnitsLength;
            do {
                int32_t first = *p;
                int8_t numCharsForLength;
                int32_t length;
                if (!U16_IS_TRAIL(first)) {
                    // NUL-terminated
                    numCharsForLength = 0;
                    for (length = 0;
                         length < remaining && p[length] != 0;
                         ++length) {}
                } else if (first < 0xdfef) {
                    numCharsForLength = 1;
                    length = first & 0x3ff;
                } else if (first < 0xdfff && remaining >= 2) {
                    numCharsForLength = 2;
                    length = ((first - 0xdfef) << 16) | p[1];
                } else if (first == 0xdfff && remaining >= 3) {
                    numCharsForLength = 3;
                    length = ((int32_t)p[1] << 16) | p[2];
                } else {
                    break;  // overrun
                }
                // Check for overrun before changing remaining,
                // so that it is always accurate after the loop body.
                if ((numCharsForLength + length) >= remaining ||
                        p[numCharsForLength + length] != 0) {
                    break;  // overrun or explicitly terminated
                }
                int32_t poolStringIndex = stringUnitsLength - remaining;
                // Maximum pool string index when suffix-sharing the last character.
                int32_t maxStringIndex = poolStringIndex + numCharsForLength + length - 1;
                if (maxStringIndex >= RES_MAX_OFFSET) {
                    // pool string index overrun
                    break;
                }
                p += numCharsForLength;
                remaining -= numCharsForLength;
                if (length != 0) {
                    StringResource *sr =
                            new StringResource(poolStringIndex, numCharsForLength,
                                               p, length, status);
                    if (sr == NULL) {
                        fprintf(stderr, "unable to allocate memory for a pool bundle string %s\n",
                                poolFileName.data());
                        return U_MEMORY_ALLOCATION_ERROR;
                    }
                    poolBundle.fStrings->add(sr);
                    poolBundle.fStringIndexLimit = maxStringIndex + 1;
                    // The StringResource constructor did not allocate further memory.
                    assert(U_SUCCESS(status));
                }
                p += length + 1;
                remaining -= length + 1;
            } while (remaining > 0);
            if (poolBundle.fStrings->fCount == 0) {
                delete poolBundle.fStrings;
                poolBundle.fStrings = NULL;
            }
        }

        T_FileStream_close(poolFile);
        setUsePoolBundle(TRUE);
        if (isVerbose() && poolBundle.fStrings != NULL) {
            printf("number of shared strings: %d\n", (int)poolBundle.fStrings->fCount);
            int32_t length = poolBundle.fStringIndexLimit + 1;  // incl. last NUL
            printf("16-bit units for strings: %6d = %6d bytes\n",
                   (int)length, (int)length * 2);
        }
    }

    if(!options[FORMAT_VERSION].doesOccur && getFormatVersion() == 3 &&
            poolBundle.fStrings == NULL &&
            !options[WRITE_POOL_BUNDLE].doesOccur) {
        // If we just default to formatVersion 3
        // but there are no pool bundle strings to share
        // and we do not write a pool bundle,
        // then write formatVersion 2 which is just as good.
        setFormatVersion(2);
    }

    if(options[INCLUDE_UNIHAN_COLL].doesOccur) {
        puts("genrb option --includeUnihanColl ignored: \n"
                "CLDR 26/ICU 54 unihan data is small, except\n"
                "the ucadata-unihan.icu version of the collation root data\n"
                "is about 300kB larger than the ucadata-implicithan.icu version.");
    }

    if((argc-1)!=1) {
        printf("genrb number of files: %d\n", argc - 1);
    }
    /* generate the binary files */
    for(i = 1; i < argc; ++i) {
        status = U_ZERO_ERROR;
        arg    = getLongPathname(argv[i]);

        CharString theCurrentFileName;
        if (inputDir) {
            theCurrentFileName.append(inputDir, status);
        }
        theCurrentFileName.appendPathPart(arg, status);
        if (U_FAILURE(status)) {
            break;
        }

        gCurrentFileName = theCurrentFileName.data();
        if (isVerbose()) {
            printf("Processing file \"%s\"\n", theCurrentFileName.data());
        }
        processFile(arg, encoding, inputDir, outputDir, NULL,
                    newPoolBundle.getAlias(),
                    options[NO_BINARY_COLLATION].doesOccur, status);
    }

    poolBundle.close();

    if(U_SUCCESS(status) && options[WRITE_POOL_BUNDLE].doesOccur) {
        char outputFileName[256];
        newPoolBundle->write(outputDir, NULL, outputFileName, sizeof(outputFileName), status);
        if(U_FAILURE(status)) {
            fprintf(stderr, "unable to write the pool bundle: %s\n", u_errorName(status));
        }
    }

    u_cleanup();

    /* Dont return warnings as a failure */
    if (U_SUCCESS(status)) {
        return 0;
    }

    return status;
}