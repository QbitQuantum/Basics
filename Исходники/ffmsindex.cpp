int main() {
	int argc;
	wchar_t **_argv;
	wchar_t **env;
	int si = 0;
	__wgetmainargs(&argc, &_argv, &env, _CRT_glob, &si);
#else
int wmain(int argc, wchar_t *_argv[]) {
#endif
	char **argv = (char**)malloc(argc*sizeof(char*));
	for (int i=0; i<argc; i++) {
		int len = WideCharToMultiByte(CP_UTF8, 0, _argv[i], -1, NULL, 0, NULL, NULL);
		if (!len) {
			std::cout << "Failed to translate commandline to Unicode" << std::endl;
			return 1;
		}
		char *temp = (char*)malloc(len*sizeof(char));
		len = WideCharToMultiByte(CP_UTF8, 0, _argv[i], -1, temp, len, NULL, NULL);
		if (!len) {
			std::cout << "Failed to translate commandline to Unicode" << std::endl;
			return 1;
		}
		argv[i] = temp;
	}
#else /* defined(_WIN32) && !defined(__MINGW32__) */
int main(int argc, char *argv[]) {
#endif /* defined(_WIN32) && !defined(__MINGW32__) */
	try {
		ParseCMDLine(argc, argv);
	} catch (const char *Error) {
		std::cout << std::endl << Error << std::endl;
		return 1;
	} catch (std::string Error) {
		std::cout << std::endl << Error << std::endl;
		return 1;
	} catch (...) {
		std::cout << std::endl << "Unknown error" << std::endl;
		return 1;
	}

#ifdef _WIN32
	if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED))) {
		std::cout << "COM initialization failure" << std::endl;
		return 1;
	}
#endif /* _WIN32 */

	FFMS_Init(0, 1);

	switch (Verbose) {
		case 0: FFMS_SetLogLevel(AV_LOG_QUIET); break;
		case 1: FFMS_SetLogLevel(AV_LOG_WARNING); break;
		case 2: FFMS_SetLogLevel(AV_LOG_INFO); break;
		case 3:	FFMS_SetLogLevel(AV_LOG_VERBOSE); break;
		default: FFMS_SetLogLevel(AV_LOG_DEBUG); // if user used -v 4 or more times, he deserves the spam
	}

	try {
		DoIndexing();
	} catch (const char *Error) {
		std::cout << Error << std::endl;
		if (Index)
			FFMS_DestroyIndex(Index);
		return 1;
	} catch (std::string Error) {
		std::cout << std::endl << Error << std::endl;
		if (Index)
			FFMS_DestroyIndex(Index);
		return 1;
	} catch (...) {
		std::cout << std::endl << "Unknown error" << std::endl;
		if (Index)
			FFMS_DestroyIndex(Index);
		return 1;
	}

	if (Index)
		FFMS_DestroyIndex(Index);
#ifdef _WIN32
	CoUninitialize();
#endif
	return 0;
}