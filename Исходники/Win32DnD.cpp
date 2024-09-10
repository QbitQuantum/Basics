String FromWin32CF(int cf)
{
    GuiLock __;
    if(cf == CF_TEXT)
        return "text";
    if(cf == CF_UNICODETEXT)
        return "wtext";
    if(cf == CF_DIB)
        return "dib";
#ifndef PLATFORM_WINCE
    if(cf == CF_HDROP)
        return "files";
#endif
    char h[256];
    GetClipboardFormatNameA(cf, h, 255);
    return h;
}