Bool
rdpDestroyWindow(WindowPtr pWindow)
{
    ScreenPtr pScreen;
    rdpWindowRec *priv;
    Bool rv;

    LLOGLN(10, ("rdpDestroyWindow:"));
    priv = GETWINPRIV(pWindow);
    pScreen = pWindow->drawable.pScreen;
    pScreen->DestroyWindow = g_rdpScreen.DestroyWindow;
    rv = pScreen->DestroyWindow(pWindow);
    pScreen->DestroyWindow = rdpDestroyWindow;

    if (g_use_rail)
    {
    }

    return rv;
}