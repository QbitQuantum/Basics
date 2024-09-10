    bool LaunchProcess(const string16& cmdline,
        const LaunchOptions& options,
        ProcessHandle* process_handle)
    {
        STARTUPINFO startup_info = {};
        startup_info.cb = sizeof(startup_info);
        if(options.empty_desktop_name)
        {
            startup_info.lpDesktop = L"";
        }
        startup_info.dwFlags = STARTF_USESHOWWINDOW;
        startup_info.wShowWindow = options.start_hidden ? SW_HIDE : SW_SHOW;
        PROCESS_INFORMATION process_info;

        DWORD flags = 0;

        if(options.job_handle)
        {
            flags |= CREATE_SUSPENDED;

            // If this code is run under a debugger, the launched process is
            // automatically associated with a job object created by the debugger.
            // The CREATE_BREAKAWAY_FROM_JOB flag is used to prevent this.
            flags |= CREATE_BREAKAWAY_FROM_JOB;
        }

        if(options.as_user)
        {
            flags |= CREATE_UNICODE_ENVIRONMENT;
            void* enviroment_block = NULL;

            if(!CreateEnvironmentBlock(&enviroment_block, options.as_user, FALSE))
            {
                return false;
            }

            BOOL launched = CreateProcessAsUser(options.as_user, NULL,
                const_cast<wchar_t*>(cmdline.c_str()),
                NULL, NULL, options.inherit_handles, flags,
                enviroment_block, NULL, &startup_info,
                &process_info);
            DestroyEnvironmentBlock(enviroment_block);
            if(!launched)
            {
                return false;
            }
        }
        else
        {
            if(!CreateProcess(NULL,
                const_cast<wchar_t*>(cmdline.c_str()), NULL, NULL,
                options.inherit_handles, flags, NULL, NULL,
                &startup_info, &process_info))
            {
                return false;
            }
        }

        if(options.job_handle)
        {
            if(0 == AssignProcessToJobObject(options.job_handle, process_info.hProcess))
            {
                LOG(ERROR) << "Could not AssignProcessToObject.";
                KillProcess(process_info.hProcess, kProcessKilledExitCode, true);
                return false;
            }

            ResumeThread(process_info.hThread);
        }

        // Handles must be closed or they will leak.
        CloseHandle(process_info.hThread);

        if(options.wait)
        {
            WaitForSingleObject(process_info.hProcess, INFINITE);
        }

        // If the caller wants the process handle, we won't close it.
        if(process_handle)
        {
            *process_handle = process_info.hProcess;
        }
        else
        {
            CloseHandle(process_info.hProcess);
        }
        return true;
    }