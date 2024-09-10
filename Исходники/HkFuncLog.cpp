bool HkAddConnectLog(uint iClientID, wstring wscReason, ...)
{
	wchar_t wszBuf[1024*8] = L"";
	va_list marker;
	va_start(marker, wscReason);

	_vsnwprintf(wszBuf, (sizeof(wszBuf) / 2) - 1, wscReason.c_str(), marker);

	FILE *f = fopen(("./flhook_logs/flhook_connects.log"), "at");
	if(!f)
		return false;

	const wchar_t *wszCharname = (wchar_t*)Players.GetActiveCharacterName(iClientID);
	if(!wszCharname)
		wszCharname = L"";

	CAccount *acc = Players.FindAccountFromClientID(iClientID);
	wstring wscAccountDir;
	HkGetAccountDirName(acc, wscAccountDir);

	time_t tNow = time(0);
	struct tm *stNow = localtime(&tNow);
	fprintf(f, "%.2d/%.2d/%.4d %.2d:%.2d:%.2d Connect (%s): %s(%s)(%s)\n", stNow->tm_mon + 1, stNow->tm_mday, stNow->tm_year + 1900, stNow->tm_hour, stNow->tm_min, stNow->tm_sec, wstos(wszBuf).c_str(), wstos(wszCharname).c_str(), wstos(wscAccountDir).c_str(), wstos(HkGetAccountID(acc)).c_str());
	fclose(f);
	return true;
}