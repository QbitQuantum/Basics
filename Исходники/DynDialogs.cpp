int InputBox(HWND hwnd, LPCTSTR prompt, LPCTSTR title, LPTSTR buffer, INT buflength) 
{ 
    HGLOBAL  hgbl; 
    LPWORD   lpw; 
    LRESULT  ret; 
    DWORD    style; 

    hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024); 
    if(!hgbl) return 0; 
    LPVOID lpv = GlobalLock(hgbl); 

    // Prepare the dialog box 
    style = DS_SETFONT | DS_CENTER | DS_3DLOOK | WS_POPUP | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION | WS_VISIBLE; 
    lpw = InitDialog(lpv, title, style, 4, "MS Sans Serif", 8, 0, 0, 319, 47); 

    // OK-Button 
    style = WS_CHILD | WS_VISIBLE | WS_TABSTOP |BS_DEFPUSHBUTTON; 
    lpw = CreateDlgControl(lpw, BUTTON_CLASS, IDOK, "OK", style, 264, 7, 48, 15); 

    // Cancel-Button 
    style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON; 
    lpw = CreateDlgControl(lpw, BUTTON_CLASS, IDCANCEL, "Abbrechen", style, 264, 26, 48, 15); 

    // Text to prompt 
    style = WS_CHILD | WS_VISIBLE | SS_LEFT; 
    lpw = CreateDlgControl(lpw, STATIC_CLASS, ID_INFOTEXT, prompt, style, 10, 9, 129, 16); 

    // Edit-Control 
    style = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP; 
    lpw = CreateDlgControl(lpw, EDIT_CLASS, ID_INPUT, "", style, 10, 26, 249, 13); 

    GlobalUnlock(hgbl); 
    int data[2] = {(int)buffer, buflength}; 
    ret = DialogBoxIndirectParamA(NULL, (LPDLGTEMPLATE)hgbl, hwnd, 
                                 (DLGPROC)InputBoxDlgProc, (int)data); 
    GlobalFree(hgbl); 
    return (ret > 0) ? ret : 0; 
} 