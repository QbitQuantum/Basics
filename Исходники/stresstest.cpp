/*
 * ======================================================================= *
 * In the startup of this program, we look at our executable name and      *
 * replace the ".EXE" with ".DLL" to find the ISAPI DLL we need to load.   *
 * This means that the executable need only be given the same "name" as    *
 * the DLL to load. There is no recompilation required.                    *
 * ======================================================================= *
*/
BOOL stress_main(const char *filename, 
				const char *arg, 
				const char *postdata,
				const char *matchdata) 
{

	EXTENSION_CONTROL_BLOCK ECB;
	DWORD rc;
	TIsapiContext context;

	// open output and input files
	context.tid = GetCurrentThreadId();
	CString fname;
	fname.Format("%08X.out", context.tid);

	context.out = CreateFile(fname, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL);
	if (context.out==INVALID_HANDLE_VALUE) {
		printf("failed to open output file %s\n", fname);
		return 0;
	}

	// not using post files
	context.in = INVALID_HANDLE_VALUE;

	//
	// Fill the ECB with the necessary information
	//
	if (!FillExtensionControlBlock(&ECB, &context) ) {
		fprintf(stderr,"Fill Ext Block Failed\n");
		return -1;
	}
	
	// check for command line argument, 
	// first arg = filename
	// this is added for testing php from command line

	context.env.RemoveAll();
	context.env["PATH_TRANSLATED"]= filename;
	context.env["SCRIPT_MAP"]= filename;
	context.env["CONTENT_TYPE"]= "";
	context.env["CONTENT_LENGTH"]= "";
	context.env["QUERY_STRING"]= arg;
	context.env["METHOD"]="GET";
	context.env["PATH_INFO"] = "";
	context.waitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	char buf[MAX_PATH];
	if (postdata && *postdata !=0) {
		ECB.cbAvailable = strlen(postdata);
		ECB.cbTotalBytes = ECB.cbAvailable;
		ECB.lpbData = (unsigned char *)postdata;
		context.env["METHOD"]="POST";

		_snprintf(buf, sizeof(buf)-1, "%d", ECB.cbTotalBytes);
		context.env["CONTENT_LENGTH"]=buf;

		context.env["CONTENT_TYPE"]="application/x-www-form-urlencoded";
	}
	ECB.lpszMethod = strdup(context.env["METHOD"]);
    ECB.lpszPathTranslated = strdup(filename);
	ECB.lpszQueryString = strdup(arg);
	ECB.lpszPathInfo = strdup(context.env["PATH_INFO"]);


	// Call the DLL
	//
	rc = IsapiHttpExtensionProc(&ECB);
	if (rc == HSE_STATUS_PENDING) {
		// We will exit in ServerSupportFunction
		WaitForSingleObject(context.waitEvent, INFINITE);
	}
	CloseHandle(context.waitEvent);
	//Sleep(75);
	free(ECB.lpszPathTranslated);
	free(ECB.lpszQueryString);
	free(ECB.lpszMethod);
	free(ECB.lpszPathInfo);

	BOOL ok = TRUE;

	if (context.out != INVALID_HANDLE_VALUE) CloseHandle(context.out);

	// compare the output with the EXPECT section
	if (matchdata && *matchdata != 0) {
		ok = CompareFiles(fname, matchdata);
	}

	DeleteFile(fname);

	return ok;
		
}