void
AcpiDbCreateExecutionThreads (
    NATIVE_CHAR             *NumThreadsArg,
    NATIVE_CHAR             *NumLoopsArg,
    NATIVE_CHAR             *MethodNameArg)
{
    ACPI_STATUS             Status;
    UINT32                  NumThreads;
    UINT32                  NumLoops;
    UINT32                  i;
    ACPI_HANDLE             ThreadGate;


    /* Get the arguments */

    NumThreads = STRTOUL (NumThreadsArg, NULL, 0);
    NumLoops = STRTOUL (NumLoopsArg, NULL, 0);

    if (!NumThreads || !NumLoops)
    {
        AcpiOsPrintf ("Bad argument: Threads %X, Loops %X\n", NumThreads, NumLoops);
        return;
    }


    /* Create the synchronization semaphore */

    Status = AcpiOsCreateSemaphore (1, 0, &ThreadGate);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not create semaphore, %s\n", AcpiFormatException (Status));
        return;
    }

    /* Setup the context to be passed to each thread */

    AcpiGbl_DbMethodInfo.Name = MethodNameArg;
    AcpiGbl_DbMethodInfo.Args = NULL;
    AcpiGbl_DbMethodInfo.Flags = 0;
    AcpiGbl_DbMethodInfo.NumLoops = NumLoops;
    AcpiGbl_DbMethodInfo.ThreadGate = ThreadGate;

    AcpiDbExecuteSetup (&AcpiGbl_DbMethodInfo);


    /* Create the threads */

    AcpiOsPrintf ("Creating %X threads to execute %X times each\n", NumThreads, NumLoops);

    for (i = 0; i < (NumThreads); i++)
    {
        AcpiOsQueueForExecution (OSD_PRIORITY_MED, AcpiDbMethodThread, &AcpiGbl_DbMethodInfo);
    }


    /* Wait for all threads to complete */

    i = NumThreads;
    while (i)   /* Brain damage for OSD implementations that only support wait of 1 unit */
    {
        Status = AcpiOsWaitSemaphore (ThreadGate, 1, WAIT_FOREVER);
        i--;
    }

    /* Cleanup and exit */

    AcpiOsDeleteSemaphore (ThreadGate);

    AcpiDbSetOutputDestination (DB_DUPLICATE_OUTPUT);
    AcpiOsPrintf ("All threads (%X) have completed\n", NumThreads);
    AcpiDbSetOutputDestination (DB_CONSOLE_OUTPUT);
}