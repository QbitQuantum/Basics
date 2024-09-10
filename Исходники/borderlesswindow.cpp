void BorderlessWindow::toggleShadow()
{
    if (borderless)
    {
        aeroShadow = !aeroShadow;
        const MARGINS c_shadowOn = {1, 1, 1, 1};
        const MARGINS c_shadowOff = {0, 0, 0, 0};
        DwmExtendFrameIntoClientArea(hWnd, (aeroShadow) ? (&c_shadowOn) : (&c_shadowOff));
    }
}