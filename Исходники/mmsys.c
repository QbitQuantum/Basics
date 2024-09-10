DWORD
MMSYS_InstallDevice(HDEVINFO hDevInfo, PSP_DEVINFO_DATA pspDevInfoData)
{
    UINT Length;
    LPWSTR pBuffer;
    WCHAR szBuffer[MAX_PATH];
    HINF hInf;
    PVOID Context;
    BOOL Result;
    SC_HANDLE hSCManager, hService;
    WCHAR WaveName[20];
    HKEY hKey;
    DWORD BufferSize;
    ULONG Index;

    if (!IsEqualIID(&pspDevInfoData->ClassGuid, &GUID_DEVCLASS_SOUND) &&
        !IsEqualIID(&pspDevInfoData->ClassGuid, &GUID_DEVCLASS_MEDIA))
        return ERROR_DI_DO_DEFAULT;

    Length = GetWindowsDirectoryW(szBuffer, MAX_PATH);
    if (!Length || Length >= MAX_PATH - 14)
    {
        return ERROR_GEN_FAILURE;
    }

    pBuffer = PathAddBackslashW(szBuffer);
    if (!pBuffer)
    {
        return ERROR_GEN_FAILURE;
    }

    wcscpy(pBuffer, L"inf\\audio.inf");

    hInf = SetupOpenInfFileW(szBuffer,
                             NULL,
                            INF_STYLE_WIN4,
                            NULL);

    if (hInf == INVALID_HANDLE_VALUE)
    {
        return ERROR_GEN_FAILURE;
    }

    Context = SetupInitDefaultQueueCallback(NULL);
    if (Context == NULL)
    {
        SetupCloseInfFile(hInf);
        return ERROR_GEN_FAILURE;
    }

    Result = SetupInstallFromInfSectionW(NULL,
                                         hInf,
                                         L"AUDIO_Inst.NT",
                                         SPINST_ALL,
                                         NULL,
                                         NULL,
                                         SP_COPY_NEWER,
                                         SetupDefaultQueueCallbackW,
                                         Context,
                                         NULL,
                                         NULL);

    if (Result)
    {
        Result = SetupInstallServicesFromInfSectionW(hInf,
                                                     L"Audio_Inst.NT.Services",
                                                     0);
    }

    SetupTermDefaultQueueCallback(Context);
    SetupCloseInfFile(hInf);



    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager)
    {
        return ERROR_DI_DO_DEFAULT;
    }

    hService = OpenService(hSCManager, L"RosAudioSrv", SERVICE_ALL_ACCESS);
    if (hService)
    {
        /* Make RosAudioSrv start automatically */
        ChangeServiceConfig(hService, SERVICE_NO_CHANGE, SERVICE_AUTO_START, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

        StartService(hService, 0, NULL);
        CloseServiceHandle(hService);
    }
    CloseServiceHandle(hSCManager);

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Drivers32", 0, GENERIC_READ | GENERIC_WRITE, &hKey) == ERROR_SUCCESS)
    {
        szBuffer[Length] = '\0';
        pBuffer = PathAddBackslashW(szBuffer);
        wcscpy(pBuffer, L"system32\\wdmaud.drv");

        for(Index = 1; Index <= 4; Index++)
        {
            swprintf(WaveName, L"wave%u", Index);
            if (RegQueryValueExW(hKey, WaveName, 0, NULL, NULL, &BufferSize) != ERROR_MORE_DATA)
            {
                /* Store new audio driver entry */
                RegSetValueExW(hKey, WaveName, 0, REG_SZ, (LPBYTE)szBuffer, (wcslen(szBuffer)+1) * sizeof(WCHAR));
                break;
            }
            else
            {
                WCHAR Buffer[MAX_PATH];
                BufferSize = sizeof(Buffer);

                if (RegQueryValueExW(hKey, WaveName, 0, NULL, (LPBYTE)Buffer, &BufferSize) == ERROR_SUCCESS)
                {
                    /* Make sure the buffer is zero terminated */
                    Buffer[MAX_PATH-1] = L'\0';

                    if (!wcsicmp(Buffer, szBuffer))
                    {
                        /* An entry already exists */
                        break;
                    }
                }
            }
        }
        RegCloseKey(hKey);
    }
    InstallSystemSoundScheme();

    return ERROR_DI_DO_DEFAULT;

}