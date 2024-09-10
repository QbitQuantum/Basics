/*
 * Check if Window is onscreen with the appropriate name.
 *
 * Windows are not created synchronously.  So we do not know
 * when and if the window will be created/shown on screen.
 * This function implements a polling mechanism to determine
 * creation.
 * A more complicated method would be to use SetWindowsHookEx.
 * Since polling worked fine in my testing, no reason to implement
 * the other.  Comments about other methods of determining when
 * window creation happened were not encouraging (not including
 * SetWindowsHookEx).
 */
static HWND CheckWindowCreated(const char *winName, BOOL closeWindow, int testParams)
{
    HWND window = NULL;
    int i;

    /* Poll for Window Creation */
    for (i = 0; window == NULL && i < PDDE_POLL_NUM; i++)
    {
        Sleep(PDDE_POLL_TIME);
        /* Specify the window class name to make sure what we find is really an
         * Explorer window. Explorer used two different window classes so try
         * both.
         */
        window = FindWindowA("ExplorerWClass", winName);
        if (!window)
            window = FindWindowA("CabinetWClass", winName);
    }
    ok (window != NULL, "Window \"%s\" was not created in %i seconds - assumed failure.%s\n",
        winName, PDDE_POLL_NUM*PDDE_POLL_TIME/1000, GetStringFromTestParams(testParams));

    /* Close Window as desired. */
    if (window != NULL && closeWindow)
    {
        SendMessageA(window, WM_SYSCOMMAND, SC_CLOSE, 0);
        window = NULL;
    }
    return window;
}