static char* winDialogGetActiveWindowAttrib(Ihandle* ih)
{
    WINDOWINFO wininfo;
    wininfo.cbSize = sizeof(WINDOWINFO);
    GetWindowInfo(ih->handle, &wininfo);
    if (wininfo.dwWindowStatus & WS_ACTIVECAPTION)
        return "Yes";
    else
        return "No";
}