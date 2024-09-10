FProcHandle FDesktopPlatformBase::InvokeUnrealBuildToolAsync(const FString& InCmdLineParams, FOutputDevice &Ar, void*& OutReadPipe, void*& OutWritePipe, bool bSkipBuildUBT)
{
	FString CmdLineParams = InCmdLineParams;

#if PLATFORM_WINDOWS
	#if _MSC_VER >= 1900
		CmdLineParams += TEXT(" -2015");
	#elif _MSC_VER >= 1800
		CmdLineParams += TEXT(" -2013");
	#else
		CmdLineParams += TEXT(" -2012");
	#endif
#endif // PLATFORM_WINDOWS

	// UnrealBuildTool is currently always located in the Binaries/DotNET folder
	FString ExecutableFileName = GetUnrealBuildToolExecutableFilename(FPaths::RootDir());

	// Rocket never builds UBT, UnrealBuildTool should already exist
	bool bSkipBuild = FApp::IsEngineInstalled() || bSkipBuildUBT;
	if (!bSkipBuild)
	{
		// When not using rocket, we should attempt to build UBT to make sure it is up to date
		// Only do this if we have not already successfully done it once during this session.
		static bool bSuccessfullyBuiltUBTOnce = false;
		if (!bSuccessfullyBuiltUBTOnce)
		{
			Ar.Log(TEXT("Building UnrealBuildTool..."));
			if (BuildUnrealBuildTool(FPaths::RootDir(), Ar))
			{
				bSuccessfullyBuiltUBTOnce = true;
			}
			else
			{
				// Failed to build UBT
				Ar.Log(TEXT("Failed to build UnrealBuildTool."));
				return FProcHandle();
			}
		}
	}

#if PLATFORM_LINUX
	CmdLineParams += (" -progress");
#endif // PLATFORM_LINUX

	Ar.Logf(TEXT("Launching UnrealBuildTool... [%s %s]"), *ExecutableFileName, *CmdLineParams);

#if PLATFORM_MAC
	// On Mac we launch UBT with Mono
	FString ScriptPath = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Build/BatchFiles/Mac/RunMono.sh"));
	CmdLineParams = FString::Printf(TEXT("\"%s\" \"%s\" %s"), *ScriptPath, *ExecutableFileName, *CmdLineParams);
	ExecutableFileName = TEXT("/bin/sh");
#elif PLATFORM_LINUX
	// Real men run Linux (with Mono??)
	FString ScriptPath = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Build/BatchFiles/Linux/RunMono.sh"));
	CmdLineParams = FString::Printf(TEXT("\"%s\" \"%s\" %s"), *ScriptPath, *ExecutableFileName, *CmdLineParams);
	ExecutableFileName = TEXT("/bin/bash");
#endif

	// Run UnrealBuildTool
	const bool bLaunchDetached = false;
	const bool bLaunchHidden = true;
	const bool bLaunchReallyHidden = bLaunchHidden;

	FProcHandle ProcHandle = FPlatformProcess::CreateProc(*ExecutableFileName, *CmdLineParams, bLaunchDetached, bLaunchHidden, bLaunchReallyHidden, NULL, 0, NULL, OutWritePipe);
	if (!ProcHandle.IsValid())
	{
		Ar.Logf(TEXT("Failed to launch Unreal Build Tool. (%s)"), *ExecutableFileName);
	}

	return ProcHandle;
}