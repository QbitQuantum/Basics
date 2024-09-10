STDMETHODIMP CAudioRawFileRenderer::setParameter(__int64 command, __int64  data1, __int64  data2, __int64 data3)
{
    CAutoLock lock(&m_ReceiveLock);
    
    HRESULT hr=NOERROR;

    switch(command)
        {
        case CMD_SPLITEVENT:
        if ( 
            ((m_SplitMode==OPT_SPLIT_DISCONTINUITY)&&m_IsDiscontinuity) ||
             (m_SplitMode==OPT_SPLIT_EVENT)
           )
            {
            CloseFile();
            dprintf("SplitEvent");
            if (lstrlenW(m_pOldFileName)>0)
                {
                char str[264]="";
                char strOld[264]="";
                DWORD dwWritten=0;
                DWORD result=0;
                HANDLE hFile=INVALID_HANDLE_VALUE;

		        WideCharToMultiByte(CP_ACP, 0, m_pFileName   , -1, str   , 264, NULL, NULL);
		        WideCharToMultiByte(CP_ACP, 0, m_pOldFileName, -1, strOld, 264, NULL, NULL);
                MoveFile(str, strOld);

                hFile = CreateFile( strOld,   // The filename
                                    GENERIC_WRITE,         // File access
                                    (DWORD) 0,             // Share access
                                    NULL,                  // Security
                                    OPEN_EXISTING,         // Open flags
                                    FILE_ATTRIBUTE_NORMAL,             // More flags
                                    NULL);                 // Template
                if (INVALID_HANDLE_VALUE!=hFile)
                    {
                    result=SetFilePointer(hFile, 0, NULL, FILE_END); 
                    LockFile(hFile, result, 0, result + sizeof(m_OldID3), 0); 
                    result=WriteFile(hFile,(PVOID)&m_OldID3,(DWORD)sizeof(m_OldID3),&dwWritten,NULL);
                    UnlockFile(hFile, result, 0, result + sizeof(m_OldID3), 0); 
                    CloseHandle(hFile);
                    }
                
                }
            OpenFile();
            }
            break;

        case CMD_SPLITDATA:
            {
            dprintf("SplitData");
            lstrcpyW(m_pOldFileName, (WCHAR *)data2);
            CopyMemory(&m_OldID3, (struct ID3 *)data1, sizeof(struct ID3));
            }
            break;
        
        case CMD_SPLITMODE:
            m_SplitMode=(int)data1;
            break;

        default:
            hr=E_NOTIMPL;
            break;
        }
    return(hr);
}