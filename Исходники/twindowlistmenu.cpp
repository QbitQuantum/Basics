static TQCString twinName() {
    TQCString appname;
    int screen_number = DefaultScreen(tqt_xdisplay());
    if (screen_number == 0)
        appname = "twin";
    else
        appname.sprintf("twin-screen-%d", screen_number);
    return appname;
}