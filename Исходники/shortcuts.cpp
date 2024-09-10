ShortcutsPlugin::~ShortcutsPlugin()
{
#ifdef WIN32
    QWidget *main = getMainWindow();
    if (main && oldProc) {
        if (IsWindowUnicode(main->winId())) {
            SetWindowLongW(main->winId(), GWL_WNDPROC, (LONG)oldProc);
        } else {
            SetWindowLongA(main->winId(), GWL_WNDPROC, (LONG)oldProc);
        }
    }
#else
#ifndef USE_KDE
    qt_set_x11_event_filter(oldFilter);
#endif
#endif
    releaseKeys();
    free_data(shortcutsData, &data);
}