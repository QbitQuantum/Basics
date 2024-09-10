sal_Int32 SAL_CALL osl_reportError(sal_uInt32 nType, const sal_Char* pszMessage)
{
    UINT nFlags;
    int nDisposition;

    // active popup window for the current thread
    HWND hWndParent = GetActiveWindow();
    if (hWndParent != NULL)
        hWndParent = GetLastActivePopup(hWndParent);

    /* set message box flags */
    nFlags = MB_TASKMODAL | MB_ICONERROR | MB_YESNOCANCEL | MB_DEFBUTTON2 | MB_SETFOREGROUND;
    if (hWndParent == NULL)
        nFlags |= MB_SERVICE_NOTIFICATION;

    // display the assert
    nDisposition = MessageBox(hWndParent, pszMessage, "Exception!", nFlags);
    (void)nType; //unused, but part of public API/ABI
    return nDisposition;
}