void gg_initpopups(GGPROTO* gg)
{
    char szDescr[256], szName[256];
    POPUPCLASS puc = {0};

    puc.cbSize = sizeof(puc);
    puc.PluginWindowProc = PopupWindowProc;

    puc.ptszDescription = szDescr;
    puc.pszName = szName;
    puc.colorBack = RGB(173, 206, 247);
    puc.colorText =  GetSysColor(COLOR_WINDOWTEXT);
    puc.hIcon = CopyIcon(LoadIconEx("main", FALSE));
    ReleaseIconEx("main", FALSE);
    puc.iSeconds = 4;
    mir_snprintf(szDescr, SIZEOF(szDescr), "%s/%s", GG_PROTONAME, Translate("Notify"));
    mir_snprintf(szName, SIZEOF(szName), "%s_%s", GG_PROTO, "Notify");
    CallService(MS_POPUP_REGISTERCLASS, 0, (WPARAM)&puc);

    puc.ptszDescription = szDescr;
    puc.pszName = szName;
    puc.colorBack = RGB(191, 0, 0); // Red
    puc.colorText = RGB(255, 245, 225); // Yellow
    puc.iSeconds = 60;
    puc.hIcon = (HICON)LoadImage(NULL, IDI_WARNING, IMAGE_ICON, 0, 0, LR_SHARED);
    mir_snprintf(szDescr, SIZEOF(szDescr), "%s/%s", GG_PROTONAME, Translate("Error"));
    mir_snprintf(szName, SIZEOF(szName), "%s_%s", GG_PROTO, "Error");
    CallService(MS_POPUP_REGISTERCLASS, 0, (WPARAM)&puc);
}