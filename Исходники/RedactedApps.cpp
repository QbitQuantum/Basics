uint32_t RedactedApps::GetDLCCount()
{
	PrintCurrentFunction();

#ifdef NO_PIRACY
	return SteamProxy::GetDLCCount();
#else
	return GetPrivateProfileIntA("DLC", "DLCCount", 0, hString::va("%s.ini", Global::Game_BinaryName));
#endif
}