//
//  MAIN program
//
int __cdecl main(int argc, char *argv[]) {
    short    rexxrc = 0;                 /* return code from rexx             */
    int   i;                             /* loop counter                      */
    int  rc;                             /* actually running program RC       */
    const char *program_name;            /* name to run                       */
    char  arg_buffer[8192];              /* starting argument buffer          */
    char *cp;                            /* option character pointer          */
    CONSTRXSTRING arguments;             /* rexxstart argument                */
    size_t argcount;
    RXSTRING rxretbuf;                   // program return buffer
    BOOL from_string = FALSE;            /* running from command line string? */
    BOOL real_argument = TRUE;           /* running from command line string? */
    RXSTRING instore[2];

    RexxInstance        *pgmInst;
    RexxThreadContext   *pgmThrdInst;
    RexxArrayObject      rxargs, rxcargs;
    RexxDirectoryObject  dir;
    RexxObjectPtr        result;

    rc = 0;                              /* set default return                */

    /*
     * Convert the input array into a single string for the Object REXX
     * argument string. Initialize the RXSTRING variable to point to this
     * string. Keep the string null terminated so we can print it for debug.
     * First argument is name of the REXX program
     * Next argument(s) are parameters to be passed
    */

    arg_buffer[0] = '\0';                /* default to no argument string     */
    program_name = NULL;                 /* no program to run yet             */

    for (i = 1; i < argc; i++)           /* loop through the arguments        */
    {
        /* is this an option switch?         */
        if ((*(cp=*(argv+i)) == '-' || *cp == '/')) {
            switch (*++cp) {
                case 'e':
                case 'E':                /* execute from string               */
                    if (from_string == FALSE) {  /* only treat 1st -e differently */
                        from_string = TRUE;
                        if ( argc == i+1 ) {
                            break;
                        }
                        program_name = "INSTORE";
                        instore[0].strptr = argv[i+1];
                        instore[0].strlength = strlen(instore[0].strptr);
                        instore[1].strptr = NULL;
                        instore[1].strlength = 0;
                        real_argument = FALSE;
                    }
                    break;
                case 'v':
                case 'V': {                                /* version display */
                    char *ptr = RexxGetVersionInformation();
                    if (ptr)
                    {
                        fprintf(stdout, ptr);
                        fprintf(stdout, "\n");
                        RexxFreeMemory(ptr);
                    }
                    return 0;
                }
                default:                       /* ignore other switches       */
                    break;
            }
        }
        else                             /* convert into an argument string   */
        {
            if (program_name == NULL) {       /* no name yet?                  */
                program_name = argv[i];        /* program is first non-option  */
                break;     /* end parsing after program_name has been resolved */
            }
            else if ( real_argument )  {  /* part of the argument string       */
                if (arg_buffer[0] != '\0')  {   /* not the first one?          */
                    strcat(arg_buffer, " ");     /* add an blank               */
                }
                strcat(arg_buffer, argv[i]);  /* add this to the argument string */
            }
            real_argument = TRUE;
        }
    }

    if (program_name == NULL) {
        /* give a simple error message       */
#undef printf
        printf("\n");
        fprintf(stderr,"Syntax is \"rexx filename [arguments]\"\n");
        fprintf(stderr,"or        \"rexx -e program_string [arguments]\"\n");
        fprintf(stderr,"or        \"rexx -v\".\n");
        return -1;
    }
    else {                              /* real program execution              */
        getArguments(NULL, GetCommandLine(), &argcount, &arguments);
        rxretbuf.strlength = 0L;                 /* initialize return to empty */

#ifdef REXXC_DEBUG
        printf("program_name = %s\n", program_name);
        printf("argv 0 = %s\n", argv[0]);
        printf("argv 1 = %s\n", argv[1]);
        printf("argv 2 = %s\n", argv[2]);
        printf("argument.strptr = %s\n", argument.strptr);
        printf("argument.strlenth = %lu\n", argument.strlength);
#endif


        if (from_string) {
            /* Here we call the interpreter.  We don't really need to use      */
            /* all the casts in this call; they just help illustrate           */
            /* the data types used.                                            */
            rc=REXXSTART(argcount,                    /* number of arguments   */
                         &arguments,                   /* array of arguments   */
                         program_name,                /* name of REXX file     */
                         instore,               /* rexx code from command line */
                         "CMD",                       /* Command env. name     */
                         RXCOMMAND,                   /* Code for how invoked  */
                         NULL,
                         &rexxrc,                     /* Rexx program output   */
                         &rxretbuf );                 /* Rexx program output   */
            /* rexx procedure executed*/
            if ((rc==0) && rxretbuf.strptr) {
                RexxFreeMemory(rxretbuf.strptr);    /* Release storage only if */
            }
            freeArguments(NULL, &arguments);
        }
        else {
            RexxCreateInterpreter(&pgmInst, &pgmThrdInst, NULL);
            // configure the traditional single argument string

            if ( arguments.strptr != NULL )
            {
                rxargs = pgmThrdInst->NewArray(1);
                pgmThrdInst->ArrayPut(rxargs, pgmThrdInst->String(arguments.strptr), 1);
            }
            else
            {
                rxargs = pgmThrdInst->NewArray(0);
            }

            // set up the C args into the .local environment
            dir = (RexxDirectoryObject)pgmThrdInst->GetLocalEnvironment();
            if ( argc > 2 )
            {
                rxcargs = pgmThrdInst->NewArray(argc - 2);
            }
            else
            {
                rxcargs = pgmThrdInst->NewArray(0);
            }
            for (i = 2; i < argc; i++)
            {
                pgmThrdInst->ArrayPut(rxcargs,
                                      pgmThrdInst->NewStringFromAsciiz(argv[i]),
                                      i - 1);
            }
            pgmThrdInst->DirectoryPut(dir, rxcargs, "SYSCARGS");
            // call the interpreter
            result = pgmThrdInst->CallProgram(program_name, rxargs);
            // display any error message if there is a condition.
            // if there was an error, then that will be our return code.
            // Although the return is a wholenumber_t we know there is no error
            // code too big to fit in an int.
            rc = (int)pgmThrdInst->DisplayCondition();
            if (rc != 0)
            {
                pgmInst->Terminate();
                return -rc;   // well, the negation of the error number is the return code
            }
            // now handle any potential return value
            if (result != NULL) {
                pgmThrdInst->ObjectToInt32(result, &rc);
            }

            pgmInst->Terminate();

            return rc;
        }
    }
    return rc ? rc : rexxrc;                    // rexx program return cd
}