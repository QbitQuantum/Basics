    virtual HRESULT STDMETHODCALLTYPE AppendMenu(
        OUT HMENU* phMenu)
    {
        HMENU hMenu, hSettingsMenu;
        DWORD dwLogoff;
        BOOL bWantLogoff;
        UINT uLastItemsCount = 5; /* 5 menu items below the last separator */
        WCHAR szUser[128];

        TRACE("ITrayPriv::AppendMenu\n");

        hMenu = LoadPopupMenu(hExplorerInstance,
                              MAKEINTRESOURCE(IDM_STARTMENU));
        *phMenu = hMenu;
        if (hMenu == NULL)
            return E_FAIL;

        /* Remove menu items that don't apply */

        dwLogoff = SHRestricted(REST_STARTMENULOGOFF);
        bWantLogoff = (dwLogoff == 2 ||
                       SHRestricted(REST_FORCESTARTMENULOGOFF) ||
                       GetExplorerRegValueSet(HKEY_CURRENT_USER,
                       TEXT("Advanced"),
                       TEXT("StartMenuLogoff")));

        /* Favorites */
        if (!GetExplorerRegValueSet(HKEY_CURRENT_USER,
            TEXT("Advanced"),
            TEXT("StartMenuFavorites")))
        {
            DeleteMenu(hMenu,
                       IDM_FAVORITES,
                       MF_BYCOMMAND);
        }

        /* Documents */
        if (SHRestricted(REST_NORECENTDOCSMENU))
        {
            DeleteMenu(hMenu,
                       IDM_DOCUMENTS,
                       MF_BYCOMMAND);
        }

        /* Settings */
        hSettingsMenu = FindSubMenu(hMenu,
                                    IDM_SETTINGS,
                                    FALSE);
        if (hSettingsMenu != NULL)
        {
            if (SHRestricted(REST_NOSETFOLDERS))
            {
                /* Control Panel */
                if (SHRestricted(REST_NOCONTROLPANEL))
                {
                    DeleteMenu(hSettingsMenu,
                               IDM_CONTROLPANEL,
                               MF_BYCOMMAND);

                    /* Delete the separator below it */
                    DeleteMenu(hSettingsMenu,
                               0,
                               MF_BYPOSITION);
                }

                /* Network Connections */
                if (SHRestricted(REST_NONETWORKCONNECTIONS))
                {
                    DeleteMenu(hSettingsMenu,
                               IDM_NETWORKCONNECTIONS,
                               MF_BYCOMMAND);
                }

                /* Printers and Faxes */
                DeleteMenu(hSettingsMenu,
                           IDM_PRINTERSANDFAXES,
                           MF_BYCOMMAND);
            }

            /* Security */
            if (GetSystemMetrics(SM_REMOTECONTROL) == 0 ||
                SHRestricted(REST_NOSECURITY))
            {
                DeleteMenu(hSettingsMenu,
                           IDM_SECURITY,
                           MF_BYCOMMAND);
            }

            if (GetMenuItemCount(hSettingsMenu) == 0)
            {
                DeleteMenu(hMenu,
                           IDM_SETTINGS,
                           MF_BYCOMMAND);
            }
        }

        /* Search */
        /* FIXME: Enable after implementing */
        /* if (SHRestricted(REST_NOFIND)) */
    {
        DeleteMenu(hMenu,
                   IDM_SEARCH,
                   MF_BYCOMMAND);
    }

        /* FIXME: Help */

        /* Run */
        if (SHRestricted(REST_NORUN))
        {
            DeleteMenu(hMenu,
                       IDM_RUN,
                       MF_BYCOMMAND);
        }

        /* Synchronize */
        if (!ShowSynchronizeMenuItem())
        {
            DeleteMenu(hMenu,
                       IDM_SYNCHRONIZE,
                       MF_BYCOMMAND);
            uLastItemsCount--;
        }

        /* Log off */
        if (dwLogoff != 1 && bWantLogoff)
        {
            /* FIXME: We need a more sophisticated way to determine whether to show
                      or hide it, it might be hidden in too many cases!!! */

            /* Update Log Off menu item */
            if (!GetCurrentLoggedOnUserName(szUser,
                sizeof(szUser) / sizeof(szUser[0])))
            {
                szUser[0] = _T('\0');
            }

            if (!FormatMenuString(hMenu,
                IDM_LOGOFF,
                MF_BYCOMMAND,
                szUser))
            {
                /* We couldn't update the menu item, delete it... */
                DeleteMenu(hMenu,
                           IDM_LOGOFF,
                           MF_BYCOMMAND);
            }
        }
        else
        {
            DeleteMenu(hMenu,
                       IDM_LOGOFF,
                       MF_BYCOMMAND);
            uLastItemsCount--;
        }


        /* Disconnect */
        if (GetSystemMetrics(SM_REMOTECONTROL) == 0)
        {
            DeleteMenu(hMenu,
                       IDM_DISCONNECT,
                       MF_BYCOMMAND);
            uLastItemsCount--;
        }

        /* Undock computer */
        if (!ShowUndockMenuItem())
        {
            DeleteMenu(hMenu,
                       IDM_UNDOCKCOMPUTER,
                       MF_BYCOMMAND);
            uLastItemsCount--;
        }

        /* Shut down */
        if (SHRestricted(REST_NOCLOSE))
        {
            DeleteMenu(hMenu,
                       IDM_SHUTDOWN,
                       MF_BYCOMMAND);
            uLastItemsCount--;
        }

        if (uLastItemsCount == 0)
        {
            /* Remove the separator at the end of the menu */
            DeleteMenu(hMenu,
                       IDM_LASTSTARTMENU_SEPARATOR,
                       MF_BYCOMMAND);
        }

        return S_OK;
    }