HBITMAP ToolbarGetImage(
    _In_ INT CommandID
    )
{
    static INT cx = 0;
    static INT cy = 0;

    if (!cx)
    {
        cx = GetSystemMetrics(SM_CXSMICON);
    }

    if (!cy)
    {
        cy = GetSystemMetrics(SM_CYSMICON);
    }

    switch (CommandID)
    {
    case PHAPP_ID_VIEW_REFRESH:
        {
            HBITMAP toolbarBitmap = NULL;

            if (ToolStatusConfig.ModernIcons)
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_ARROW_REFRESH_MODERN));
            }
            else
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_ARROW_REFRESH));
            }

            if (!toolbarBitmap)
            {
                toolbarBitmap = LoadImage(
                    PluginInstance->DllBase,
                    MAKEINTRESOURCE(IDB_ARROW_REFRESH_BMP),
                    IMAGE_BITMAP,
                    0, 0, 0
                    );
            }

            return toolbarBitmap;
        }
        break;
    case PHAPP_ID_HACKER_OPTIONS:
        {
            HBITMAP toolbarBitmap = NULL;

            if (ToolStatusConfig.ModernIcons)
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_COG_EDIT_MODERN));
            }
            else
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_COG_EDIT));
            }

            if (!toolbarBitmap)
            {
                toolbarBitmap = LoadImage(
                    PluginInstance->DllBase,
                    MAKEINTRESOURCE(IDB_COG_EDIT_BMP),
                    IMAGE_BITMAP,
                    0, 0, 0
                    );
            }

            return toolbarBitmap;
        }
        break;
    case PHAPP_ID_HACKER_FINDHANDLESORDLLS:
        {
            HBITMAP toolbarBitmap = NULL;

            if (ToolStatusConfig.ModernIcons)
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_FIND_MODERN));
            }
            else
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_FIND));
            }

            if (!toolbarBitmap)
            {
                toolbarBitmap = LoadImage(
                    PluginInstance->DllBase,
                    MAKEINTRESOURCE(IDB_FIND_BMP),
                    IMAGE_BITMAP,
                    0, 0, 0
                    );
            }

            return toolbarBitmap;
        }
        break;
    case PHAPP_ID_VIEW_SYSTEMINFORMATION:
        {
            HBITMAP toolbarBitmap = NULL;

            if (ToolStatusConfig.ModernIcons)
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_CHART_LINE_MODERN));
            }
            else
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_CHART_LINE));
            }

            if (!toolbarBitmap)
            {
                toolbarBitmap = LoadImage(
                    PluginInstance->DllBase,
                    MAKEINTRESOURCE(IDB_CHART_LINE_BMP),
                    IMAGE_BITMAP,
                    0, 0, 0
                    );
            }

            return toolbarBitmap;
        }
        break;
    case TIDC_FINDWINDOW:
        {
            HBITMAP toolbarBitmap = NULL;

            if (ToolStatusConfig.ModernIcons)
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_APPLICATION_MODERN));
            }
            else
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_APPLICATION));
            }

            if (!toolbarBitmap)
            {
                toolbarBitmap = LoadImage(
                    PluginInstance->DllBase,
                    MAKEINTRESOURCE(IDB_APPLICATION_BMP),
                    IMAGE_BITMAP,
                    0, 0, 0
                    );
            }

            return toolbarBitmap;
        }
        break;
    case TIDC_FINDWINDOWTHREAD:
        {
            HBITMAP toolbarBitmap = NULL;

            if (ToolStatusConfig.ModernIcons)
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_APPLICATION_GO_MODERN));
            }
            else
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_APPLICATION_GO));
            }

            if (!toolbarBitmap)
            {
                toolbarBitmap = LoadImage(
                    PluginInstance->DllBase,
                    MAKEINTRESOURCE(IDB_APPLICATION_GO_BMP),
                    IMAGE_BITMAP,
                    0, 0, 0
                    );
            }

            return toolbarBitmap;
        }
        break;
    case TIDC_FINDWINDOWKILL:
        {
            HBITMAP toolbarBitmap = NULL;

            if (ToolStatusConfig.ModernIcons)
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_CROSS_MODERN));
            }
            else
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_CROSS));
            }

            if (!toolbarBitmap)
            {
                toolbarBitmap = LoadImage(
                    PluginInstance->DllBase,
                    MAKEINTRESOURCE(IDB_CROSS_BMP),
                    IMAGE_BITMAP,
                    0, 0, 0
                    );
            }

            return toolbarBitmap;
        }
        break;
    case PHAPP_ID_VIEW_ALWAYSONTOP:
        {
            HBITMAP toolbarBitmap = NULL;

            if (ToolStatusConfig.ModernIcons)
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_APPLICATION_GET_MODERN));
            }
            else
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_APPLICATION_GET));
            }

            if (!toolbarBitmap)
            {
                toolbarBitmap = LoadImage(
                    PluginInstance->DllBase,
                    MAKEINTRESOURCE(IDB_APPLICATION_GET_BMP),
                    IMAGE_BITMAP,
                    0, 0, 0
                    );
            }

            return toolbarBitmap;
        }
        break;
    case TIDC_POWERMENUDROPDOWN:
        {
            HBITMAP toolbarBitmap = NULL;

            if (ToolStatusConfig.ModernIcons)
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_POWER_MODERN));
            }
            else
            {
                toolbarBitmap = LoadImageFromResources(cx, cy, MAKEINTRESOURCE(IDB_POWER));
            }

            if (!toolbarBitmap)
            {
                toolbarBitmap = LoadImage(
                    PluginInstance->DllBase,
                    MAKEINTRESOURCE(IDB_POWER_BMP),
                    IMAGE_BITMAP,
                    0, 0, 0
                    );
            }

            return toolbarBitmap;
        }
        break;
    case PHAPP_ID_HACKER_SHOWDETAILSFORALLPROCESSES:
        {
            HBITMAP toolbarBitmap = NULL;
            HICON shieldIcon = NULL;
            _LoadIconMetric loadIconMetric = NULL;

            // It is necessary to use LoadIconMetric because otherwise the icons are at the wrong
            // resolution and look very bad when scaled down to the small icon size.
            loadIconMetric = (_LoadIconMetric)PhGetModuleProcAddress(L"comctl32.dll", "LoadIconMetric");

            if (loadIconMetric && SUCCEEDED(loadIconMetric(NULL, IDI_SHIELD, LIM_SMALL, &shieldIcon)))
            {
                toolbarBitmap = PhIconToBitmap(
                    shieldIcon,
                    cx,
                    cy
                    );

                DestroyIcon(shieldIcon);
            }

            return toolbarBitmap;
        }
        break;
    }

    return NULL;
}