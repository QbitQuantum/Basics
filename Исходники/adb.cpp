int launch_server(int server_port)
{
#if defined(_WIN32)
    /* we need to start the server in the background                    */
    /* we create a PIPE that will be used to wait for the server's "OK" */
    /* message since the pipe handles must be inheritable, we use a     */
    /* security attribute                                               */
    HANDLE                nul_read, nul_write;
    HANDLE                pipe_read, pipe_write;
    HANDLE                stdout_handle, stderr_handle;
    SECURITY_ATTRIBUTES   sa;
    STARTUPINFOW          startup;
    PROCESS_INFORMATION   pinfo;
    WCHAR                 program_path[ MAX_PATH ];
    int                   ret;

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    /* Redirect stdin and stderr to Windows /dev/null. If we instead pass our
     * stdin/stderr handles and they are console handles, when the adb server
     * starts up, the C Runtime will see console handles for a process that
     * isn't connected to a console and it will configure stderr to be closed.
     * At that point, freopen() could be used to reopen stderr, but it would
     * take more massaging to fixup the file descriptor number that freopen()
     * uses. It's simplest to avoid all of this complexity by just redirecting
     * stdin/stderr to `nul' and then the C Runtime acts as expected.
     */
    nul_read = CreateFileW(L"nul", GENERIC_READ,
                           FILE_SHARE_READ | FILE_SHARE_WRITE, &sa,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (nul_read == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "CreateFileW(nul, GENERIC_READ) failed: %s\n",
                SystemErrorCodeToString(GetLastError()).c_str());
        return -1;
    }

    nul_write = CreateFileW(L"nul", GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, &sa,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (nul_write == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "CreateFileW(nul, GENERIC_WRITE) failed: %s\n",
                SystemErrorCodeToString(GetLastError()).c_str());
        CloseHandle(nul_read);
        return -1;
    }

    /* create pipe, and ensure its read handle isn't inheritable */
    ret = CreatePipe( &pipe_read, &pipe_write, &sa, 0 );
    if (!ret) {
        fprintf(stderr, "CreatePipe() failed: %s\n",
                SystemErrorCodeToString(GetLastError()).c_str());
        CloseHandle(nul_read);
        CloseHandle(nul_write);
        return -1;
    }

    SetHandleInformation( pipe_read, HANDLE_FLAG_INHERIT, 0 );

    /* Some programs want to launch an adb command and collect its output by
     * calling CreateProcess with inheritable stdout/stderr handles, then
     * using read() to get its output. When this happens, the stdout/stderr
     * handles passed to the adb client process will also be inheritable.
     * When starting the adb server here, care must be taken to reset them
     * to non-inheritable.
     * Otherwise, something bad happens: even if the adb command completes,
     * the calling process is stuck while read()-ing from the stdout/stderr
     * descriptors, because they're connected to corresponding handles in the
     * adb server process (even if the latter never uses/writes to them).
     */
    stdout_handle = GetStdHandle( STD_OUTPUT_HANDLE );
    stderr_handle = GetStdHandle( STD_ERROR_HANDLE );
    if (stdout_handle != INVALID_HANDLE_VALUE) {
        SetHandleInformation( stdout_handle, HANDLE_FLAG_INHERIT, 0 );
    }
    if (stderr_handle != INVALID_HANDLE_VALUE) {
        SetHandleInformation( stderr_handle, HANDLE_FLAG_INHERIT, 0 );
    }

    ZeroMemory( &startup, sizeof(startup) );
    startup.cb = sizeof(startup);
    startup.hStdInput  = nul_read;
    startup.hStdOutput = nul_write;
    startup.hStdError  = nul_write;
    startup.dwFlags    = STARTF_USESTDHANDLES;

    ZeroMemory( &pinfo, sizeof(pinfo) );

    /* get path of current program */
    DWORD module_result = GetModuleFileNameW(NULL, program_path,
                                             arraysize(program_path));
    if ((module_result == arraysize(program_path)) || (module_result == 0)) {
        // String truncation or some other error.
        fprintf(stderr, "GetModuleFileNameW() failed: %s\n",
                SystemErrorCodeToString(GetLastError()).c_str());
        return -1;
    }

    // Verify that the pipe_write handle value can be passed on the command line
    // as %d and that the rest of adb code can pass it around in an int.
    const int pipe_write_as_int = cast_handle_to_int(pipe_write);
    if (cast_int_to_handle(pipe_write_as_int) != pipe_write) {
        // If this fires, either handle values are larger than 32-bits or else
        // there is a bug in our casting.
        // https://msdn.microsoft.com/en-us/library/windows/desktop/aa384203%28v=vs.85%29.aspx
        fprintf(stderr, "CreatePipe handle value too large: 0x%p\n",
                pipe_write);
        return -1;
    }

    WCHAR args[64];
    snwprintf(args, arraysize(args),
              L"adb -P %d fork-server server --reply-fd %d", server_port,
              pipe_write_as_int);
    ret = CreateProcessW(
            program_path,                              /* program path  */
            args,
                                    /* the fork-server argument will set the
                                       debug = 2 in the child           */
            NULL,                   /* process handle is not inheritable */
            NULL,                    /* thread handle is not inheritable */
            TRUE,                          /* yes, inherit some handles */
            DETACHED_PROCESS, /* the new process doesn't have a console */
            NULL,                     /* use parent's environment block */
            NULL,                    /* use parent's starting directory */
            &startup,                 /* startup info, i.e. std handles */
            &pinfo );

    CloseHandle( nul_read );
    CloseHandle( nul_write );
    CloseHandle( pipe_write );

    if (!ret) {
        fprintf(stderr, "CreateProcess failed: %s\n",
                SystemErrorCodeToString(GetLastError()).c_str());
        CloseHandle( pipe_read );
        return -1;
    }

    CloseHandle( pinfo.hProcess );
    CloseHandle( pinfo.hThread );

    /* wait for the "OK\n" message */
    {
        char  temp[3];
        DWORD  count;

        ret = ReadFile( pipe_read, temp, 3, &count, NULL );
        CloseHandle( pipe_read );
        if ( !ret ) {
            fprintf(stderr, "could not read ok from ADB Server, error: %s\n",
                    SystemErrorCodeToString(GetLastError()).c_str());
            return -1;
        }
        if (count != 3 || temp[0] != 'O' || temp[1] != 'K' || temp[2] != '\n') {
            fprintf(stderr, "ADB server didn't ACK\n" );
            return -1;
        }
    }
#else /* !defined(_WIN32) */
    char    path[PATH_MAX];
    int     fd[2];

    // set up a pipe so the child can tell us when it is ready.
    // fd[0] will be parent's end, and the child will write on fd[1]
    if (pipe(fd)) {
        fprintf(stderr, "pipe failed in launch_server, errno: %d\n", errno);
        return -1;
    }
    get_my_path(path, PATH_MAX);
    pid_t pid = fork();
    if(pid < 0) return -1;

    if (pid == 0) {
        // child side of the fork

        adb_close(fd[0]);

        char str_port[30];
        snprintf(str_port, sizeof(str_port), "%d", server_port);
        char reply_fd[30];
        snprintf(reply_fd, sizeof(reply_fd), "%d", fd[1]);
        // child process
        int result = execl(path, "adb", "-P", str_port, "fork-server", "server", "--reply-fd", reply_fd, NULL);
        // this should not return
        fprintf(stderr, "OOPS! execl returned %d, errno: %d\n", result, errno);
    } else  {
        // parent side of the fork

        char  temp[3];

        temp[0] = 'A'; temp[1] = 'B'; temp[2] = 'C';
        // wait for the "OK\n" message
        adb_close(fd[1]);
        int ret = adb_read(fd[0], temp, 3);
        int saved_errno = errno;
        adb_close(fd[0]);
        if (ret < 0) {
            fprintf(stderr, "could not read ok from ADB Server, errno = %d\n", saved_errno);
            return -1;
        }
        if (ret != 3 || temp[0] != 'O' || temp[1] != 'K' || temp[2] != '\n') {
            fprintf(stderr, "ADB server didn't ACK\n" );
            return -1;
        }

        setsid();
    }
#endif /* !defined(_WIN32) */
    return 0;
}