shared_ptr<rett> createAny(const boost::filesystem::path& libpath, const std::string& methodName)
{
	typedef void(*TGetAIFun)(shared_ptr<rett>&); 
	typedef void(*TGetNameFun)(char*); 

	char temp[150];

	TGetAIFun getAI = nullptr;
	TGetNameFun getName = nullptr;

#ifdef VCMI_ANDROID
	// this is awful but it seems using shared libraries on some devices is even worse
	const std::string filename = libpath.filename().string();
	if (filename == "libVCAI.so")
	{
		getName = (TGetNameFun)VCAI_GetAiName;
		getAI = (TGetAIFun)VCAI_GetNewAI;
	}
	else if (filename == "libStupidAI.so")
	{
		getName = (TGetNameFun)StupidAI_GetAiName;
		getAI = (TGetAIFun)StupidAI_GetNewBattleAI;
	}
	else if (filename == "libBattleAI.so")
	{
		getName = (TGetNameFun)BattleAI_GetAiName;
		getAI = (TGetAIFun)BattleAI_GetNewBattleAI;
	}
	else
		throw std::runtime_error("Don't know what to do with " + libpath.string() + " and method " + methodName);
#else // !VCMI_ANDROID
#ifdef VCMI_WINDOWS
	HMODULE dll = LoadLibraryW(libpath.c_str());
	if (dll)
	{
		getName = (TGetNameFun)GetProcAddress(dll, "GetAiName");
		getAI = (TGetAIFun)GetProcAddress(dll, methodName.c_str());
	}
#else // !VCMI_WINDOWS
	void *dll = dlopen(libpath.string().c_str(), RTLD_LOCAL | RTLD_LAZY);
	if (dll)
	{
		getName = (TGetNameFun)dlsym(dll, "GetAiName");
		getAI = (TGetAIFun)dlsym(dll, methodName.c_str());
	}
	else
        logGlobal->errorStream() << "Error: " << dlerror();
#endif // VCMI_WINDOWS
	if (!dll)
	{
		logGlobal->errorStream() << "Cannot open dynamic library ("<<libpath<<"). Throwing...";
		throw std::runtime_error("Cannot open dynamic library");
	}
	else if(!getName || !getAI)
	{
		logGlobal->errorStream() << libpath << " does not export method " << methodName;
#ifdef VCMI_WINDOWS
		FreeLibrary(dll);
#else
		dlclose(dll);
#endif
		throw std::runtime_error("Cannot find method " + methodName);
	}
#endif // VCMI_ANDROID

	getName(temp);
    logGlobal->infoStream() << "Loaded " << temp;

	shared_ptr<rett> ret;
	getAI(ret);
	if(!ret)
        logGlobal->errorStream() << "Cannot get AI!";

	return ret;
}