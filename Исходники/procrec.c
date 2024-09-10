INT_PTR CALLBACK PhpProcessRecordDlgProc(
    __in HWND hwndDlg,
    __in UINT uMsg,
    __in WPARAM wParam,
    __in LPARAM lParam
    )
{
    PPROCESS_RECORD_CONTEXT context = NULL;

    if (uMsg == WM_INITDIALOG)
    {
        context = (PPROCESS_RECORD_CONTEXT)lParam;
        SetProp(hwndDlg, PhMakeContextAtom(), (HANDLE)context);
    }
    else
    {
        context = (PPROCESS_RECORD_CONTEXT)GetProp(hwndDlg, PhMakeContextAtom());

        if (uMsg == WM_DESTROY)
        {
            RemoveProp(hwndDlg, PhMakeContextAtom());
        }
    }

    if (!context)
        return FALSE;

    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            PH_IMAGE_VERSION_INFO versionInfo;
            BOOLEAN versionInfoInitialized;
            PPH_STRING processNameString;
            PPH_PROCESS_ITEM processItem;

            if (!PH_IS_FAKE_PROCESS_ID(context->Record->ProcessId))
            {
                processNameString = PhaFormatString(L"%s (%u)",
                    context->Record->ProcessName->Buffer, (ULONG)context->Record->ProcessId);
            }
            else
            {
                processNameString = context->Record->ProcessName;
            }

            PhCenterWindow(hwndDlg, GetParent(hwndDlg));
            SetWindowText(hwndDlg, processNameString->Buffer);

            SetDlgItemText(hwndDlg, IDC_PROCESSNAME, processNameString->Buffer);

            if (processItem = PhReferenceProcessItemForRecord(context->Record))
            {
                PPH_PROCESS_ITEM parentProcess;

                if (parentProcess = PhReferenceProcessItemForParent(
                    processItem->ParentProcessId,
                    processItem->ProcessId,
                    &processItem->CreateTime
                    ))
                {
                    CLIENT_ID clientId;

                    clientId.UniqueProcess = parentProcess->ProcessId;
                    clientId.UniqueThread = NULL;

                    SetDlgItemText(hwndDlg, IDC_PARENT,
                        ((PPH_STRING)PHA_DEREFERENCE(PhGetClientIdNameEx(&clientId, parentProcess->ProcessName)))->Buffer);

                    PhDereferenceObject(parentProcess);
                }
                else
                {
                    SetDlgItemText(hwndDlg, IDC_PARENT, PhaFormatString(L"Non-existent process (%u)",
                        (ULONG)context->Record->ParentProcessId)->Buffer);
                }

                PhDereferenceObject(processItem);
            }
            else
            {
                SetDlgItemText(hwndDlg, IDC_PARENT, PhaFormatString(L"Unknown process (%u)",
                    (ULONG)context->Record->ParentProcessId)->Buffer);

                EnableWindow(GetDlgItem(hwndDlg, IDC_PROPERTIES), FALSE);
            }

            memset(&versionInfo, 0, sizeof(PH_IMAGE_VERSION_INFO));
            versionInfoInitialized = FALSE;

            if (context->Record->FileName)
            {
                if (PhInitializeImageVersionInfo(&versionInfo, context->Record->FileName->Buffer))
                    versionInfoInitialized = TRUE;
            }

            context->FileIcon = PhGetFileShellIcon(PhGetString(context->Record->FileName), L".exe", TRUE);

            SendMessage(GetDlgItem(hwndDlg, IDC_OPENFILENAME), BM_SETIMAGE, IMAGE_BITMAP,
                (LPARAM)PH_LOAD_SHARED_IMAGE(MAKEINTRESOURCE(IDB_FOLDER), IMAGE_BITMAP));
            SendMessage(GetDlgItem(hwndDlg, IDC_FILEICON), STM_SETICON,
                (WPARAM)context->FileIcon, 0);

            SetDlgItemText(hwndDlg, IDC_NAME, PhpGetStringOrNa(versionInfo.FileDescription));
            SetDlgItemText(hwndDlg, IDC_COMPANYNAME, PhpGetStringOrNa(versionInfo.CompanyName));
            SetDlgItemText(hwndDlg, IDC_VERSION, PhpGetStringOrNa(versionInfo.FileVersion));
            SetDlgItemText(hwndDlg, IDC_FILENAME, PhpGetStringOrNa(context->Record->FileName));

            if (versionInfoInitialized)
                PhDeleteImageVersionInfo(&versionInfo);

            if (!context->Record->FileName)
                EnableWindow(GetDlgItem(hwndDlg, IDC_OPENFILENAME), FALSE);

            SetDlgItemText(hwndDlg, IDC_CMDLINE, PhpGetStringOrNa(context->Record->CommandLine));

            if (context->Record->CreateTime.QuadPart != 0)
                SetDlgItemText(hwndDlg, IDC_STARTED, PhapGetRelativeTimeString(&context->Record->CreateTime)->Buffer);
            else
                SetDlgItemText(hwndDlg, IDC_STARTED, L"N/A");

            if (context->Record->ExitTime.QuadPart != 0)
                SetDlgItemText(hwndDlg, IDC_TERMINATED, PhapGetRelativeTimeString(&context->Record->ExitTime)->Buffer);
            else
                SetDlgItemText(hwndDlg, IDC_TERMINATED, L"N/A");

            SetDlgItemInt(hwndDlg, IDC_SESSIONID, context->Record->SessionId, FALSE);
        }
        break;
    case WM_DESTROY:
        {
            if (context->FileIcon)
                DestroyIcon(context->FileIcon);
        }
        break;
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDCANCEL:
            case IDOK:
                {
                    EndDialog(hwndDlg, IDOK);
                }
                break;
            case IDC_OPENFILENAME:
                {
                    if (context->Record->FileName)
                        PhShellExploreFile(hwndDlg, context->Record->FileName->Buffer);
                }
                break;
            case IDC_PROPERTIES:
                {
                    PPH_PROCESS_ITEM processItem;

                    if (processItem = PhReferenceProcessItemForRecord(context->Record))
                    {
                        ProcessHacker_ShowProcessProperties(PhMainWndHandle, processItem);
                        PhDereferenceObject(processItem);
                    }
                    else
                    {
                        PhShowError(hwndDlg, L"The process has already terminated; only the process record is available.");
                    }
                }
                break;
            }
        }
        break;
    }

    return FALSE;
}