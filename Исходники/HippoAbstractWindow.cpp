void
HippoAbstractWindow::hide(void)
{
    if (!showing_)
        return;

#if 0
    g_debug("SIZING: hide %p %s",
        window_, HippoUStr(getClassName()).c_str());
#endif

    if (animate_)
        AnimateWindow(window_, 400, AW_BLEND | AW_HIDE);
    else
        ShowWindow(window_, SW_HIDE);

    showing_ = false;
}