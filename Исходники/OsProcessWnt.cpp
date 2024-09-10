OsStatus OsProcessWnt::launch(UtlString &rAppName, UtlString parameters[],OsPath &startupDir,
                    OsProcessPriorityClass prioClass, UtlBoolean bExeclusive, UtlBoolean bIgnoreChildSignals)
{
    OsStatus retval = OS_FAILED;
        STARTUPINFO StartupInfo;
        PROCESS_INFORMATION ProcessInformation;
    UtlString cmdLine = startupDir + OsPath::separator;
        cmdLine += rAppName;
/*
    int saved_stderr = dup(2);
    int saved_stdout = dup(1);
    int saved_stdin  = dup(0);
*/
    //build one string out of the array passed in
    int parameterCount = 0;
    while (!parameters[parameterCount].isNull())
    {
        if(parameters[parameterCount].index(" ") != UTL_NOT_FOUND)
            parameters[parameterCount] = "\"" + parameters[parameterCount] + "\"";
        cmdLine.append(" ");
        cmdLine.append(parameters[parameterCount]);
        parameterCount++;
    }
        //clear out structure
        memset(&StartupInfo,'\0',sizeof(STARTUPINFO));

        StartupInfo.cb = sizeof(STARTUPINFO);
        StartupInfo.lpReserved = NULL;
        StartupInfo.wShowWindow = SW_MINIMIZE|SW_HIDE;
        StartupInfo.lpDesktop = NULL;
        StartupInfo.lpTitle = NULL;

    StartupInfo.dwFlags |= STARTF_USESTDHANDLES;

    //now it's time to redirect the output,input and error streams
    if (mStdErrorFilename.length())
        StartupInfo.hStdError  = mStdErrorHandle;
    else
        StartupInfo.hStdError =GetStdHandle(STD_ERROR_HANDLE);

    if (mStdInputFilename.length())
        StartupInfo.hStdInput  = mStdInputHandle;
    else
        StartupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

    if (mStdOutputFilename.length())
        StartupInfo.hStdOutput = mStdOutputHandle;
    else
        StartupInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    //now apply the env variables the user may have set
    ApplyEnv();


    //3...2...1...  LAUNCH!!!!
        int retcode = CreateProcess(
                                NULL,
                // name of executable module (null because we want to execute all commands)
                // even things such as dir
                                (char *)cmdLine.data(),       // command line string
                                NULL,
                                NULL,
                //this originally was TRUE but the web browser was never coming back.
                                FALSE,       // handle inheritance flag
//                CREATE_NEW_CONSOLE,
                                CREATE_NO_WINDOW | DETACHED_PROCESS,      // creation flags
                                NULL,       // new environment block
                                startupDir.data(), // startupdir
                                &StartupInfo,
                                &ProcessInformation
                                );

    if (retcode != 0)
    {
        //translate the incoming priority to Wnt values
        DWORD wntPrio = NORMAL_PRIORITY_CLASS;

        switch(prioClass)
        {
            case IdlePriorityClass:     wntPrio = IDLE_PRIORITY_CLASS;
                                        break;
            case NormalPriorityClass:   wntPrio = NORMAL_PRIORITY_CLASS;
                                        break;
            case HighPriorityClass:     wntPrio = HIGH_PRIORITY_CLASS;
                                        break;
            case RealtimePriorityClass: wntPrio = REALTIME_PRIORITY_CLASS;
                                        break;
            default:                    osPrintf("**** Invalid process priority class specified!\n");
                                        osPrintf("***  Defaulting to NormalPriorityClass *** \n");
                                        break;
        }

        if (!SetPriorityClass(ProcessInformation.hProcess, wntPrio))
        {
            osPrintf("*** Could not change the process priority on launch ***\n");
            osPrintf("*** Priority will be the parents priority ! ***\n");
        }

        if (bExeclusive)
        {
            //here is where we check if a process by the same name is already running
        }

        mPID = ProcessInformation.dwProcessId;
        mParentPID = getpid();
        mhProcess = ProcessInformation.hProcess;
        mhThread = ProcessInformation.hThread;
        retval = OS_SUCCESS;
    }
    else
    {

        LPVOID lpMsgBuf;
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            (LPTSTR) &lpMsgBuf,
            0,
            NULL
            );
        osPrintf("***** ERROR FROM LAUNCH: %s",(LPCTSTR)lpMsgBuf);
        // Free the buffer.
        LocalFree( lpMsgBuf );

    }
/*
        dup2(saved_stderr,2);
        dup2(saved_stdout,1);
        dup2(saved_stdin, 0);
*/
    return retval;
}