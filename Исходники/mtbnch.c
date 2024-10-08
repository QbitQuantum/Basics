int _CRTAPI1
main(
    int argc,
    char *argv[],
    char *envp[]
    )
{
    DWORD StartTicks, EndTicks;
    DWORD i;
    BOOL fShowUsage;
    char c, *p, *whocares;
    PDWORD CellVector;
    DWORD NumberOfDwords;
    DWORD DwordsPerThread;
    DWORD ThreadId;
    LPSTR Answer;

    fShowUsage = FALSE;
    fMemoryContention = FALSE;

    if (argc <= 1) {
        goto showUsage;
        }

    while (--argc) {
        p = *++argv;
        if (*p == '/' || *p == '-') {
            while (c = *++p)
            switch (toupper( c )) {
            case '?':
                fShowUsage = TRUE;
                goto showUsage;
                break;

            case 'M':
                if (!argc--) {
                    fShowUsage = TRUE;
                    goto showUsage;
                    }
                argv++;
                Mb = strtoul(*argv,&whocares,10);
                break;

            case 'C':
                fMemoryContention = TRUE;
                break;

            case 'T':
                if (!argc--) {
                    fShowUsage = TRUE;
                    goto showUsage;
                    }
                argv++;
                NumberOfThreads = strtoul(*argv,&whocares,10);
                if ( NumberOfThreads > MAX_THREADS ) {
                    fShowUsage = TRUE;
                    goto showUsage;
                    }
                break;

            default:
                fprintf( stderr, "MTBNCH: Invalid switch - /%c\n", c );
                goto showUsage;
                break;
                }
            }
        }

showUsage:
    if ( fShowUsage ) {
        fprintf(stderr,"usage: MTBNCH\n" );
        fprintf(stderr,"              [-?] display this message\n" );
        fprintf(stderr,"              [-t n] use n threads for benchmark (less than 32)\n" );
        fprintf(stderr,"              [-m n] use an n Mb spreadsheet size (default 4)\n" );
        fprintf(stderr,"              [-c] cause memory contention on each loop iteration\n" );
        ExitProcess(1);
        }

    //
    // Prepare the race events. These are manual reset events.
    //

    hStartOfRace = CreateEvent(NULL,TRUE,FALSE,NULL);
    hEndOfRace = CreateEvent(NULL,TRUE,FALSE,NULL);

    if ( !hStartOfRace || !hEndOfRace ) {
        fprintf(stderr,"MTBNCH: Race Event Creation Failed\n");
        ExitProcess(1);
        }

    //
    // Prepare the ready done events. These are auto clearing events
    //

    for(i=0; i<NumberOfThreads; i++ ) {
        ThreadReadyDoneEvents[i] = CreateEvent(NULL,FALSE,FALSE,NULL);
        if ( !ThreadReadyDoneEvents[i] ) {
            fprintf(stderr,"MTBNCH: Ready Done Event Creation Failed %d\n",GetLastError());
            ExitProcess(1);
            }
        }

    //
    // Allocate and initialize the CellVector
    //

    CellVector = (PDWORD)VirtualAlloc(NULL,Mb*ONE_MB,MEM_COMMIT,PAGE_READWRITE);
    if ( !CellVector ) {
        fprintf(stderr,"MTBNCH: Cell Vector Allocation Failed %d\n",GetLastError());
        ExitProcess(1);
        }

    NumberOfDwords = (Mb*ONE_MB) / sizeof(DWORD);
    DwordsPerThread = NumberOfDwords / NumberOfThreads;

    //
    // Initialize the Cell Vector
    //

    for(i=0, ExpectedRecalcValue; i<NumberOfDwords; i++ ){
        ExpectedRecalcValue += i;
        CellVector[i] = i;
        }

    //
    // Partition the work to the worker threads
    //

    for(i=0; i<NumberOfThreads; i++ ){
        ThreadWork[i].CellVector = &CellVector[i*DwordsPerThread];
        ThreadWork[i].NumberOfCells = DwordsPerThread;
        NumberOfDwords -= DwordsPerThread;

        //
        // If we have a remainder, give the remaining work to the last thread
        //

        if ( NumberOfDwords < DwordsPerThread ) {
            ThreadWork[i].NumberOfCells += NumberOfDwords;
            }
        }

    //
    // Create the worker threads
    //

    for(i=0; i<NumberOfThreads; i++ ) {
        ThreadHandles[i] = CreateThread(
                                NULL,
                                0,
                                WorkerThread,
                                (PVOID)i,
                                0,
                                &ThreadId
                                );
        if ( !ThreadHandles[i] ) {
            fprintf(stderr,"MTBNCH: Worker Thread Creation Failed %d\n",GetLastError());
            ExitProcess(1);
            }
        }

    //
    // All of the worker threads will signal thier ready done event
    // when they are idle and ready to proceed. Once all events have been
    // set, then setting the hStartOfRaceEvent will begin the recalc
    //

    i = WaitForMultipleObjects(
            NumberOfThreads,
            ThreadReadyDoneEvents,
            TRUE,
            INFINITE
            );

    if ( i == WAIT_FAILED ) {
        fprintf(stderr,"MTBNCH: Wait for threads to stabalize Failed %d\n",GetLastError());
        ExitProcess(1);
        }

    //
    // Everthing is set to begin the recalc operation
    //

    StartTicks = GetTickCount();
    if ( !SetEvent(hStartOfRace) ) {
        fprintf(stderr,"MTBNCH: SetEvent(hStartOfRace) Failed %d\n",GetLastError());
        ExitProcess(1);
        }

    //
    // Now just wait for the recalc to complete
    //

    i = WaitForMultipleObjects(
            NumberOfThreads,
            ThreadReadyDoneEvents,
            TRUE,
            INFINITE
            );

    if ( i == WAIT_FAILED ) {
        fprintf(stderr,"MTBNCH: Wait for threads to complete Failed %d\n",GetLastError());
        ExitProcess(1);
        }

    //
    // Now pick up the individual recalc values
    //

    for(i=0, ActualRecalcValue = 0; i<NumberOfThreads; i++ ){
        ActualRecalcValue += ThreadWork[i].RecalcResult;
        }

    EndTicks = GetTickCount();

    if ( fMemoryContention ) {
        if ( ContentionValue == (Mb*ONE_MB) / sizeof(DWORD) ) {
            if ( ActualRecalcValue == ExpectedRecalcValue ) {
                Answer = "Correct";
                }
            else {
                Answer = "Recalc Failure";
                }
            }
        else {
            Answer = "Contention Failure";
            }
        }
    else {
        if ( ActualRecalcValue == ExpectedRecalcValue ) {
            Answer = "Correct";
            }
        else {
            Answer = "Recalc Failure";
            }
        }

    fprintf(stdout,"MTBNCH: %d Thread Recalc complete in %dms, Answer = %s\n",
        NumberOfThreads,
        EndTicks-StartTicks,
        Answer
        );

    ExitProcess(2);
}