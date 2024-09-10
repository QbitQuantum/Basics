	virtual VoidFunc findSymbol(const char *symbol) {
		#ifndef _WIN32_WCE
		FARPROC func = GetProcAddress((HMODULE)_dlHandle, symbol);
		#else
		FARPROC func = GetProcAddress((HMODULE)_dlHandle, toUnicode(symbol));
		#endif
		if (!func)
			debug("Failed loading symbol '%s' from plugin '%s'", symbol, _filename.c_str());

		return (void (*)())func;
	}