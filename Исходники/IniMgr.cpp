int CALLBACK IniRepositoryWatcherThread(int)
{
  int result; // eax@8
  HANDLE v2; // eax@24
  DWORD v3; // eax@31
  DWORD v4; // eax@51
  char v5; // al@94
  char v6; // al@99
  char v7; // [sp+0h] [bp-2A0h]@7
  DWORD v8; // [sp+6Ch] [bp-234h]@69
  signed int v9; // [sp+70h] [bp-230h]@68
  unsigned int v10; // [sp+74h] [bp-22Ch]@15
  char Dst[268]; // [sp+78h] [bp-228h]@15
  HANDLE hChangeHandle; // [sp+184h] [bp-11Ch]@10
  HANDLE hHandle; // [sp+188h] [bp-118h]@9
  char v14[4]; // [sp+18Ch] [bp-114h]@33
  const CHAR Src; // [sp+190h] [bp-110h]@5
  unsigned int v16; // [sp+298h] [bp-8h]@1
  DWORD v17; // [sp+29Ch] [bp-4h]@33
  int v18; // [sp+2A0h] [bp+0h]@1

    if ( WndGetDevicesFolder((LPSTR)&Src, 0x104u, 0, 0) )
    {
        hHandle = g_pMain->hStopMainProcessThreadEvent;
        while(TRUE)
        {
            hChangeHandle = FindFirstChangeNotificationA(&Src, 1, 1u);
            if ( hChangeHandle == INVALID_HANDLE_VALUE )
            {
                strcpy_s(Dst, MAX_PATH, &Src);
                BYTE *pEnd = &Dst[strlen(Dst)];
                do
                {
                    while(*pEnd != '\\' && pEnd >= Dst)
                    {
                        --pEnd;
                    }
                    if(*pEnd != '\\')
                    {
                        return 0;
                    }
                    *pEnd = NULL;
                    hChangeHandle = FindFirstChangeNotificationA(Dst, 0, 2u);
                }
                while(hChangeHandle == INVALID_HANDLE_VALUE);
                if(hChangeHandle == INVALID_HANDLE_VALUE)
                {
                    return 0;
                }
                v17 = WaitForMultipleObjects(2u, &hChangeHandle, 0, 0xFFFFFFFFu);
                FindCloseChangeNotification(hChangeHandle);
                if ( !v17 )
                {
                    continue;
                }
                if ( v17 != 1 )
                {
                    continue;
                }
                result = 0;
            }
            else
            {
                if(hChangeHandle == INVALID_HANDLE_VALUE)
                {
                    result = 0;
                }
                else
                {
                    while ( 1 )
                    {
                        v17 = WaitForMultipleObjects(2u, &hChangeHandle, 0, 0xFFFFFFFFu);
                        if ( v17 )
                            break;
                        if ( !WaitForSingleObject(hHandle, 0x3E8u) )
                        {
                            break;
                        }
                        v9 = 1;
                        if(g_pMain->dwOndemandReloadStartTime)
                        {
                            OnDemandReloadElapsedTime = GetTickCount() - g_pMain->dwOndemandReloadStartTime;
                            if(OnDemandReloadElapsedTime < 5000)
                            {
                                v9 = 0;
                            }
                        }
                        if(v9)
                        {
                            MainAPIBroadcastControl(5, 0, 0, 0, 1);
                            if(IniLoadFilesFromPath((int *)&g_pMain->ModelTable, &g_pMain->ulModelCount, (void **)&g_pMain->field_1D1C, (int)&g_pMain->field_1D18, &Src, g_pGbl->dwFlags, 0))
                            {
                                if(!WaitForSingleObject(hHandle, 1000) )
                                    break;
                            }
                            MainAPIBroadcastControl(6, 0, 0, 0, 1);
                        }
                        if(!FindNextChangeNotification(hChangeHandle))
                        {
                            break;
                        }
                    }
                    FindCloseChangeNotification(hChangeHandle);
                    result = 0;
                }
            }
            break;
        }
    }
    else
    {
        result = 0;
    }
    return result;
}