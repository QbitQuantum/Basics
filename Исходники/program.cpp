Program::Program()
{
	wchar_t savePathBuffer[MAX_PATH];
	if (SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, savePathBuffer) >= 0)
	{
		PathAppendW(savePathBuffer, L"\\SA-MP Audio Plugin");
		if (!boost::filesystem::exists(savePathBuffer))
		{
			boost::filesystem::create_directories(savePathBuffer);
		}
		savePath = savePathBuffer;
	}
	else
	{
		savePath = L".";
	}
	const char *defaultAcceptedFileExtensions[] =
	{
		".afc",
		".aif",
		".aifc",
		".aiff",
		".it",
		".mo3",
		".mod",
		".mp1",
		".mp2",
		".mp3",
		".mtm",
		".oga",
		".ogg",
		".s3m",
		".umx",
		".wav",
		".wave",
		".xm"
	};
	for (std::size_t i = 0; i < sizeof(defaultAcceptedFileExtensions) / sizeof(const char*); ++i)
	{
		acceptedFileExtensions.insert(defaultAcceptedFileExtensions[i]);
	}
	const char *defaultIllegalCharacters[] =
	{
		"\"",
		"*",
		"..",
		"/",
		":",
		"<",
		">",
		"?",
		"\\",
		"|"
	};
	for (std::size_t i = 0; i < sizeof(defaultIllegalCharacters) / sizeof(const char*); ++i)
	{
		illegalCharacters.insert(defaultIllegalCharacters[i]);
	}
	settings.reset(new Settings);
	loadSettings();
	logText("SA-MP Audio Plugin loaded");
}