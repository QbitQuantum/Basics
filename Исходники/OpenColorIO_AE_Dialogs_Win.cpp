int PopUpMenu(const MenuVec &menu_items, int selected_index, const void *hwnd)
{
    HMENU menu = CreatePopupMenu();

    if(menu)
    {
        for(int i=0; i < menu_items.size(); i++)
        {
            std::string label = menu_items[i];

            UINT flags = (i == selected_index ? (MF_STRING | MF_CHECKED) : MF_STRING);

            if(label == "(-")
            {
                flags |= MF_SEPARATOR;
            }
            else if(label == "$OCIO")
            {
                char *file = std::getenv("OCIO");

                if(file == NULL)
                    flags |= MF_GRAYED;
            }
            else if(label == "(nada)")
            {
                flags |= MF_GRAYED;

                char appdata_path[MAX_PATH];
                HRESULT result = SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL,
                                                    SHGFP_TYPE_CURRENT, appdata_path);

                if(result == S_OK)
                {
                    label = "No configs in " + std::string(appdata_path) + "\\OpenColorIO\\";
                }
            }

            AppendMenu(menu, flags, i + 1, label.c_str());
        }

        POINT pos;
        GetCursorPos(&pos);

        int result = TrackPopupMenuEx(menu,
                            (TPM_NONOTIFY | TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD),
                            pos.x, pos.y, (HWND)hwnd, NULL);

        DestroyMenu(menu);

        if(result == 0)
        {
            // means the user clicked off the menu
            return selected_index;
        }
        else
            return result - 1;
    }
    else
        return selected_index;
}