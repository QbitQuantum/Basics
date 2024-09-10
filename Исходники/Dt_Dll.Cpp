BOOL WINAPI 
DllMain(
    HINSTANCE InstanceHandle, 
    DWORD     Reason, 
    LPVOID    Reserved)
/*++
  
  DllMain()
  
  Function Description:
  
      Please see Windows documentation for DllEntryPoint.
  
  Arguments:
  
      Please see windows documentation.
  
  Return Value:
  
      Please see windows documentation.
  
--*/
{
    
    Cstack_c   *ThreadCstack;   // points to Cstack objects in tls 
    PINITDATA   InitDataPtr;    // to pass to the window creation thread
    HKEY        hkeyAppData;
    char        szSubKeyStr[sizeof(szDtRegKey)+256],
               *ptr=NULL;
    int         ModuleLen=0;


    // OutputDebugString ("DllMain called.\n");
    switch(Reason) {

        // Determine the reason for the call and act accordingly.
        case DLL_PROCESS_ATTACH:

            if ((ModuleLen = GetModuleFileName (NULL, ModuleFileName, sizeof (ModuleFileName)))==0)
                return FALSE;


            // Allocate a TLS index.
            TlsIndex = TlsAlloc();
            if (TlsIndex==0xFFFFFFFF)
                return FALSE;

            DllInstHandle = InstanceHandle;
            try {
                InitializeCriticalSection(&CrSec);
	        }
            catch(...) {
                OutputStyle = NO_OUTPUT;
                return FALSE;
            }
            
            TextOutEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
            if (TextOutEvent==NULL)
                return FALSE;

            // Fill in the handler function table.
            DTHandlerInit(HdlFuncTable, MAX_DTCODE);

            // Build the log file name
            StringCchCopy( LogFileName, MAX_PATH+1, ModuleFileName );
            StringCchCat( LogFileName, MAX_PATH+1, ".log");

            // See if the reg key exists for this EXE
            ptr = &ModuleFileName[ModuleLen-1];
            while ( (ptr != ModuleFileName) &&  (*ptr != '\\') )
                ptr--;
            if (*ptr == '\\')
                ptr++;

            // Build the key

            StringCchPrintf(szSubKeyStr, sizeof(szDtRegKey)+255, "%s\\%s", szDtRegKey, ptr);

            OutputDebugString("Looking for key: ");
            OutputDebugString(szSubKeyStr);
            OutputDebugString("\r\n");

            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                        szSubKeyStr,
                        0,
                        KEY_QUERY_VALUE,
                        &hkeyAppData) == NO_ERROR)
            {
                OutputDebugString("Found the registry key\r\n");
                OutputStyle = FILE_ONLY;
  
                RegCloseKey(hkeyAppData);
            }
            else
            {
                OutputStyle = NO_OUTPUT;
            }

            if (OutputStyle == FILE_ONLY)
            {
                LogFileHandle = CreateFile(LogFileName, 
                        GENERIC_WRITE, 
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        NULL, 
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL, 
                        NULL);
                if (LogFileHandle == INVALID_HANDLE_VALUE) {
                    OutputDebugString("Unable to create log file!\r\n");
                    OutputStyle = NO_OUTPUT;
                }
            }

            // Get some information for later output to the debug window
            // or file -- get the time, PID, and TID of the calling
            // process and put into a INITDATA struct.  This memory will
            // be freed by the thread it is passed to.
            InitDataPtr = (PINITDATA) LocalAlloc(0, sizeof(INITDATA));
            GetLocalTime(&(InitDataPtr->LocalTime));
            InitDataPtr->TID = GetCurrentThreadId();
            InitDataPtr->PID = GetCurrentProcessId();

            // Normally the window thread does a DTTextOut of the time
            // and process info that we saved just above.  But in this
            // case,  there is no window thread so spit it out to the
            // file or debugger. 

            StringCchPrintf(Buffer, TEXT_LEN-1, "Log initiated: %d-%d-%d, %d:%d:%d\r\n", 
                    InitDataPtr->LocalTime.wMonth, 
                    InitDataPtr->LocalTime.wDay, 
                    InitDataPtr->LocalTime.wYear, 
                    InitDataPtr->LocalTime.wHour, 
                    InitDataPtr->LocalTime.wMinute, 
                    InitDataPtr->LocalTime.wSecond);
            DTTextOut(LogFileHandle, Buffer, OutputStyle);
            StringCchPrintf(Buffer, TEXT_LEN-1, "Process ID: 0x%X   Thread ID: 0x%X\r\n",
                    InitDataPtr->PID,
                    InitDataPtr->TID);
            DTTextOut(LogFileHandle, Buffer, OutputStyle);

            // Setting this event allows {Pre|Post}ApiNotify to
            // proceed.  This event isn't really needed in this case
            // (because there is only one thread, and we know the code
            // above has been executed before WSAPre|PostApiNotify).
            SetEvent(TextOutEvent);

            // flow through...

        case DLL_THREAD_ATTACH:

            // Store a pointer to a new Cstack_c in the slot for this
            // thread. 
            ThreadCstack = new Cstack_c();
            TlsSetValue(TlsIndex, (LPVOID)ThreadCstack);

            break;

        case DLL_PROCESS_DETACH:

            // Free up some resources.  This is like cleaning up your room
            // before the tornado strikes, but hey, it's good practice.
            TlsFree(TlsIndex);
            DeleteCriticalSection(&CrSec);

            CloseHandle(LogFileHandle);

            break;

        case DLL_THREAD_DETACH:

            // Get the pointer to this thread's Cstack, and delete the
            // object.
            ThreadCstack = (Cstack_c *)TlsGetValue(TlsIndex);
            delete ThreadCstack;

            break;

        default:

            break;
    } // switch (Reason)

    return TRUE;
} // DllMain()