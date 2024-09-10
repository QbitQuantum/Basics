long	EdFail_CrashHandler (struct _EXCEPTION_POINTERS *pmExceptionInfo)
{
    static int		stInCrashHandler = 0;
    static FilePath	stMyPanicLogName, stMyAltPanicLogName;
    static HANDLE	stMyPanicFile;
    static DWORD	stMyNumBytesWritten;
    static int		stMyFileOpenStatus;
    static int		stMyFileOpenError;
        
    stCrashing = TRUE;
    
    if (stCrashBuffer == NULL)
    {
    	return EXCEPTION_EXECUTE_HANDLER;
    }

    if (stInCrashHandler > 1)
    {
    	return EXCEPTION_EXECUTE_HANDLER;
    }
    
    stInCrashHandler++;
    
    if (stInCrashHandler == 2)
    {
    	MyAddToBuffer ("\r\nCrashed in Crash Handler!\r\n");
    }
    else
    {
    	// Get file name
    	strcpy (stMyPanicLogName, EdProp_GetStartupDirectory ());

    	MyLoadString (IDS_PANIC_LOG_FILE, 
    	    &stMyPanicLogName [strlen (stMyPanicLogName)], 
            sizeof (stMyPanicLogName), PANIC_LOG_FILE_REPL);
            
	// Try opening the file.            
    	stMyPanicFile = CreateFile (stMyPanicLogName, GENERIC_WRITE, 0, NULL,
    	    OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// If opening the file failed, then try current directory instead.    	    
    	if (stMyPanicFile != (HANDLE) INVALID_HANDLE_VALUE)
    	{
    	    // File opened successfully.  Now close it
	    stMyFileOpenStatus = OPEN_SUCCESS;
    	    CloseHandle (stMyPanicFile);
    	}
    	else
	{
    	    stMyFileOpenError = GetLastError ();
    	    
	    // If the opening failed, try using the current directory.
	    EdFile_GetCurrentDirectory (stMyAltPanicLogName);
	    
	    if (strcmp (stMyAltPanicLogName, 
	    		EdProp_GetStartupDirectory ()) == 0)
	    {
	    	stMyFileOpenStatus = OPEN_FAIL_CURRENT_IS_STARTUP;
	    }
	    else
	    {
    	    	MyLoadString (IDS_PANIC_LOG_FILE, 
    	    	    &stMyAltPanicLogName [strlen (stMyAltPanicLogName)], 
            	    sizeof (stMyAltPanicLogName), PANIC_LOG_FILE_REPL);
            
	    	// Try opening the file.            
    	    	stMyPanicFile = CreateFile (stMyAltPanicLogName, GENERIC_WRITE, 
    	    			  	    0, NULL, OPEN_ALWAYS, 
    	    			  	    FILE_ATTRIBUTE_NORMAL, NULL);
    	    	if (stMyPanicFile != (HANDLE) INVALID_HANDLE_VALUE)
    	    	{
    	    	    // File opened successfully.  Now close it
	    	    stMyFileOpenStatus = OPEN_SUCCESS;
    	    	    CloseHandle (stMyPanicFile);
    	    	    strcpy (stMyPanicLogName, stMyAltPanicLogName);
    	    	}
    	    	else
	    	{
    	    	    stMyFileOpenError = GetLastError ();
	    	    stMyFileOpenStatus = OPEN_FAIL_BOTH_FAILED;
	    	}    	    
            }
	}

    	//
    	// Display the crash dialog box
    	//
    	stCrashBufferPtr = stCrashBuffer;
    	stCrashBufferLeft = CRASH_BUFFER_SIZE - 10;
        
    	// Get the window title (e.g. "Turing Internal Error")
    	MyLoadString (IDS_FATALWINDOWTITLE, stWindowTitle, 
    		      sizeof (stWindowTitle), WINDOW_TITLE_REPL);
    
    	// Get the preamble (e.g. "An unexpected error... Please record...")
    	MyLoadString (IDS_CRASHPREAMBLE1, stCrashBufferPtr, stCrashBufferLeft,
    		      CRASH_PREAMBLE_REPL1);
    	stCrashBufferLeft -= strlen (stCrashBufferPtr);
    	stCrashBufferPtr += strlen (stCrashBufferPtr);
    	MyAddToBuffer (stMyPanicLogName);
    	MyLoadString (IDS_CRASHPREAMBLE2, stCrashBufferPtr, stCrashBufferLeft,
    		      CRASH_PREAMBLE_REPL2);
    	stCrashBufferLeft -= strlen (stCrashBufferPtr);
    	stCrashBufferPtr += strlen (stCrashBufferPtr);

    	// Add the reason for the crash
    	MyAddToBuffer ("Cause of Crash: ");
    	EdCrash_GetExceptionName (stCrashBufferPtr, 
    			pmExceptionInfo -> ExceptionRecord -> ExceptionCode);
    	stCrashBufferLeft -= strlen (stCrashBufferPtr);
    	stCrashBufferPtr += strlen (stCrashBufferPtr);
    	MyAddToBuffer ("\r\n\r\n");
	
    	// Add the register dump
    	EdCrash_RegisterDump (stCrashBufferPtr, pmExceptionInfo -> ContextRecord);
    	stCrashBufferLeft -= strlen (stCrashBufferPtr);
    	stCrashBufferPtr += strlen (stCrashBufferPtr);
    	MyAddToBuffer ("\r\n");

    	// Add the saving files message    
    	MyLoadString (IDS_FAILSAVEFILE, stCrashBufferPtr, stCrashBufferLeft,
        	      FAIL_SAVE_FILE_REPL);
    	stCrashBufferLeft -= strlen (stCrashBufferPtr);
    	stCrashBufferPtr += strlen (stCrashBufferPtr);
    
    	// Display the error message    		
    	MessageBox (NULL, stCrashBuffer, stWindowTitle, 
            MB_OK | MB_ICONERROR | MB_TASKMODAL);

    	//
    	// Write to panic.log
    	//
    	stCrashBufferPtr = stCrashBuffer;
    	stCrashBufferLeft = CRASH_BUFFER_SIZE - 10;
   
    	// Title
    	MyAddToBuffer ("*** ENVIRONMENT CRASH ***\r\n\r\n");
    	
    	// Get environment information
    	MyGetEnvironmentInfo ();

    	// Add the reason for the crash
    	MyAddToBuffer ("\r\n\r\n");
    	MyAddToBuffer ("Cause of Crash: ");
        EdCrash_GetExceptionName (stCrashBufferPtr, 
    			pmExceptionInfo -> ExceptionRecord -> ExceptionCode);
    	stCrashBufferLeft -= strlen (stCrashBufferPtr);
    	stCrashBufferPtr += strlen (stCrashBufferPtr);

	// Add previous operations
	MyAddPreviousCommandsToBuffer ();
	    
    	// Add the register dump
    	EdCrash_RegisterDump (stCrashBufferPtr, pmExceptionInfo -> ContextRecord);
    	stCrashBufferLeft -= strlen (stCrashBufferPtr);
    	stCrashBufferPtr += strlen (stCrashBufferPtr);
    	MyAddToBuffer ("\r\n\r\n");

    	// Add the stack dump    
    	EdCrash_StackDump (stCrashBufferPtr, stCrashBufferLeft, 
    		           pmExceptionInfo -> ContextRecord);
    	stCrashBufferLeft -= strlen (stCrashBufferPtr);
    	stCrashBufferPtr += strlen (stCrashBufferPtr);

	MyAddToBuffer (LINE_OF_DASHES);
    	MyAddToBuffer ("\r\n");
    }

    if (stMyFileOpenStatus != OPEN_SUCCESS)
    {
    	if (stMyFileOpenStatus == OPEN_FAIL_CURRENT_IS_STARTUP)
    	{
    	    EdGUI_Message ("Panic log failure", 
    	        "Unable to open \"%s\" for writing.\nError = %d", 
    	        stMyPanicLogName, stMyFileOpenError);
    	}
    	else
    	{
	    EdGUI_Message ("Panic log failure", 
	    	"Unable to open \"%s\" or \"%s\" for writing.\nError = %d", 
	    	stMyPanicLogName, stMyAltPanicLogName, stMyFileOpenError);
	}	    	
    	return EXCEPTION_EXECUTE_HANDLER;
    }

    stMyPanicFile = CreateFile (stMyPanicLogName, GENERIC_WRITE, 0, NULL,
    	OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (stMyPanicFile == (HANDLE) INVALID_HANDLE_VALUE)
    {
    	EdGUI_Message ("Panic log failure", 
    	    "Unable to open \"%s\" for writing.\nError = %d", 
    	    stMyPanicLogName, GetLastError ());
    	return EXCEPTION_EXECUTE_HANDLER;
    }
    
    // Move to the end of the file
    SetFilePointer (stMyPanicFile, 0, NULL, FILE_END);

    if (!WriteFile (stMyPanicFile, stCrashBuffer, strlen (stCrashBuffer),
    		    &stMyNumBytesWritten, NULL))
    {
    	EdGUI_Message ("Panic log failure",
    	    "Unable to write to \"%s\"\nError = %d", 
    	    stMyPanicLogName, GetLastError ());
    	return EXCEPTION_EXECUTE_HANDLER;
    }
    if (stMyNumBytesWritten != strlen (stCrashBuffer))
    {
    	EdGUI_Message ("Panic log failure",
    	    "Unable to write to \"%s\"\n%d bytes written instead of %d bytes",
    	    stMyPanicLogName, stMyNumBytesWritten, strlen (stCrashBuffer));
    	return EXCEPTION_EXECUTE_HANDLER;
    }
    if (!FlushFileBuffers (stMyPanicFile))
    {
    	EdGUI_Message ("Panic log failure",
    	    "Unable to flush buffers of \"%s\"\nError = %d", 
    	    stMyPanicLogName, GetLastError ());
    	return EXCEPTION_EXECUTE_HANDLER;
    }

    if (!CloseHandle (stMyPanicFile))
    {
    	EdGUI_Message ("Panic log failure",
    	    "Unable to close \"%s\"\nError = %d", 
    	    stMyPanicLogName, GetLastError ());
    	return EXCEPTION_EXECUTE_HANDLER;
    }

    return EXCEPTION_EXECUTE_HANDLER;
} // EdFail_CrashHandler