void PDC_set_title(const char *title)
{
#ifdef PDC_WIDE
    wchar_t wtitle[512];
#endif
    PDC_LOG(("PDC_set_title() - called:<%s>\n", title));

#ifdef PDC_WIDE
    PDC_mbstowcs(wtitle, title, 511);
    SetConsoleTitleW(wtitle);
#else
    SetConsoleTitleA(title);
#endif
}