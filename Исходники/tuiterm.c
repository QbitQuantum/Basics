static DWORD WINAPI
TuiConsoleThread(PVOID Data)
{
    PTUI_CONSOLE_DATA TuiData = (PTUI_CONSOLE_DATA)Data;
    PCONSOLE Console = TuiData->Console;
    HWND NewWindow;
    MSG msg;

    NewWindow = CreateWindowW(TUI_CONSOLE_WINDOW_CLASS,
                              Console->Title.Buffer,
                              0,
                              -32000, -32000, 0, 0,
                              NULL, NULL,
                              ConSrvDllInstance,
                              (PVOID)Console);
    if (NULL == NewWindow)
    {
        DPRINT1("CONSRV: Unable to create console window\n");
        return 1;
    }
    TuiData->hWindow = NewWindow;

    SetForegroundWindow(TuiData->hWindow);
    NtUserConsoleControl(ConsoleAcquireDisplayOwnership, NULL, 0);

    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}