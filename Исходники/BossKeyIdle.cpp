static bool IsUserIdle()
{
	DWORD dwTick;
	if (g_wMaskAdv & OPT_HIDEIFMIRIDLE) {
		CallService(MS_SYSTEM_GETIDLE, 0, (LPARAM)&dwTick);
		return GetTickCount() - dwTick > (minutes * 60 * 1000);
	}

	LASTINPUTINFO ii = { sizeof(ii) };
	if (GetLastInputInfo(&ii))
		return GetTickCount() - ii.dwTime > (minutes * 60 * 1000);

	return FALSE;
}