int WindowsIdleQuerier::getIdleTimeSeconds() {
	LASTINPUTINFO info;
	info.cbSize = sizeof(info);
	if (GetLastInputInfo(&info)) {
		return (GetTickCount() - info.dwTime) / 1000;
	}
	else {
		return 0;
	}
}