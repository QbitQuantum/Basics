int TrayCalcChanged(const char *szChangedProto, int averageMode, int netProtoCount)
{
	HICON hIcon;
	int iIcon;
	HWND hwnd = pcli->hwndContactList;

	if (netProtoCount > 1) {
		if (averageMode > 0) {
			if (cfg::getByte("CList", "TrayIcon", SETTING_TRAYICON_DEFAULT) == SETTING_TRAYICON_MULTI) {
				if (cfg::getByte("CList", "AlwaysMulti", SETTING_ALWAYSMULTI_DEFAULT)) {
					iIcon = IconFromStatusMode(szChangedProto, averageMode, 0, &hIcon);
					hIcon = (hIcon) ? CopyIcon(hIcon) : ImageList_GetIcon(hCListImages, iIcon, ILD_NORMAL);
					return pcli->pfnTrayIconSetBaseInfo(hIcon, szChangedProto);
				}
				if (pcli->trayIcon == NULL || pcli->trayIcon[0].szProto == NULL) {
					iIcon = IconFromStatusMode(NULL, averageMode, 0, &hIcon);
					hIcon = (hIcon) ? CopyIcon(hIcon) : ImageList_GetIcon(hCListImages, iIcon, ILD_NORMAL);
					return pcli->pfnTrayIconSetBaseInfo(hIcon, NULL);
				}
				pcli->pfnTrayIconDestroy(hwnd);
				pcli->pfnTrayIconInit(hwnd);
			}
			else {
				iIcon = IconFromStatusMode(NULL, averageMode, 0, &hIcon);
				hIcon = (hIcon) ? CopyIcon(hIcon) : ImageList_GetIcon(hCListImages, iIcon, ILD_NORMAL);
				return pcli->pfnTrayIconSetBaseInfo(hIcon, NULL);
			}
		}
		else {
			switch (cfg::getByte("CList", "TrayIcon", SETTING_TRAYICON_DEFAULT)) {
			case SETTING_TRAYICON_CYCLE:
				iIcon = IconFromStatusMode(szChangedProto, CallProtoService(szChangedProto, PS_GETSTATUS, 0, 0), 0, &hIcon);
				pcli->cycleTimerId = SetTimer(NULL, 0, cfg::getWord("CList", "CycleTime", SETTING_CYCLETIME_DEFAULT) * 1000, pcli->pfnTrayCycleTimerProc);
				hIcon = (hIcon) ? CopyIcon(hIcon) : ImageList_GetIcon(hCListImages, iIcon, ILD_NORMAL);
				return pcli->pfnTrayIconSetBaseInfo(hIcon, NULL);

			case SETTING_TRAYICON_MULTI:
				if (!pcli->trayIcon)
					pcli->pfnTrayIconRemove(NULL, NULL);
				else if (cfg::getByte("CList", "AlwaysMulti", SETTING_ALWAYSMULTI_DEFAULT)) {
					iIcon = IconFromStatusMode(szChangedProto, CallProtoService(szChangedProto, PS_GETSTATUS, 0, 0), 0, &hIcon);
					hIcon = (hIcon) ? CopyIcon(hIcon) : ImageList_GetIcon(hCListImages, iIcon, ILD_NORMAL);
					return pcli->pfnTrayIconSetBaseInfo(hIcon, szChangedProto);
				}
				pcli->pfnTrayIconDestroy(hwnd);
				pcli->pfnTrayIconInit(hwnd);
				break;

			case SETTING_TRAYICON_SINGLE:
				ptrA szProto( db_get_sa(NULL, "CList", "PrimaryStatus"));
				iIcon = IconFromStatusMode(szProto, szProto ? CallProtoService(szProto, PS_GETSTATUS, 0, 0) : CallService(MS_CLIST_GETSTATUSMODE, 0, 0), 0, &hIcon);
				hIcon = (hIcon) ? CopyIcon(hIcon) : ImageList_GetIcon(hCListImages, iIcon, ILD_NORMAL);
				return pcli->pfnTrayIconSetBaseInfo(hIcon, NULL);
			}
		}
	}
	else {
		iIcon = IconFromStatusMode(NULL, averageMode, 0, &hIcon);
		hIcon = (hIcon) ? CopyIcon(hIcon) : ImageList_GetIcon(hCListImages, iIcon, ILD_NORMAL);
		return pcli->pfnTrayIconSetBaseInfo(hIcon, NULL);
	}

	return -1;
}