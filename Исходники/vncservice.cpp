BOOL CALLBACK WinStationEnumProc(LPTSTR name, LPARAM param) {
	HWINSTA station = OpenWindowStation(name, FALSE, GENERIC_ALL);
	HWINSTA oldstation = GetProcessWindowStation();
	USEROBJECTFLAGS flags;
	if (!GetUserObjectInformation(station, UOI_FLAGS, &flags, sizeof(flags), NULL)) {
		return TRUE;
	}
	BOOL visible = flags.dwFlags & WSF_VISIBLE;
	if (visible) {
		if (SetProcessWindowStation(station)) {
			if (oldstation != home_window_station) {
				CloseWindowStation(oldstation);
			}
		} else {
			CloseWindowStation(station);
		}
		return FALSE;
	}
	return TRUE;
}