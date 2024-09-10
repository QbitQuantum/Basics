WORD
MNetServiceInstall(
    LPTSTR pszServer,
    LPTSTR pszService,
    LPTSTR pszCmdArgs,
    LPBYTE * ppbBuffer)
{
#define DEFAULT_NUMBER_OF_ARGUMENTS 25

    DWORD MaxNumberofArguments = DEFAULT_NUMBER_OF_ARGUMENTS;
    DWORD argc = 0;
    LPTSTR * argv = NULL;
    BOOL fDone = FALSE;
    WORD ReturnCode;

    //
    // First see if there are any parms in the buffer, if so,
    // allocate a buffer for the array of pointers, we will grow this
    // later if there are more than will fit
    //

    if (!pszCmdArgs || *pszCmdArgs == NULLC)
    {
        fDone = TRUE;
    }
    else
    {
        argv = malloc(DEFAULT_NUMBER_OF_ARGUMENTS * sizeof(LPTSTR));
        if ( argv == NULL )
        {
            return(ERROR_NOT_ENOUGH_MEMORY);
        }
    }

    //
    // The buffer is a series of unicodez strings, terminated by and additional
    // NULL.  This peels them off one at a time, putting a pointer to the
    // string in argv[argc] until it hits the final NULL.
    //

    while (fDone == FALSE)
    {
        //
        // Save the pointer to the string
        //

        argv[argc++] = pszCmdArgs;

        //
        // Make sure we don't have too many arguments to fit into our array.
        // Grow the array if we do.
        //

        if (argc >= MaxNumberofArguments)
        {
            MaxNumberofArguments *= 2;
            if((argv = realloc(argv, MaxNumberofArguments * sizeof(LPTSTR)))
                     == NULL)
            {
                free(argv);
                return(ERROR_NOT_ENOUGH_MEMORY);
            }
        }

        //
        // Find the start of the next string
        //

        while (*pszCmdArgs++ != NULLC);

        //
        // If the next character is another null, we're thru
        //

        if (*pszCmdArgs == NULLC)
            fDone = TRUE;
    }

    ReturnCode = LOWORD(NetServiceInstall(pszServer, pszService, argc, argv,
                            ppbBuffer));

    // Free up the memory we allocated

    free(argv);

    // Now return

    return(ReturnCode);
}