int WebEmberLinker::link(const char* prefix)
{
	assert(!mModuleHandle);
	std::string libdir(prefix);

#ifdef _WIN32
	if(!libdir.empty()) {
#if defined(_DEBUG) && defined(SEPARATE_BUILDS)
		//In msvc I prefer to separate release/debug builds to prevent mixing the runtime.
		//Set SEPARATE_BUILDS to enable this feature.
		libdir += "\\bin_d";
#else
		libdir += "\\bin";
#endif
		SetDllDirectoryA(libdir.c_str());
		SetCurrentDirectoryA(libdir.c_str());
		libdir += "\\";
	}

	//normally the browsers are disabling verbose popup messages from the OS on errors,
	//but to get more info on what is the missing DLL when linking recursively, we need to enable this.
	UINT browserErrorMode = GetErrorMode();
	SetErrorMode(0);
#else
	if (!libdir.empty()) {
		libdir += "/lib/";
	}
#endif

	std::string libfile(libdir + sLibName);
	FBLOG_INFO("WebEmberLinker::runEmber", "Loading library: " << libfile);
	//Loads the specified module into the address space of the calling process.
	mModuleHandle = LoadLib(libfile.c_str());
	if (mModuleHandle == NULL) {
#ifndef _WIN32
		FBLOG_ERROR("WebEmberLinker::runEmber", "dlerror: " << dlerror());
#endif
		FBLOG_ERROR("WebEmberLinker::runEmber", "Unable to load " << libfile);
		return 1;
	}
	
	//Retrieves the address of an exported function or variable from the specified DLL.
	pStartWebEmber = (funcTypeStart)GetFunction(mModuleHandle, sFuncNameStart);
	if (pStartWebEmber == NULL) {
#ifndef _WIN32
		FBLOG_ERROR("WebEmberLinker::runEmber", "dlerror: " << dlerror());
#endif
		FBLOG_ERROR("WebEmberLinker::runEmber", "Unable to load function " << sFuncNameStart << " in " << libfile);
		UnloadLib(mModuleHandle);
		return 2;
	}

	//same as above
	pQuitWebEmber = (funcTypeQuit)GetFunction(mModuleHandle, sFuncNameQuit);
	if (pQuitWebEmber == NULL) {
#ifndef _WIN32
		FBLOG_ERROR("WebEmberLinker::runEmber", "dlerror: " << dlerror());
#endif
		FBLOG_ERROR("WebEmberLinker::runEmber", "Unable to load function " << sFuncNameQuit << " in " << libfile);
		UnloadLib(mModuleHandle);
		return 3;
	}

#ifdef _WIN32
	//SetErrorMode of the process back to the original.
	SetErrorMode(browserErrorMode);
#endif
	return 0;
}