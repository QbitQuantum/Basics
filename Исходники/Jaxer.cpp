static int JaxerStartup(int &argc, char **argv)
{
    // tell manager I am up and establish the communication channel for later use

    // return 0 on success, none-0 if fails.
    // program should terminate if this function fails.

    // TODO: we should get this from the cmdline and get rid of the env var

    char *pipename = getenv("JAXER_PIPENAME");
    if (pipename == NULL) {
        gJaxerLog.Log(eFATAL, "Must be launched by Jaxer Server Manager.\n");
        fprintf(stderr, "Must be launched by Jaxer Server Manager.\n");
        return 1;
    }

#ifdef _WIN32
    // Manager is waiting for us to connect back to it.  Don't keep it waiting.
    g_pipe = CreateFile(pipename,
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_FLAG_OVERLAPPED,
                        NULL);
    if (g_pipe == INVALID_HANDLE_VALUE) {
        gJaxerLog.Log(eFATAL, "Invalid handle value when creating the pipe");
        return 1;
    }

    // Put pipe into message mode.
    DWORD mode = PIPE_READMODE_MESSAGE;
    if (!SetNamedPipeHandleState(g_pipe, &mode, NULL, NULL)) {
        gJaxerLog.Log(eFATAL, "Unable to put pipe into message mode.");
        return 1;
    }
#else
    // Manager created a Unix-domain socket pair and passed one of the sockets
    // as standard input.
    g_pipe = 0;

    // Let Manager know we're alive.
    char byte = 1;
    int rc;
    do {
        rc = send(g_pipe, &byte, 1, 0);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        gJaxerLog.Log(eFATAL, "Error in sending 'alive status' to Jaxer Manager");
        return 1;
    } else if (rc == 0) {
        gJaxerLog.Log(eFATAL, "Manager stop talking to us immediately");
        return 1;
    }
#endif
    return 0;
}