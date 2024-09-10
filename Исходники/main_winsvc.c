static void WINAPI service_ctrl_handler(DWORD control_code)
{
        switch (control_code) {
        case SERVICE_CONTROL_INTERROGATE:
                break;
        case SERVICE_CONTROL_SHUTDOWN:
        case SERVICE_CONTROL_STOP:
                svc_status.dwCurrentState = SERVICE_STOP_PENDING;
                svc_status.dwWaitHint = 2000;
                eloop_terminate();
                SetEvent(kill_svc);
                break;
        }

        if (!SetServiceStatus(svc_status_handle, &svc_status)) {
                printf("SetServiceStatus() failed: %d\n",
                       (int) GetLastError());
        }
}