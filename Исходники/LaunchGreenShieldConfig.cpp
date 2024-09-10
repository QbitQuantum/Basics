bool LaunchGreenShieldConfig::CheckEnableLaunchNow()
{
	assert(this->Valid());
	if(!this->Valid()) {
		return false;
	}
	if(!this->UpdateConfig()) {
		return false;
	}
	if(!this->IsEnableLaunchNow()) {
		return false;
	}

	wchar_t configFilePath[MAX_PATH];
	if(!this->GetConfigFilePath(configFilePath, MAX_PATH)) {
		return false;
	}
	const wchar_t* szSectionName = L"pusher";

	__time64_t nLastLaunchTime = this->GetLastPull();
	__time64_t nCurrentTime = 0;
	_time64(&nCurrentTime);
	const tm* curentTime = _gmtime64(&nCurrentTime);
	int cur_year = curentTime->tm_year;
	int cur_yday = curentTime->tm_yday;
	const tm* lastLaunchTime = _gmtime64(&nLastLaunchTime);
	if(cur_year != lastLaunchTime->tm_year || cur_yday != lastLaunchTime->tm_yday) {
		this->m_Cnt = 1;
	}
	else {
		++this->m_Cnt;
	}
	std::wstring cntStr;
	{
		std::wstringstream wss;
		wss << this->m_Cnt;
		wss >> cntStr;
	}
	if(!::WritePrivateProfileString(szSectionName, L"cnt", cntStr.c_str(), configFilePath)) {
		return false;
	}

	this->m_LastPull = nCurrentTime;
	std::wstring lastPullStr;
	{
		std::wstringstream wss;
		wss << this->m_LastPull;
		wss >> lastPullStr;
	}
	if(!::WritePrivateProfileString(szSectionName, L"lastpull", lastPullStr.c_str(), configFilePath)) {
		return false;
	}
	return true;
}