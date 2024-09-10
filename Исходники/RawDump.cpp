//-----------------------------------------------------------------------------
// Name: RawDumpDump
// Object: make a raw dump for specified process, address and length
// Parameters :
//     in  : 
//     out : 
//     return : 
//-----------------------------------------------------------------------------
void RawDumpDump()
{
    TCHAR psz[MAX_PATH];
    TCHAR* pc;
    DWORD ProcessId=0;
    PVOID StartAddress=0;;
    DWORD Size=0;
    HANDLE hWndControl;
    
    if (UserMode)
    {
        // retrieve process ID
        *psz=0;
        hWndControl=GetDlgItem(RawDumphDlg,IDC_COMBO_RAW_DUMP_SELECT_PROCESS);
        SendMessage((HWND) hWndControl,(UINT) WM_GETTEXT,MAX_PATH,(LPARAM)psz);
        pc=_tcsrchr(psz,'(');
        if (!pc)
            return;
        pc++;
        ProcessId=(DWORD)_ttol(pc);

        if(!RawCheckIfProcessIsAlive(ProcessId))
            return;
    }

    // retrieve start address
    *psz=0;
    hWndControl=GetDlgItem(RawDumphDlg,IDC_EDIT_RAW_DUMP_START_ADDRESS);
    SendMessage((HWND) hWndControl,(UINT) WM_GETTEXT,MAX_PATH,(LPARAM)psz);
    int iScanfRes;

    if(_tcsnicmp(psz,_T("0x"),2)==0)
        iScanfRes=_stscanf(psz,_T("0x%x"),&StartAddress);
    else
        iScanfRes=_stscanf(psz,_T("%u"),&StartAddress);
    if ((!iScanfRes)||(!StartAddress))
    {
        MessageBox(RawDumphDlg,_T("Bad Start Address"),_T("Error"),MB_OK|MB_ICONERROR|MB_TOPMOST);
        return;
    }

    // retrieve size
    hWndControl=GetDlgItem(RawDumphDlg,IDC_EDIT_RAW_DUMP_SIZE);
    SendMessage((HWND) hWndControl,(UINT) WM_GETTEXT,MAX_PATH,(LPARAM)psz);

    if(_tcsnicmp(psz,_T("0x"),2)==0)
        iScanfRes=_stscanf(psz,_T("0x%x"),&Size);
    else
        iScanfRes=_stscanf(psz,_T("%u"),&Size);
    if ((!iScanfRes)||(!Size))
    {
        MessageBox(RawDumphDlg,_T("Bad Size"),_T("Error"),MB_OK|MB_ICONERROR|MB_TOPMOST);
        return;
    }


    // make dump
    BYTE* Buffer=new BYTE[Size];
    SIZE_T ReadSize=0;

    if (UserMode)
    {
        CProcessMemory ProcessMemory(ProcessId,TRUE);
        if (!ProcessMemory.Read((LPCVOID)StartAddress,Buffer,Size,&ReadSize))
        {
            if (ReadSize==0)
            {
                MessageBox(RawDumphDlg,_T("Error reading memory"),_T("Error"),MB_OK|MB_ICONERROR|MB_TOPMOST);
                delete[] Buffer;
                return;
            }

            // else
            Size=ReadSize;
            _stprintf(psz,_T("Error reading memory.\r\nOnly first 0x%X bytes are readable"),ReadSize);
            MessageBox(RawDumphDlg,psz,_T("Warning"),MB_OK|MB_ICONWARNING|MB_TOPMOST);
        }
    }
    else
    {
        CKernelMemoryAccessInterface KMem;
        KMem.StartDriver();
        KMem.OpenDriver();
        if (KMem.ReadMemory(StartAddress,Size,Buffer,&ReadSize))
        {
            if (ReadSize==0)
            {
                MessageBox(RawDumphDlg,_T("Error reading memory"),_T("Error"),MB_OK|MB_ICONERROR|MB_TOPMOST);
                delete[] Buffer;
                return;
            }

            // else
            Size=ReadSize;
            _stprintf(psz,_T("Error reading memory.\r\nOnly first 0x%X bytes are readable"),ReadSize);
            MessageBox(RawDumphDlg,psz,_T("Warning"),MB_OK|MB_ICONWARNING|MB_TOPMOST);
        }
        KMem.CloseDriver();
    }
    /////////////////
    // save dump
    ////////////////

    OPENFILENAME ofn;
    TCHAR pszFileName[MAX_PATH];

    
    // save file dialog
    memset(&ofn,0,sizeof (OPENFILENAME));
    ofn.lStructSize=sizeof (OPENFILENAME);
    ofn.hwndOwner=RawDumphDlg;
    ofn.hInstance=RawDumphInstance;
    ofn.lpstrFilter=_T("dmp\0*.dmp\0All\0*.*\0");
    ofn.nFilterIndex = 1;
    ofn.Flags=OFN_EXPLORER|OFN_NOREADONLYRETURN|OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt=_T("dmp");
    *pszFileName=0;
    ofn.lpstrFile=pszFileName;
    ofn.nMaxFile=MAX_PATH;
    
    if (!GetSaveFileName(&ofn))
    {
        delete[] Buffer;
        return;
    }

    // write dump
    HANDLE hFile = CreateFile(
        ofn.lpstrFile,
        GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ|FILE_SHARE_WRITE, 
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile==INVALID_HANDLE_VALUE)
    {
        CAPIError::ShowLastError();
        delete[] Buffer;
        return;
    }

    if (!WriteFile(hFile,
                    Buffer,
                    Size,
                    &Size,
                    NULL
                    ))
    {
        CAPIError::ShowLastError();
        CloseHandle(hFile);
        delete[] Buffer;
        return;
    }

    CloseHandle(hFile);
    delete[] Buffer;

    // show message information
    MessageBox(NULL,_T("Dump successfully completed"),_T("Information"),MB_OK|MB_ICONINFORMATION|MB_TOPMOST);

    return;
}