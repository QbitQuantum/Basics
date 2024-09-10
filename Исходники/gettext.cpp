void init_gettext(const char *path, const std::string &configured_language, int argc, char** argv) {
#else
void init_gettext(const char *path, const std::string &configured_language) {
#endif
#if USE_GETTEXT
	/** first try to set user override environment **/
	if (configured_language.length() != 0) {
#ifndef _WIN32
		/* add user specified locale to environment */
		setenv("LANGUAGE", configured_language.c_str(), 1);

		/* reload locale with changed environment */
		setlocale(LC_ALL, "");
#elif defined(_MSC_VER)
		std::string current_language_var("");
		if (getenv("LANGUAGE") != 0) {
			current_language_var = std::string(getenv("LANGUAGE"));
		}

		char *lang_str = (char*)calloc(10 + configured_language.length(), sizeof(char));
		strcat(lang_str, "LANGUAGE=");
		strcat(lang_str, configured_language.c_str());
		putenv(lang_str);

		SetEnvironmentVariableA("LANGUAGE",configured_language.c_str());

#ifndef SERVER
		//very very dirty workaround to force gettext to see the right environment
		if (current_language_var != configured_language) {
			STARTUPINFO startupinfo;
			PROCESS_INFORMATION processinfo;
			memset(&startupinfo, 0, sizeof(startupinfo));
			memset(&processinfo, 0, sizeof(processinfo));
			errorstream << "MSVC localization workaround active restating minetest in new environment!" << std::endl;

			std::string parameters = "";

			for (unsigned int i=1;i < argc; i++) {
				if (parameters != "") {
					parameters += " ";
				}
				parameters += argv[i];
			}

			const char* ptr_parameters = 0;

			if (parameters != "") {
				ptr_parameters = parameters.c_str();
			}
			
			/** users may start by short name in commandline without extention **/
			std::string appname = argv[0];
			if (appname.substr(appname.length() - 4) != ".exe") {
				appname += ".exe";
			}

			if (!CreateProcess(appname.c_str(),
					(char*) ptr_parameters,
					NULL,
					NULL,
					false,
					DETACHED_PROCESS | CREATE_UNICODE_ENVIRONMENT,
					NULL,
					NULL,
					&startupinfo,
					&processinfo)) {
				char buffer[1024];		
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					GetLastError(),
					MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
					buffer,
					sizeof(buffer)-1,
					NULL);
				errorstream << "*******************************************************" << std::endl;
				errorstream << "CMD: " << appname << std::endl;
				errorstream << "Failed to restart with current locale: " << std::endl;
				errorstream << buffer;
				errorstream << "Expect language to be broken!" << std::endl;
				errorstream << "*******************************************************" << std::endl;
			}
			else {
				exit(0);
			}
#else
			errorstream << "*******************************************************" << std::endl;
			errorstream << "Can't apply locale workaround for server!" << std::endl;
			errorstream << "Expect language to be broken!" << std::endl;
			errorstream << "*******************************************************" << std::endl;

#endif
		}

		setlocale(LC_ALL,configured_language.c_str());
#else // Mingw
		char *lang_str = (char*)calloc(10 + configured_language.length(), sizeof(char));
		strcat(lang_str, "LANGUAGE=");
		strcat(lang_str, configured_language.c_str());
		putenv(lang_str);

		setlocale(LC_ALL, "");
#endif // ifndef _WIN32
	}
	else {
		 /* set current system default locale */
		setlocale(LC_ALL, "");
	}

#if defined(_WIN32)
	if (getenv("LANGUAGE") != 0) {
		setlocale(LC_ALL, getenv("LANGUAGE"));
	}
#ifdef _MSC_VER
	else if (getenv("LANG") != 0) {
		setlocale(LC_ALL, getenv("LANG"));
	}
#endif
#endif

	static std::string name = lowercase(PROJECT_NAME);
	bindtextdomain(name.c_str(), path);
	textdomain(name.c_str());

#if defined(_WIN32)
	// Set character encoding for Win32
	char *tdomain = textdomain( (char *) NULL );
	if( tdomain == NULL )
	{
		errorstream << "Warning: domainname parameter is the null pointer" <<
				", default domain is not set" << std::endl;
		tdomain = (char *) "messages";
	}
	/* char *codeset = */bind_textdomain_codeset( tdomain, "UTF-8" );
	//errorstream << "Gettext debug: domainname = " << tdomain << "; codeset = "<< codeset << std::endl;
#endif // defined(_WIN32)

#else
	/* set current system default locale */
	setlocale(LC_ALL, "");
#endif // if USE_GETTEXT

	/* no matter what locale is used we need number format to be "C" */
	/* to ensure formspec parameters are evaluated correct!          */

	setlocale(LC_NUMERIC, "C");
	infostream << "Message locale is now set to: "
			<< setlocale(LC_ALL, 0) << std::endl;
}