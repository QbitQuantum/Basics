/*
 * mswin_tw_wm_command() - WM_CONTEXTMENU handler for textwindows
 */
static void
mswin_tw_wm_contextmenu(MSWIN_TEXTWINDOW *mswin_tw, HWND hwnd, HWND hwndContext,
    int xPos, int yPos)
{
   HMENU hMenu;

    hMenu = CreatePopupMenu();
    if(hMenu)
    {
        int i;
        CHARRANGE cr;
        MENUITEMINFO mitem;
        static const struct
        {
            UINT wID;
            LPTSTR dwTypeData;
        } s_popup_menu[] =
        {
            { IDM_EDIT_COPY,        TEXT("&Copy")        },
            { IDM_EDIT_COPY_APPEND, TEXT("Copy &Append") },
            { IDM_EDIT_CLEAR,       TEXT("Clea&r")       },
        };

        memset(&mitem, 0, sizeof(MENUITEMINFO));
        mitem.cbSize = sizeof(MENUITEMINFO);
        mitem.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
        mitem.fType = MFT_STRING;

        SendMessage(mswin_tw->hwnd_edit, EM_EXGETSEL, (WPARAM)0, (LPARAM)&cr);

        for(i = 0; i < ARRAYSIZE(s_popup_menu); i++)
        {
            switch(s_popup_menu[i].wID)
            {
            case IDM_EDIT_CLEAR:
                // Only enable it if there is a clear callback set.
                mitem.fState = (mswin_tw->clear_callback) ? 
                    MFS_ENABLED : MFS_GRAYED;
                break;
            case IDM_EDIT_COPY:
            case IDM_EDIT_COPY_APPEND:
                // Only enable if there is a selection.
                mitem.fState = (cr.cpMax > cr.cpMin) ? 
                    MFS_ENABLED : MFS_GRAYED;
                break;
            default:
                mitem.fState = MFS_ENABLED;
                break;
            }
            
            mitem.wID = s_popup_menu[i].wID;
            mitem.dwTypeData = s_popup_menu[i].dwTypeData;
            mitem.cch = (UINT)_tcslen(s_popup_menu[i].dwTypeData);
            InsertMenuItem(hMenu, i, FALSE, &mitem);
        }

        TrackPopupMenu(hMenu,
               TPM_LEFTALIGN | TPM_TOPALIGN |
               TPM_RIGHTBUTTON | TPM_LEFTBUTTON,
               xPos, yPos, 0, hwnd, NULL);

        DestroyMenu(hMenu);
    }
}