static void loadGeneralParams(LPCWSTR path) {
	GeneralParams.HookTarget = (HookTargetEnum)GetPrivateProfileIntW(
		L"General",
		L"HookTarget",
		(int)GeneralParams.HookTarget,
		path);
	GeneralParams.ForceNoHinting = 0 != GetPrivateProfileIntW(
		L"General",
		L"ForceNoHinting",
		(int)GeneralParams.ForceNoHinting,
		path);
	
	wchar_t exePath[_MAX_PATH];
	GetModuleFileNameW(NULL, exePath, _MAX_PATH);
	wchar_t* exeName = PathFindFileNameW(exePath);
	CharLower(exeName);
	
	switch (GeneralParams.HookTarget) {
		case HookTargetEnum::All:
			GeneralParams.isHookTarget = true;
			break;
		case HookTargetEnum::ExcludeMode: {
			std::set<std::wstring, std::less<>> set;
			loadExeName(set, L"Exclude", path);
			GeneralParams.isHookTarget = set.count(exeName) == 0;
			break;
		}
		case HookTargetEnum::IncludeMode: {
			std::set<std::wstring, std::less<>> set;
			loadExeName(set, L"Include", path);
			GeneralParams.isHookTarget = set.count(exeName) > 0;
			break;
		}
		case HookTargetEnum::None:
			GeneralParams.isHookTarget = false;
			break;
	}
}