/**
 * @brief this one gets the active application window.
 */
Window XfitMan::getActiveAppWindow() const
{
    Window window = getActiveWindow();
    if (window == 0)
        return 0;

    if (acceptWindow(window))
        return window;

    Window transFor = None;
    if (XGetTransientForHint(QX11Info::display(), window, &transFor))
        return transFor;

    return 0;
}