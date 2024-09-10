/**
 * Initializes the IPC communication.
 *
 * @return  IPRT status code.
 * @param   pEnv                        The IPC service's environment.
 * @param   ppInstance                  The instance pointer which refer to this object.
 * @param   pfStartThread               Pointer to flag whether the IPC service can be started or not.
 */
int VBoxIPCInit(const VBOXSERVICEENV *pEnv, void **ppInstance, bool *pfStartThread)
{
    Log(("VBoxTray: VBoxIPCInit\n"));

    *pfStartThread = false;
    gCtx.pEnv = pEnv;

    int rc = VINF_SUCCESS;
    SECURITY_ATTRIBUTES sa;
    sa.lpSecurityDescriptor = (PSECURITY_DESCRIPTOR)RTMemAlloc(SECURITY_DESCRIPTOR_MIN_LENGTH);
    if (!sa.lpSecurityDescriptor)
        rc = VERR_NO_MEMORY;
    else
    {
        if (!InitializeSecurityDescriptor(sa.lpSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION))
            rc = RTErrConvertFromWin32(GetLastError());
        else
        {
            if (!SetSecurityDescriptorDacl(sa.lpSecurityDescriptor, TRUE, (PACL)0, FALSE))
                rc = RTErrConvertFromWin32(GetLastError());
            else
            {
                sa.nLength = sizeof(sa);
                sa.bInheritHandle = TRUE;
            }
        }

        if (RT_SUCCESS(rc))
        {
            gCtx.hPipe = CreateNamedPipe((LPSTR)VBOXTRAY_PIPE_IPC,
                                         PIPE_ACCESS_DUPLEX,
                                         PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                                         PIPE_UNLIMITED_INSTANCES,
                                         VBOXTRAY_PIPE_IPC_BUFSIZE, /* Output buffer size. */
                                         VBOXTRAY_PIPE_IPC_BUFSIZE, /* Input buffer size. */
                                         NMPWAIT_USE_DEFAULT_WAIT,
                                         &sa);
            if (gCtx.hPipe == INVALID_HANDLE_VALUE)
                rc = RTErrConvertFromWin32(GetLastError());
            else
            {
                *pfStartThread = true;
                *ppInstance = &gCtx;
            }
        }
        RTMemFree(sa.lpSecurityDescriptor);
    }
    return rc;
}