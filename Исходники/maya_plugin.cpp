MStatus initializeMayaPlugin(MObject obj)
{
	MStatus status;

	if (!Environment::getValue<MAX_PATH>(WGT_HOME, wgtHome))
	{
#ifdef _WIN32
		GetModuleFileNameA(hApp, wgtHome, MAX_PATH);
		PathRemoveFileSpecA(wgtHome);
		Environment::setValue(WGT_HOME, wgtHome);
#endif // _WIN32

#ifdef __APPLE__
		Dl_info info;
		if (!dladdr(reinterpret_cast<void*>(setContext), &info))
		{
			WGT_ERROR_MSG("Generic plugin manager: failed to get current module file name%s", "\n");
		}
		strcpy(wgtHome, info.dli_fname);
		const char* dir = dirname(wgtHome);
		Environment::setValue(WGT_HOME, dir);

		std::string dlybs = dir;
		dlybs += "/../PlugIns";
		Environment::setValue("LD_LIBRARY_PATH", dlybs.c_str());
#endif // __APPLE__
	}

	Environment::setValue("QTWEBENGINEPROCESS_PATH", wgtHome);

#ifdef __APPLE__
	Environment::setValue("QT_QPA_PLATFORM_PLUGIN_PATH", (std::string(wgtHome) + "/../PlugIns/platforms").c_str());
#else
	Environment::setValue("QT_QPA_PLATFORM_PLUGIN_PATH", (std::string(wgtHome) + "/platforms").c_str());
#endif

#ifdef _WIN32
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, exePath, MAX_PATH, wgtHome, _TRUNCATE);
	assert(convertedChars);
#endif // _WIN32

#ifdef __APPLE__
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	wcscpy(exePath, conv.from_bytes(wgtHome).c_str());
#endif // __APPLE__

	QDir::setCurrent(wgtHome);

	char path[2048];
	if (Environment::getValue<2048>(WGT_PATH, path))
	{
		std::string newPath("\"");
		newPath += wgtHome;
		newPath += "\";";
		newPath += path;
		Environment::setValue(WGT_PATH, newPath.c_str());
	}

#ifdef _WIN32
	SetDllDirectoryA(wgtHome);
#endif // _WIN32

	pluginManager = new GenericPluginManager();

	WGTShowCommand::registerCommand(obj);
	WGTHideCommand::registerCommand(obj);
	WGTStartCommand::registerCommand(obj);
	WGTStopCommand::registerCommand(obj);

	return loadWGT() ? MStatus::kSuccess : MStatus::kFailure;
}