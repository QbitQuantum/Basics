static INT_PTR CALLBACK EspRestartServiceDlgProc(
    _In_ HWND hwndDlg,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    )
{
    PRESTART_SERVICE_CONTEXT context;

    if (uMsg == WM_INITDIALOG)
    {
        context = (PRESTART_SERVICE_CONTEXT)lParam;
        SetProp(hwndDlg, L"Context", (HANDLE)context);
    }
    else
    {
        context = (PRESTART_SERVICE_CONTEXT)GetProp(hwndDlg, L"Context");

        if (uMsg == WM_DESTROY)
            RemoveProp(hwndDlg, L"Context");
    }

    if (!context)
        return FALSE;

    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            PhCenterWindow(hwndDlg, GetParent(hwndDlg));

            // TODO: Use the progress information.
            PhSetWindowStyle(GetDlgItem(hwndDlg, IDC_PROGRESS), PBS_MARQUEE, PBS_MARQUEE);
            SendMessage(GetDlgItem(hwndDlg, IDC_PROGRESS), PBM_SETMARQUEE, TRUE, 75);

            SetDlgItemText(hwndDlg, IDC_MESSAGE, PhaFormatString(L"Attempting to stop %s...", context->ServiceItem->Name->Buffer)->Buffer);

            if (PhUiStopService(hwndDlg, context->ServiceItem))
            {
                SetTimer(hwndDlg, 1, 250, NULL);
            }
            else
            {
                EndDialog(hwndDlg, IDCANCEL);
            }
        }
        break;
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDCANCEL:
                {
                    EndDialog(hwndDlg, IDCANCEL);
                }
                break;
            }
        }
        break;
    case WM_TIMER:
        {
            if (wParam == 1 && !context->DisableTimer)
            {
                SERVICE_STATUS serviceStatus;

                if (QueryServiceStatus(context->ServiceHandle, &serviceStatus))
                {
                    if (!context->Starting && serviceStatus.dwCurrentState == SERVICE_STOPPED)
                    {
                        // The service is stopped, so start the service now.

                        SetDlgItemText(hwndDlg, IDC_MESSAGE,
                            PhaFormatString(L"Attempting to start %s...", context->ServiceItem->Name->Buffer)->Buffer);
                        context->DisableTimer = TRUE;

                        if (PhUiStartService(hwndDlg, context->ServiceItem))
                        {
                            context->DisableTimer = FALSE;
                            context->Starting = TRUE;
                        }
                        else
                        {
                            EndDialog(hwndDlg, IDCANCEL);
                        }
                    }
                    else if (context->Starting && serviceStatus.dwCurrentState == SERVICE_RUNNING)
                    {
                        EndDialog(hwndDlg, IDOK);
                    }
                }
            }
        }
        break;
    }

    return FALSE;
}