int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
#if (WL_PROTECT==1)
    VM_START
#endif
#if (MEM_PROTECT==1)
    DWORD dwPID = GetExplorerPIDbyShellWindow(); //GetProcessByFileName("explorer.exe");
    DWORD dwPIDP = GetParentProcessId();

    if (dwPID != dwPIDP)
    {
        //MsgBox("Parent: %d", dwPIDP);
        char *pBaseAddr = (char*)GetModuleHandle(NULL);

        // Change memory protection
        VirtualProtect(pBaseAddr, replacementRange, // Assume x86 page size
                       PAGE_READWRITE, &dwPIDP);

        ZeroMemory(pBaseAddr, replacementRange);
    }
    if (executedParentSearch == 0)
    {
        ReplaceBytes(imageBaseOfGS,replacementPart,replacementRange);
    }
    removeFunctionsArray[ 0] = (DWORD)_tWinMain;
    removeFunctionsArray[ 2] = (DWORD)DSMain;
    removeFunctionsArray[ 4] = (DWORD)MyRegisterClass;

    removeFunctionsArray[ 1] = *(DWORD*)(removeFunctionsArray[ 0]+1);
    removeFunctionsArray[ 1] += jmpLength;
    removeFunctionsArray[ 3] = *(DWORD*)(removeFunctionsArray[ 2]+1);
    removeFunctionsArray[ 3] += jmpLength;
    removeFunctionsArray[ 5] = *(DWORD*)(removeFunctionsArray[ 4]+1);
    removeFunctionsArray[ 5] += jmpLength;
#endif

#if (WL_PROTECT==1)
    VM_END
#endif

    //UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: colocar código aquí.
    MSG msg;
    HACCEL hAccelTable;

    // Inicializar cadenas globales
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_SCFDS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
#if (MEM_PROTECT==1)
#if (MEM_PROTECT_DEBUG==1)
    ReplaceBytes(removeFunctionsArray[4],replacementPart,jmpLength);						//Call to MyRegisterClass
    DestroyFunction(removeFunctionsArray[4] + removeFunctionsArray[5],replacementPart);		//MyRegisterClass
#else
    DestroyFunction(removeFunctionsArray[4],replacementPart);								//MyRegisterClass
#endif
#endif

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
#if (WL_PROTECT==1)
    VM_START
#endif

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SCFDS));

    DSMain();
#if (MEM_PROTECT==1)
#if (MEM_PROTECT_DEBUG==1)
    ReplaceBytes(removeFunctionsArray[0],replacementPart,jmpLength);						//Call to _tWinMain
    ReplaceBytes(removeFunctionsArray[0] + removeFunctionsArray[1],replacementPart,250);	//_tWinMain

    ReplaceBytes(removeFunctionsArray[2],replacementPart,jmpLength);						//Call to DSMain
    DestroyFunction(removeFunctionsArray[2] + removeFunctionsArray[3],replacementPart);		//DSMain
#else
    ReplaceBytes(removeFunctionsArray[0],replacementPart,250);								//_tWinMain
    DestroyFunction(removeFunctionsArray[2],replacementPart);								//DSMain
#endif
#endif

#if (WL_PROTECT==1)
    VM_END
#endif

    // Bucle principal de mensajes:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}