static VOID PhpRefreshProcessList(
    _In_ HWND hwndDlg,
    _In_ PCHOOSE_PROCESS_DIALOG_CONTEXT Context
    )
{
    NTSTATUS status;
    HWND lvHandle;
    PVOID processes;
    PSYSTEM_PROCESS_INFORMATION process;

    lvHandle = Context->ListViewHandle;

    ListView_DeleteAllItems(lvHandle);
    ImageList_RemoveAll(Context->ImageList);

    if (!NT_SUCCESS(status = PhEnumProcesses(&processes)))
    {
        PhShowStatus(hwndDlg, L"Unable to enumerate processes", status, 0);
        return;
    }

    ExtendedListView_SetRedraw(lvHandle, FALSE);

    process = PH_FIRST_PROCESS(processes);

    do
    {
        INT lvItemIndex;
        PPH_STRING name;
        HANDLE processHandle;
        PPH_STRING fileName = NULL;
        HICON icon = NULL;
        WCHAR processIdString[PH_INT32_STR_LEN_1];
        PPH_STRING userName = NULL;
        INT imageIndex;

        if (process->UniqueProcessId != SYSTEM_IDLE_PROCESS_ID)
            name = PhCreateStringFromUnicodeString(&process->ImageName);
        else
            name = PhCreateString(SYSTEM_IDLE_PROCESS_NAME);

        lvItemIndex = PhAddListViewItem(lvHandle, MAXINT, name->Buffer, process->UniqueProcessId);
        PhDereferenceObject(name);

        if (NT_SUCCESS(PhOpenProcess(&processHandle, ProcessQueryAccess, process->UniqueProcessId)))
        {
            HANDLE tokenHandle;
            PTOKEN_USER user;

            if (!WINDOWS_HAS_IMAGE_FILE_NAME_BY_PROCESS_ID && process->UniqueProcessId != SYSTEM_PROCESS_ID)
                PhGetProcessImageFileName(processHandle, &fileName);

            if (NT_SUCCESS(PhOpenProcessToken(&tokenHandle, TOKEN_QUERY, processHandle)))
            {
                if (NT_SUCCESS(PhGetTokenUser(tokenHandle, &user)))
                {
                    userName = PhGetSidFullName(user->User.Sid, TRUE, NULL);
                    PhFree(user);
                }

                NtClose(tokenHandle);
            }

            NtClose(processHandle);
        }

        if (process->UniqueProcessId == SYSTEM_IDLE_PROCESS_ID && !userName && PhLocalSystemName)
            PhSetReference(&userName, PhLocalSystemName);

        if (WINDOWS_HAS_IMAGE_FILE_NAME_BY_PROCESS_ID && process->UniqueProcessId != SYSTEM_PROCESS_ID)
            PhGetProcessImageFileNameByProcessId(process->UniqueProcessId, &fileName);

        if (process->UniqueProcessId == SYSTEM_PROCESS_ID)
            fileName = PhGetKernelFileName();

        if (fileName)
            PhMoveReference(&fileName, PhGetFileName(fileName));

        icon = PhGetFileShellIcon(PhGetString(fileName), L".exe", FALSE);

        // Icon
        if (icon)
        {
            imageIndex = ImageList_AddIcon(Context->ImageList, icon);
            PhSetListViewItemImageIndex(Context->ListViewHandle, lvItemIndex, imageIndex);
            DestroyIcon(icon);
        }

        // PID
        PhPrintUInt32(processIdString, HandleToUlong(process->UniqueProcessId));
        PhSetListViewSubItem(Context->ListViewHandle, lvItemIndex, 1, processIdString);

        // User Name
        PhSetListViewSubItem(Context->ListViewHandle, lvItemIndex, 2, PhGetString(userName));

        if (userName) PhDereferenceObject(userName);
        if (fileName) PhDereferenceObject(fileName);
    } while (process = PH_NEXT_PROCESS(process));

    PhFree(processes);

    ExtendedListView_SortItems(lvHandle);
    ExtendedListView_SetRedraw(lvHandle, TRUE);
}