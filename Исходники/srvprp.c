INT_PTR CALLBACK PhpServiceGeneralDlgProc(
    __in HWND hwndDlg,
    __in UINT uMsg,
    __in WPARAM wParam,
    __in LPARAM lParam
    )
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            LPPROPSHEETPAGE propSheetPage = (LPPROPSHEETPAGE)lParam;
            PSERVICE_PROPERTIES_CONTEXT context = (PSERVICE_PROPERTIES_CONTEXT)propSheetPage->lParam;
            PPH_SERVICE_ITEM serviceItem = context->ServiceItem;
            SC_HANDLE serviceHandle;

            // HACK
            PhCenterWindow(GetParent(hwndDlg), GetParent(GetParent(hwndDlg)));

            SetProp(hwndDlg, PhMakeContextAtom(), (HANDLE)context);

            PhAddComboBoxStrings(GetDlgItem(hwndDlg, IDC_TYPE), PhServiceTypeStrings,
                sizeof(PhServiceTypeStrings) / sizeof(WCHAR *));
            PhAddComboBoxStrings(GetDlgItem(hwndDlg, IDC_STARTTYPE), PhServiceStartTypeStrings,
                sizeof(PhServiceStartTypeStrings) / sizeof(WCHAR *));
            PhAddComboBoxStrings(GetDlgItem(hwndDlg, IDC_ERRORCONTROL), PhServiceErrorControlStrings,
                sizeof(PhServiceErrorControlStrings) / sizeof(WCHAR *));

            SetDlgItemText(hwndDlg, IDC_DESCRIPTION, serviceItem->DisplayName->Buffer);
            ComboBox_SelectString(GetDlgItem(hwndDlg, IDC_TYPE), -1,
                PhGetServiceTypeString(serviceItem->Type));
            ComboBox_SelectString(GetDlgItem(hwndDlg, IDC_STARTTYPE), -1,
                PhGetServiceStartTypeString(serviceItem->StartType));
            ComboBox_SelectString(GetDlgItem(hwndDlg, IDC_ERRORCONTROL), -1,
                PhGetServiceErrorControlString(serviceItem->ErrorControl));

            serviceHandle = PhOpenService(serviceItem->Name->Buffer, SERVICE_QUERY_CONFIG);

            if (serviceHandle)
            {
                LPQUERY_SERVICE_CONFIG config;
                PPH_STRING description;
                BOOLEAN delayedStart;

                if (config = PhGetServiceConfig(serviceHandle))
                {
                    SetDlgItemText(hwndDlg, IDC_GROUP, config->lpLoadOrderGroup);
                    SetDlgItemText(hwndDlg, IDC_BINARYPATH, config->lpBinaryPathName);
                    SetDlgItemText(hwndDlg, IDC_USERACCOUNT, config->lpServiceStartName);

                    PhFree(config);
                }

                if (description = PhGetServiceDescription(serviceHandle))
                {
                    SetDlgItemText(hwndDlg, IDC_DESCRIPTION, description->Buffer);
                    PhDereferenceObject(description);
                }

                if (PhGetServiceDelayedAutoStart(serviceHandle, &delayedStart))
                {
                    context->OldDelayedStart = delayedStart;

                    if (delayedStart)
                        Button_SetCheck(GetDlgItem(hwndDlg, IDC_DELAYEDSTART), BST_CHECKED);
                }

                CloseServiceHandle(serviceHandle);
            }

            SetDlgItemText(hwndDlg, IDC_PASSWORD, L"password");
            Button_SetCheck(GetDlgItem(hwndDlg, IDC_PASSWORDCHECK), BST_UNCHECKED);

            SetDlgItemText(hwndDlg, IDC_SERVICEDLL, L"N/A");

            {
                HANDLE keyHandle;
                PPH_STRING keyName;

                keyName = PhConcatStrings(
                    3,
                    L"System\\CurrentControlSet\\Services\\",
                    serviceItem->Name->Buffer,
                    L"\\Parameters"
                    );

                if (NT_SUCCESS(PhOpenKey(
                    &keyHandle,
                    KEY_READ,
                    PH_KEY_LOCAL_MACHINE,
                    &keyName->sr,
                    0
                    )))
                {
                    PPH_STRING serviceDllString;

                    if (serviceDllString = PhQueryRegistryString(keyHandle, L"ServiceDll"))
                    {
                        PPH_STRING expandedString;

                        if (expandedString = PhExpandEnvironmentStrings(&serviceDllString->sr))
                        {
                            SetDlgItemText(hwndDlg, IDC_SERVICEDLL, expandedString->Buffer);
                            PhDereferenceObject(expandedString);
                        }

                        PhDereferenceObject(serviceDllString);
                    }

                    NtClose(keyHandle);
                }

                PhDereferenceObject(keyName);
            }

            PhpRefreshControls(hwndDlg);

            context->Ready = TRUE;
        }
        break;
    case WM_DESTROY:
        {
            RemoveProp(hwndDlg, PhMakeContextAtom());
        }
        break;
    case WM_COMMAND:
        {
            PSERVICE_PROPERTIES_CONTEXT context =
                (PSERVICE_PROPERTIES_CONTEXT)GetProp(hwndDlg, PhMakeContextAtom());

            switch (LOWORD(wParam))
            {
            case IDCANCEL:
                {
                    // Workaround for property sheet + multiline edit: http://support.microsoft.com/kb/130765

                    SendMessage(GetParent(hwndDlg), uMsg, wParam, lParam);
                }
                break;
            case IDC_PASSWORD:
                {
                    if (HIWORD(wParam) == EN_CHANGE)
                    {
                        Button_SetCheck(GetDlgItem(hwndDlg, IDC_PASSWORDCHECK), BST_CHECKED);
                    }
                }
                break;
            case IDC_DELAYEDSTART:
                {
                    context->Dirty = TRUE;
                }
                break;
            case IDC_BROWSE:
                {
                    static PH_FILETYPE_FILTER filters[] =
                    {
                        { L"Executable files (*.exe;*.sys)", L"*.exe;*.sys" },
                        { L"All files (*.*)", L"*.*" }
                    };
                    PVOID fileDialog;
                    PPH_STRING fileName;

                    fileDialog = PhCreateOpenFileDialog();
                    PhSetFileDialogFilter(fileDialog, filters, sizeof(filters) / sizeof(PH_FILETYPE_FILTER));

                    fileName = PhGetFileName(PHA_GET_DLGITEM_TEXT(hwndDlg, IDC_BINARYPATH));
                    PhSetFileDialogFileName(fileDialog, fileName->Buffer);
                    PhDereferenceObject(fileName);

                    if (PhShowFileDialog(hwndDlg, fileDialog))
                    {
                        fileName = PhGetFileDialogFileName(fileDialog);
                        SetDlgItemText(hwndDlg, IDC_BINARYPATH, fileName->Buffer);
                        PhDereferenceObject(fileName);
                    }

                    PhFreeFileDialog(fileDialog);
                }
                break;
            }

            switch (HIWORD(wParam))
            {
            case EN_CHANGE:
            case CBN_SELCHANGE:
                {
                    PhpRefreshControls(hwndDlg);

                    if (context->Ready)
                        context->Dirty = TRUE;
                }
                break;
            }
        }
        break;
    case WM_NOTIFY:
        {
            LPNMHDR header = (LPNMHDR)lParam;

            switch (header->code)
            {
            case PSN_QUERYINITIALFOCUS:
                {
                    SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, (LONG_PTR)GetDlgItem(hwndDlg, IDC_TYPE));
                }
                return TRUE;
            case PSN_KILLACTIVE:
                {
                    SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, FALSE);
                }
                return TRUE;
            case PSN_APPLY:
                {
                    NTSTATUS status;
                    PSERVICE_PROPERTIES_CONTEXT context =
                        (PSERVICE_PROPERTIES_CONTEXT)GetProp(hwndDlg, PhMakeContextAtom());
                    PPH_SERVICE_ITEM serviceItem = context->ServiceItem;
                    SC_HANDLE serviceHandle;
                    PPH_STRING newServiceTypeString;
                    PPH_STRING newServiceStartTypeString;
                    PPH_STRING newServiceErrorControlString;
                    ULONG newServiceType;
                    ULONG newServiceStartType;
                    ULONG newServiceErrorControl;
                    PPH_STRING newServiceGroup;
                    PPH_STRING newServiceBinaryPath;
                    PPH_STRING newServiceUserAccount;
                    PPH_STRING newServicePassword;

                    SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, PSNRET_NOERROR);

                    if (!context->Dirty)
                    {
                        return TRUE;
                    }

                    newServiceTypeString = PHA_DEREFERENCE(PhGetWindowText(GetDlgItem(hwndDlg, IDC_TYPE)));
                    newServiceStartTypeString = PHA_DEREFERENCE(PhGetWindowText(GetDlgItem(hwndDlg, IDC_STARTTYPE)));
                    newServiceErrorControlString = PHA_DEREFERENCE(PhGetWindowText(GetDlgItem(hwndDlg, IDC_ERRORCONTROL)));
                    newServiceType = PhGetServiceTypeInteger(newServiceTypeString->Buffer);
                    newServiceStartType = PhGetServiceStartTypeInteger(newServiceStartTypeString->Buffer);
                    newServiceErrorControl = PhGetServiceErrorControlInteger(newServiceErrorControlString->Buffer);

                    newServiceGroup = PHA_DEREFERENCE(PhGetWindowText(GetDlgItem(hwndDlg, IDC_GROUP)));
                    newServiceBinaryPath = PHA_DEREFERENCE(PhGetWindowText(GetDlgItem(hwndDlg, IDC_BINARYPATH)));
                    newServiceUserAccount = PHA_DEREFERENCE(PhGetWindowText(GetDlgItem(hwndDlg, IDC_USERACCOUNT)));

                    if (Button_GetCheck(GetDlgItem(hwndDlg, IDC_PASSWORDCHECK)) == BST_CHECKED)
                    {
                        newServicePassword = PhGetWindowText(GetDlgItem(hwndDlg, IDC_PASSWORD));
                    }
                    else
                    {
                        newServicePassword = NULL;
                    }

                    if (newServiceType == SERVICE_KERNEL_DRIVER && newServiceUserAccount->Length == 0)
                    {
                        newServiceUserAccount = NULL;
                    }

                    serviceHandle = PhOpenService(serviceItem->Name->Buffer, SERVICE_CHANGE_CONFIG);

                    if (serviceHandle)
                    {
                        if (ChangeServiceConfig(
                            serviceHandle,
                            newServiceType,
                            newServiceStartType,
                            newServiceErrorControl,
                            newServiceBinaryPath->Buffer,
                            newServiceGroup->Buffer,
                            NULL,
                            NULL,
                            PhGetString(newServiceUserAccount),
                            PhGetString(newServicePassword),
                            NULL
                            ))
                        {
                            BOOLEAN newDelayedStart;

                            newDelayedStart = Button_GetCheck(GetDlgItem(hwndDlg, IDC_DELAYEDSTART)) == BST_CHECKED;

                            if (newDelayedStart != context->OldDelayedStart)
                            {
                                PhSetServiceDelayedAutoStart(serviceHandle, newDelayedStart);
                            }

                            PhMarkNeedsConfigUpdateServiceItem(serviceItem);

                            CloseServiceHandle(serviceHandle);
                        }
                        else
                        {
                            CloseServiceHandle(serviceHandle);
                            goto ErrorCase;
                        }
                    }
                    else
                    {
                        if (GetLastError() == ERROR_ACCESS_DENIED && !PhElevated)
                        {
                            // Elevate using phsvc.
                            if (PhUiConnectToPhSvc(hwndDlg, FALSE))
                            {
                                if (NT_SUCCESS(status = PhSvcCallChangeServiceConfig(
                                    serviceItem->Name->Buffer,
                                    newServiceType,
                                    newServiceStartType,
                                    newServiceErrorControl,
                                    newServiceBinaryPath->Buffer,
                                    newServiceGroup->Buffer,
                                    NULL,
                                    NULL,
                                    PhGetString(newServiceUserAccount),
                                    PhGetString(newServicePassword),
                                    NULL
                                    )))
                                {
                                    BOOLEAN newDelayedStart;

                                    newDelayedStart = Button_GetCheck(GetDlgItem(hwndDlg, IDC_DELAYEDSTART)) == BST_CHECKED;

                                    if (newDelayedStart != context->OldDelayedStart)
                                    {
                                        SERVICE_DELAYED_AUTO_START_INFO info;

                                        info.fDelayedAutostart = newDelayedStart;
                                        PhSvcCallChangeServiceConfig2(
                                            serviceItem->Name->Buffer,
                                            SERVICE_CONFIG_DELAYED_AUTO_START_INFO,
                                            &info
                                            );
                                    }

                                    PhMarkNeedsConfigUpdateServiceItem(serviceItem);
                                }

                                PhUiDisconnectFromPhSvc();

                                if (!NT_SUCCESS(status))
                                {
                                    SetLastError(PhNtStatusToDosError(status));
                                    goto ErrorCase;
                                }
                            }
                            else
                            {
                                // User cancelled elevation.
                                SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, PSNRET_INVALID);
                            }
                        }
                        else
                        {
                            goto ErrorCase;
                        }
                    }

                    goto Cleanup;
ErrorCase:
                    if (PhShowMessage(
                        hwndDlg,
                        MB_ICONERROR | MB_RETRYCANCEL,
                        L"Unable to change service configuration: %s",
                        ((PPH_STRING)PHA_DEREFERENCE(PhGetWin32Message(GetLastError())))->Buffer
                        ) == IDRETRY)
                    {
                        SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, PSNRET_INVALID);
                    }

Cleanup:
                    if (newServicePassword)
                    {
                        RtlSecureZeroMemory(newServicePassword->Buffer, newServicePassword->Length);
                        PhDereferenceObject(newServicePassword);
                    }
                }
                return TRUE;
            }
        }
        break;
    }

    return FALSE;
}