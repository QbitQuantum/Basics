BOOL
ConsoleSetFocus(
    HWND hWnd,
    HANDLE hConsole,
    HKL hKL
    )
{
    PCONSOLE_TABLE ConTbl;
    HKL OldhKL;

    ConTbl = SearchConsole(hConsole);
    if (ConTbl == NULL) {
        DBGPRINT(("CONIME: Error! Cannot found registed Console\n"));
        return FALSE;
    }

    if ( gfDoNotKillFocus ){
        gfDoNotKillFocus = FALSE;
    }

    OldhKL = ConTbl->hklActive ;
    ConTbl->hklActive = hKL;
    ActivateKeyboardLayout(ConTbl->hklActive, 0);
    ImmAssociateContext(hWnd, ConTbl->hIMC_Current);

    if (OldhKL == 0) {
        GetIMEName( ConTbl );
        ConTbl->ImmGetProperty = ImmGetProperty(ConTbl->hklActive , IGP_PROPERTY);
    }

//v-hirshi Jun.13.1996 #if defined(LATER_DBCS)  // kazum
    ImmSetActiveContextConsoleIME(hWnd, TRUE);
//v-hirshi Jun.13.1996 #endif

    LastConsole = hConsole;

#ifdef DEBUG_MODE
    DisplayInformation(hWnd, hConsole);
#endif

    ImeUISetOpenStatus( hWnd );
    if (ConTbl->lpCompStrMem != NULL)
        ReDisplayCompositionStr( hWnd );

    return TRUE;
}