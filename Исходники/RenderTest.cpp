void InitializeMenuItems(HMENU popupMenu)
{
    int count = GetMenuItemCount(popupMenu);
    for (int i = 0; i < count; ++i)
    {
        MENUITEMINFO info;
        info.cbSize = sizeof(info);
        info.fMask = MIIM_ID | MIIM_STATE;

        if (!GetMenuItemInfo(popupMenu, i, TRUE, &info))
            break;

        bool check = false;
        bool disable = false;

        switch (info.wID)
        {
        case ID_EDIT_COPY:
            disable = g_text.empty();
            break;

        case ID_EDIT_PASTE:
            disable = !IsClipboardFormatAvailable(CF_TEXT);
            break;

        case ID_EDIT_DECREASETEXTSIZE:
            disable = (g_fontSize == g_minFontSize);
            break;

        case ID_VIEW_SHOWMAGNIFIER:
            check = g_magnifier.visible;
            break;

        case ID_MAGNIFIERTYPE_VECTOR:
            check = (g_magnifier.type == MagnifierInfo::Vector);
            disable = (g_measuringMode != DWRITE_MEASURING_MODE_NATURAL);
            break;

        case ID_MAGNIFIERTYPE_PIXELS:
            check = (g_magnifier.type == MagnifierInfo::Pixel);
            break;

        case ID_MAGNIFIERTYPE_SUBPIXELS:
            check = (g_magnifier.type == MagnifierInfo::Subpixel);
            disable = (g_rendererID == RendererD2D);
            break;

        case ID_MAGNIFIERSCALE_3X:
            check = (g_magnifier.scale == 3);
            break;

        case ID_MAGNIFIERSCALE_6X:
            check = (g_magnifier.scale == 6);
            break;

        case ID_OPTIONS_NATURALMODE:
            check = (g_measuringMode == DWRITE_MEASURING_MODE_NATURAL);
            break;

        case ID_OPTIONS_GDICLASSICMODE:
            check = (g_measuringMode == DWRITE_MEASURING_MODE_GDI_CLASSIC);
            break;

        case ID_OPTIONS_GDINATURALMODE:
            check = (g_measuringMode == DWRITE_MEASURING_MODE_GDI_NATURAL);
            break;

        case ID_OPTIONS_USEDIRECT2D:
            check = (g_rendererID == RendererD2D);
            break;

        case ID_OPTIONS_USEDIRECTWRITE:
            check = (g_rendererID == RendererDWrite);
            break;
        }

        UINT newState = 
            (check ? MFS_CHECKED : 0) | 
            (disable ? MFS_DISABLED : 0);

        if (newState != info.fState)
        {
            info.fMask = MIIM_STATE;
            info.fState = newState;
            SetMenuItemInfo(popupMenu, i, TRUE, &info);
        }
    }
}