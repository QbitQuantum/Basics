int ParseInputFile()
{
    char pszKeyWord[MAX];              // input token
    char pszParam[MAX];                // parameter for keyword
    CODEPAGE CP;                       // codepage structure
    LANGUAGE Lang;                     // language structure
    LANG_EXCEPT LangExcept;            // language exception structure
    LOCALE_HEADER LocHdr;              // header locale structure
    LOCALE_STATIC LocStat;             // static length locale structure
    LOCALE_VARIABLE LocVar;            // variable length locale structure
    UNICODE Unic;                      // unicode structure
    CTYPES CTypes;                     // ctypes structure
    SORTKEY Sortkey;                   // sortkey structure - sorting
    SORT_TABLES SortTbls;              // sort tables structure - sorting
    IDEOGRAPH_EXCEPT IdeographExcept;  // ideograph exception structure - sorting


    while (fscanf(pInputFile, "%s", pszKeyWord) == 1)
    {
        if (_strcmpi(pszKeyWord, "CODEPAGE") == 0)
        {
            if (Verbose)
                printf("\n\nFound CODEPAGE keyword.\n");

            //
            //  Initialize CodePage structure.
            //
            memset(&CP, 0, sizeof(CODEPAGE));
            memset(pszParam, 0, MAX * sizeof(char));
            CP.pszName = pszParam;

            //
            //  Get CODEPAGE parameter string.
            //
            if (GetKeyParam(pszParam))
            {
                return (1);
            }

            //
            //  Get the valid keywords for CODEPAGE.
            //
            if (ParseCodePage(&CP, pszKeyWord))
            {
                return (1);
            }

            //
            //  Write the CODEPAGE tables to an output file.
            //
            if (WriteCodePage(&CP))
            {
                return (1);
            }
        }

        else if (_strcmpi(pszKeyWord, "LANGUAGE") == 0)
        {
            if (Verbose)
                printf("\n\nFound LANGUAGE keyword.\n");

            //
            //  Initialize Language structure.
            //
            memset(&Lang, 0, sizeof(LANGUAGE));

            //
            //  Get LANGUAGE parameter string.
            //
            if (GetKeyParam(pszParam))
            {
                return (1);
            }

            //
            //  Get the valid keywords for LANGUAGE.
            //
            if (ParseLanguage(&Lang, pszKeyWord))
            {
                return (1);
            }

            //
            //  Write the LANGUAGE tables to an output file.
            //
            if (WriteLanguage(&Lang))
            {
                return (1);
            }
        }

        else if (_strcmpi(pszKeyWord, "LANGUAGE_EXCEPTION") == 0)
        {
            if (Verbose)
                printf("\n\nFound LANGUAGE_EXCEPTION keyword.\n");

            //
            //  Initialize Language structure.
            //
            memset(&LangExcept, 0, sizeof(LANG_EXCEPT));

            //
            //  Get the valid keywords for LANGUAGE_EXCEPTION.
            //
            if (ParseLangException(&LangExcept, pszKeyWord))
            {
                return (1);
            }

            //
            //  Write the LANGUAGE_EXCEPTION tables to an output file.
            //
            if (WriteLangException(&LangExcept))
            {
                return (1);
            }
        }

        else if (_strcmpi(pszKeyWord, "LOCALE") == 0)
        {
            if (Verbose)
                printf("\n\nFound LOCALE keyword.\n");

            //
            //  Get the valid keywords for LOCALE.
            //  Write the LOCALE information to an output file.
            //
            if (ParseWriteLocale( &LocHdr,
                                  &LocStat,
                                  &LocVar,
                                  pszKeyWord ))
            {
                return (1);
            }
        }

        else if (_strcmpi(pszKeyWord, "UNICODE") == 0)
        {
            if (Verbose)
                printf("\n\nFound UNICODE keyword.\n");

            //
            //  Initialize Unicode structure.
            //
            memset(&Unic, 0, sizeof(UNICODE));

            //
            //  Get the valid keywords for UNICODE.
            //
            if (ParseUnicode(&Unic, pszKeyWord))
            {
                return (1);
            }

            //
            //  Write the UNICODE tables to an output file.
            //
            if (WriteUnicode(&Unic))
            {
                return (1);
            }
        }

        else if (_strcmpi(pszKeyWord, "CTYPES") == 0)
        {
            if (Verbose)
                printf("\n\nFound CTYPES keyword.\n");

            //
            //  Initialize CTypes structure.
            //
            memset(&CTypes, 0, sizeof(CTYPES));

            //
            //  Get the valid keywords for CTYPES.
            //
            if (ParseCTypes(&CTypes))
            {
                return (1);
            }

            //
            //  Write the CTYPES tables to different output files.
            //
            if (WriteCTypes(&CTypes))
            {
                return (1);
            }
        }

        else if (_strcmpi(pszKeyWord, "SORTKEY") == 0)
        {
            if (Verbose)
                printf("\n\nFound SORTKEY keyword.\n");

            //
            //  Initialize Sortkey structure.
            //
            memset(&Sortkey, 0, sizeof(SORTKEY));

            //
            //  Get the valid keywords for SORTKEY.
            //
            if (ParseSortkey(&Sortkey, pszKeyWord))
            {
                return (1);
            }

            //
            //  Write the SORTKEY tables to an output file.
            //
            if (WriteSortkey(&Sortkey))
            {
                return (1);
            }
        }

        else if (_strcmpi(pszKeyWord, "SORTTABLES") == 0)
        {
            if (Verbose)
                printf("\n\nFound SORTTABLES keyword.\n");

            //
            //  Initialize Sort Tables structure.
            //
            memset(&SortTbls, 0, sizeof(SORT_TABLES));

            //
            //  Get the valid keywords for SORTTABLES.
            //
            if (ParseSortTables(&SortTbls, pszKeyWord))
            {
                return (1);
            }

            //
            //  Write the Sort Tables to an output file.
            //
            if (WriteSortTables(&SortTbls))
            {
                return (1);
            }
        }

        else if (_strcmpi(pszKeyWord, "IDEOGRAPH_EXCEPTION") == 0)
        {
            if (Verbose)
                printf("\n\nFound IDEOGRAPH_EXCEPTION keyword.\n");

            //
            //  Initialize Ideograph Exception structure.
            //
            memset(&IdeographExcept, 0, sizeof(IDEOGRAPH_EXCEPT));

            //
            //  Get the valid keywords for IDEOGRAPH_EXCEPTION.
            //
            if (ParseIdeographExceptions(&IdeographExcept))
            {
                return (1);
            }

            //
            //  Write the Ideograph Exceptions to the given output file.
            //
            if (WriteIdeographExceptions(&IdeographExcept))
            {
                return (1);
            }
        }

        else
        {
            printf("Parse Error: Invalid Instruction '%s'.\n", pszKeyWord);
            return (1);
        }
    }

    //
    //  Return success.
    //
    return (0);
}