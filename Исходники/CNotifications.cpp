// Update all notifications except those that RegistryNotifyWindow succeeded.
// Return TRUE if at least one has changed.
BOOL CNotifications::PollingUpdate()
{
	BOOL changed = FALSE;

	for (int i = 0; i < MAXDWORDNOTIFICATION; i++) {
		if (!dwHrNotify[i] || i == SN_POWERBATTERYSTATE) {
			DWORD value = 0;
			if (i == SN_POWERBATTERYSTATE) {
				SYSTEM_POWER_STATUS_EX pwrStatus;
				if (GetSystemPowerStatusEx(&pwrStatus, TRUE)) {
					value = pwrStatus.BatteryLifePercent << 16;
					value |= pwrStatus.BatteryFlag;
				} else {
					value = BATTERY_PERCENTAGE_UNKNOWN << 16;
				}
			} else if (i == SN_VOLUME) {
				waveOutGetVolume(0, &value);
			} else {
				LoadDwordSetting(SN_DW[i].hKey, &value, SN_DW[i].pszSubKey, SN_DW[i].pszValueName, 0);
			}
			if (dwNotifications[i] != value) {
				dwNotifications[i] = value;
				dwNotificationsChanged[i] = TRUE;
				changed = TRUE;
			} else {
				dwNotificationsChanged[i] = FALSE;
			}
		}
	}

	for (int i = 0; i < MAXSTRINGNOTIFICATION; i++) {
		TCHAR value[MAX_PATH];
		if (!szHrNotify[i]) {
			LoadTextSetting(SN_SZ[i].hKey, value, SN_SZ[i].pszSubKey, SN_SZ[i].pszValueName, L"");
			if (lstrcmp(szNotifications[i], value) != 0) {
				wcscpy(szNotifications[i], value);
				szNotificationsChanged[i] = TRUE;
				changed = TRUE;
			} else {
				szNotificationsChanged[i] = FALSE;
			}
		}
	}

	//if (!ftHrNotify[SN_TIME] || !ftHrNotify[SN_DATE]) {
		SYSTEMTIME st_new;
		GetLocalTime(&st_new);
		if (st.wMinute != st_new.wMinute || st.wHour != st_new.wHour) {
			ftNotificationsChanged[SN_TIME] = TRUE;
			changed = TRUE;
		} else {
			ftNotificationsChanged[SN_TIME] = FALSE;
		}
		if (st.wDay != st_new.wDay || st.wDayOfWeek != st_new.wDayOfWeek) {
			ftNotificationsChanged[SN_DATE] = TRUE;
			changed = TRUE;
		} else {
			ftNotificationsChanged[SN_DATE] = FALSE;
		}
		memcpy(&st, &st_new, sizeof(SYSTEMTIME));
	//}

	if (!ftHrNotify[SN_ALARMS_NEXT]) {
		FILETIME ftAlarmsNext_new;
		LoadDateTimeSetting(SN_FT[SN_ALARMS_NEXT].hKey, &ftAlarmsNext_new, SN_FT[SN_ALARMS_NEXT].pszSubKey, SN_FT[SN_ALARMS_NEXT].pszValueName);
		if (CompareFileTime(&ftAlarmsNext_new , &ftAlarmsNext) != 0) {
			memcpy(&ftAlarmsNext, &ftAlarmsNext_new, sizeof(FILETIME));
			ftNotificationsChanged[SN_ALARMS_NEXT] = TRUE;
			changed = TRUE;
		} else {
			ftNotificationsChanged[SN_ALARMS_NEXT] = FALSE;
		}
	}

	int wss = GetWifiSignalStrength();
	if (wss != wifiSignalStrength) {
		wifiSignalStrength = wss;
		wifiSignalStrength_changed = TRUE;
	} else {
		wifiSignalStrength_changed = FALSE;
	}

	MEMORYSTATUS mems;
	mems.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&mems);
	if (mems.dwMemoryLoad != memoryStatus.dwMemoryLoad) {
		memory_changed = TRUE;
		changed = TRUE;
	} else {
		memory_changed = FALSE;
	}
	memcpy(&memoryStatus, &mems, sizeof(MEMORYSTATUS));

	return changed;
}