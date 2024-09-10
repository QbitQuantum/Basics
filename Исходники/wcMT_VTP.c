int main (int argc, char * argv[])
{
	DWORD nchar = 0, nword = 0, nline = 0;
    PTP_WORK *pWorkObjects;
    WORK_OBJECT_ARG ** pWorkObjArgsArray, *pObjectArg;
	TP_CALLBACK_ENVIRON cbe;  // Callback environment
	int nThread, iThrd;
	
    if (!WindowsVersionOK (6, 0)) 
        ReportError ("This program requires Windows NT 6.0 or greater", 1, TRUE);

	if (argc < 2) {
		printf ("Usage: wcMT_vtp filename ... filename\n");
		return 1;
	}

	/* Create a worker thread for each file on the command line */
	nThread = (DWORD)argc - 1;
    pWorkObjects = malloc (nThread * sizeof(PTP_WORK));
	if (pWorkObjects != NULL)
		pWorkObjArgsArray = malloc (nThread * sizeof(WORK_OBJECT_ARG *));
	if (pWorkObjects == NULL || pWorkObjArgsArray == NULL)
        ReportError ("Cannot allocate working memory for worke item or argument array.", 2, TRUE);

	InitializeThreadpoolEnvironment (&cbe);

	/* Create a work object argument for each file on the command line.
	   First put the file names in the thread arguments.	*/
	for (iThrd = 0; iThrd < nThread; iThrd++) {
		pObjectArg = (pWorkObjArgsArray[iThrd] = _aligned_malloc (sizeof(WORK_OBJECT_ARG), CACHE_LINE_SIZE));
		if (NULL == pObjectArg)
			ReportError ("Cannot allocate memory for a thread argument structure.", 3, TRUE);
		pObjectArg->filename = argv[iThrd+1];
		pObjectArg->kword = pObjectArg->kchar = pObjectArg->kline = 0;
		pWorkObjects[iThrd] = CreateThreadpoolWork (wcfunc, pObjectArg, &cbe);
        if (pWorkObjects[iThrd] == NULL) 
            ReportError ("Cannot create consumer thread", 4, TRUE);
		SubmitThreadpoolWork (pWorkObjects[iThrd]);
	}
	
	/* Worker objects are all submitted. Wait for them 	*/
	/* to complete and accumulate the results			*/
	for (iThrd = 0; iThrd < nThread; iThrd++) {
		/* Wait for the thread pool work item to complete */
		WaitForThreadpoolWorkCallbacks (pWorkObjects[iThrd], FALSE);
		CloseThreadpoolWork(pWorkObjects[iThrd]);
	}
    free (pWorkObjects);
	
	/* Accumulate the results							*/
	for (iThrd = 0; iThrd < argc - 1; iThrd++) {
		pObjectArg = pWorkObjArgsArray[iThrd]; 
		nchar += pObjectArg->kchar;
		nword += pObjectArg->kword;
		nline += pObjectArg->kline;
		printf ("%10d %9d %9d %s\n", pObjectArg->kline,
			pObjectArg->kword, pObjectArg->kchar,
			pObjectArg->filename);
	}
	free (pWorkObjArgsArray);
	printf ("%10d %9d %9d \n", nline, nword, nchar);
	return 0;
}