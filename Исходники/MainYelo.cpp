		static Enums::version_result_code GetVersionResultCode()
		{
			Enums::version_result_code result_code = Enums::_version_result_code_invalid;

			char dir[MAX_PATH];
			GetCurrentDirectory(NUMBEROF(dir), dir);

			char name[64];
			GetModuleBaseName(GetCurrentProcess(), GetModuleHandle(nullptr), name, NUMBEROF(name));
			_strlwr_s(name);

			// Ok, the warning message will get annoying after a while for sapien (and tool) users
			if ( strstr(name,"sapien") != nullptr || strstr(name,"hobo") != nullptr || 
				 strstr(name,"tool") != nullptr )
				return Enums::_version_result_code_dx9_app;

			// Enable OS if the exe name is haloce/OS_ded
			_main_globals.enabled = (strcmp(name, PLATFORM_VALUE("haloce.exe","os_haloceded.exe")) == 0);

			return Enums::_version_result_code_valid;
		}