static inline bool detectKDEDesktopIsRunning()
{
    const QByteArray xdgCurrentDesktop = qgetenv("XDG_CURRENT_DESKTOP");

    if (!xdgCurrentDesktop.isEmpty())
        return (xdgCurrentDesktop.toUpper() == "KDE");

    // Classic fallbacks

    if (!qgetenv("KDE_FULL_SESSION").isEmpty())
        return true;

    return false;
}