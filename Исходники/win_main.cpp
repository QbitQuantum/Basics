void Sys_Init( void ) {

	CoInitialize( NULL );

	// make sure the timer is high precision, otherwise
	// NT gets 18ms resolution
	timeBeginPeriod( 1 );

	// get WM_TIMER messages pumped every millisecond
//	SetTimer( NULL, 0, 100, NULL );

	cmdSystem->AddCommand( "in_restart", Sys_In_Restart_f, CMD_FL_SYSTEM, "restarts the input system" );
#ifdef DEBUG
	cmdSystem->AddCommand( "createResourceIDs", CreateResourceIDs_f, CMD_FL_TOOL, "assigns resource IDs in _resouce.h files" );
#endif
#if 0
	cmdSystem->AddCommand( "setAsyncSound", Sys_SetAsyncSound_f, CMD_FL_SYSTEM, "set the async sound option" );
#endif

	//
	// Windows user name
	//
	win32.win_username.SetString( Sys_GetCurrentUser() );

	//
	// Windows version
	//
	win32.osversion.dwOSVersionInfoSize = sizeof( win32.osversion );

	if ( !GetVersionEx( (LPOSVERSIONINFO)&win32.osversion ) )
		Sys_Error( "Couldn't get OS info" );

	if ( win32.osversion.dwMajorVersion < 4 ) {
		Sys_Error( GAME_NAME " requires Windows version 4 (NT) or greater" );
	}
	if ( win32.osversion.dwPlatformId == VER_PLATFORM_WIN32s ) {
		Sys_Error( GAME_NAME " doesn't run on Win32s" );
	}

	if( win32.osversion.dwPlatformId == VER_PLATFORM_WIN32_NT ) {
		if( win32.osversion.dwMajorVersion <= 4 ) {
			win32.sys_arch.SetString( "Windows NT (NT)" );
		} else if( win32.osversion.dwMajorVersion == 5 && win32.osversion.dwMinorVersion == 0 ) {
			win32.sys_arch.SetString( "Windows 2K (NT)" );
		} else if( win32.osversion.dwMajorVersion == 5 && win32.osversion.dwMinorVersion == 1 ) {
			win32.sys_arch.SetString( "Windows XP (NT)" );
		} else if ( win32.osversion.dwMajorVersion == 6 ) {
			// jkrige - windows version
			//win32.sys_arch.SetString( "Vista" );
			if( win32.osversion.dwMinorVersion == 0 ) {
				win32.sys_arch.SetString( "Windows Vista" );
			} else if ( win32.osversion.dwMinorVersion == 1 ) {
				win32.sys_arch.SetString( "Windows 7" );
			} else if ( win32.osversion.dwMinorVersion == 2 ) {
				win32.sys_arch.SetString( "Windows 8" );
			} else if ( win32.osversion.dwMinorVersion == 3 ){
				win32.sys_arch.SetString( "Windows 8.1" );
			} else {
				win32.sys_arch.SetString( "Unknown NT 6.x variant" );
			}
			// jkrige - windows version
		} else {
			win32.sys_arch.SetString( "Unknown NT variant" );
		}
	} else if( win32.osversion.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ) {
		if( win32.osversion.dwMajorVersion == 4 && win32.osversion.dwMinorVersion == 0 ) {
			// Win95
			if( win32.osversion.szCSDVersion[1] == 'C' ) {
				win32.sys_arch.SetString( "Win95 OSR2 (95)" );
			} else {
				win32.sys_arch.SetString( "Win95 (95)" );
			}
		} else if( win32.osversion.dwMajorVersion == 4 && win32.osversion.dwMinorVersion == 10 ) {
			// Win98
			if( win32.osversion.szCSDVersion[1] == 'A' ) {
				win32.sys_arch.SetString( "Win98SE (95)" );
			} else {
				win32.sys_arch.SetString( "Win98 (95)" );
			}
		} else if( win32.osversion.dwMajorVersion == 4 && win32.osversion.dwMinorVersion == 90 ) {
			// WinMe
		  	win32.sys_arch.SetString( "WinMe (95)" );
		} else {
		  	win32.sys_arch.SetString( "Unknown 95 variant" );
		}
	} else {
		win32.sys_arch.SetString( "unknown Windows variant" );
	}

	//
	// CPU type
	//
	if ( !idStr::Icmp( win32.sys_cpustring.GetString(), "detect" ) ) {
		idStr string;

		common->Printf( "%1.0f MHz ", Sys_ClockTicksPerSecond() / 1000000.0f );

		win32.cpuid = Sys_GetCPUId();

		string.Clear();

		if ( win32.cpuid & CPUID_AMD ) {
			string += "AMD CPU";
		} else if ( win32.cpuid & CPUID_INTEL ) {
			string += "Intel CPU";
		} else if ( win32.cpuid & CPUID_UNSUPPORTED ) {
			string += "unsupported CPU";
		} else {
			string += "generic CPU";
		}

		string += " with ";
		if ( win32.cpuid & CPUID_MMX ) {
			string += "MMX & ";
		}
		if ( win32.cpuid & CPUID_3DNOW ) {
			string += "3DNow! & ";
		}
		if ( win32.cpuid & CPUID_SSE ) {
			string += "SSE & ";
		}
		if ( win32.cpuid & CPUID_SSE2 ) {
            string += "SSE2 & ";
		}
		if ( win32.cpuid & CPUID_SSE3 ) {
			string += "SSE3 & ";
		}
		if ( win32.cpuid & CPUID_HTT ) {
			string += "HTT & ";
		}
		string.StripTrailing( " & " );
		string.StripTrailing( " with " );
		win32.sys_cpustring.SetString( string );
	} else {
		common->Printf( "forcing CPU type to " );
		idLexer src( win32.sys_cpustring.GetString(), idStr::Length( win32.sys_cpustring.GetString() ), "sys_cpustring" );
		idToken token;

		int id = CPUID_NONE;
		while( src.ReadToken( &token ) ) {
			if ( token.Icmp( "generic" ) == 0 ) {
				id |= CPUID_GENERIC;
			} else if ( token.Icmp( "intel" ) == 0 ) {
				id |= CPUID_INTEL;
			} else if ( token.Icmp( "amd" ) == 0 ) {
				id |= CPUID_AMD;
			} else if ( token.Icmp( "mmx" ) == 0 ) {
				id |= CPUID_MMX;
			} else if ( token.Icmp( "3dnow" ) == 0 ) {
				id |= CPUID_3DNOW;
			} else if ( token.Icmp( "sse" ) == 0 ) {
				id |= CPUID_SSE;
			} else if ( token.Icmp( "sse2" ) == 0 ) {
				id |= CPUID_SSE2;
			} else if ( token.Icmp( "sse3" ) == 0 ) {
				id |= CPUID_SSE3;
			} else if ( token.Icmp( "htt" ) == 0 ) {
				id |= CPUID_HTT;
			}
		}
		if ( id == CPUID_NONE ) {
			common->Printf( "WARNING: unknown sys_cpustring '%s'\n", win32.sys_cpustring.GetString() );
			id = CPUID_GENERIC;
		}
		win32.cpuid = (cpuid_t) id;
	}

	common->Printf( "%s\n", win32.sys_cpustring.GetString() );
	common->Printf( "%d MB System Memory\n", Sys_GetSystemRam() );
	common->Printf( "%d MB Video Memory\n", Sys_GetVideoRam() );
}