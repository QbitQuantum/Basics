Result<ExitCode> ProcessWithLogon::RunInternal(Trace& trace, const Settings& settings, ProcessTracker& processTracker, Environment& environment, bool changeIntegrityLevel) const
{
	SECURITY_ATTRIBUTES securityAttributes = {};
	securityAttributes.nLength = sizeof(SECURITY_DESCRIPTOR);
	securityAttributes.bInheritHandle = true;

	STARTUPINFO startupInfo = {};
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
	startupInfo.wShowWindow = ShowModeConverter::ToShowWindowFlag(settings.GetShowMode());	
	PROCESS_INFORMATION processInformation = {};

	trace < L"ProcessTracker::InitializeConsoleRedirection";
	processTracker.InitializeConsoleRedirection(securityAttributes, startupInfo);	

	StringBuffer userName(settings.GetUserName());
	StringBuffer domain(settings.GetDomain());
	StringBuffer password(settings.GetPassword());
	StringBuffer workingDirectory(settings.GetWorkingDirectory());
	StringBuffer commandLine(settings.GetCommandLine());

	if (changeIntegrityLevel)
	{
		trace < L"::LogonUser";
		auto newUserSecurityTokenHandle = Handle(L"New user security token");
		if (!LogonUser(
			userName.GetPointer(),
			domain.GetPointer(),
			password.GetPointer(),
			LOGON32_LOGON_BATCH,
			LOGON32_PROVIDER_DEFAULT,
			&newUserSecurityTokenHandle))
		{
			return Error(L"LogonUser");
		}

		trace < L"::LoadUserProfile";
		PROFILEINFO profileInfo = {};
		profileInfo.dwSize = sizeof(PROFILEINFO);
		profileInfo.lpUserName = userName.GetPointer();
		if (!LoadUserProfile(newUserSecurityTokenHandle, &profileInfo))
		{
			return Error(L"LoadUserProfile");
		}

		SecurityManager securityManager;
		auto setIntegrityLevelResult = securityManager.SetIntegrityLevel(settings.GetIntegrityLevel(), newUserSecurityTokenHandle, trace);
		if (setIntegrityLevelResult.HasError())
		{
			return Result<ExitCode>(setIntegrityLevelResult.GetError());
		}

		trace < L"::CreateProcessWithTokenW";		
		if (!CreateProcessWithTokenW(
			newUserSecurityTokenHandle,
			LOGON_WITH_PROFILE,
			nullptr,
			commandLine.GetPointer(),
			CREATE_UNICODE_ENVIRONMENT,
			environment.CreateEnvironment(),
			workingDirectory.GetPointer(),
			&startupInfo,
			&processInformation))
		{
			return Error(L"CreateProcessWithLogonW");
		}
	}
	else
	{
		trace < L"::CreateProcessWithLogonW";		
		if (!CreateProcessWithLogonW(
			userName.GetPointer(),
			domain.GetPointer(),
			password.GetPointer(),
			LOGON_WITH_PROFILE,
			nullptr,
			commandLine.GetPointer(),
			CREATE_UNICODE_ENVIRONMENT,
			environment.CreateEnvironment(),
			workingDirectory.GetPointer(),
			&startupInfo,
			&processInformation))
		{
			return Error(L"CreateProcessWithLogonW");
		}
	}

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto processHandle = Handle(L"Process");
	processHandle = processInformation.hProcess;

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto threadHandle = Handle(L"Thread");
	threadHandle = processInformation.hThread;

	return processTracker.WaiteForExit(processInformation.hProcess, trace);
}