int system_( const char *cmd ){

#if _WIN32

	bool inherit=false;
	DWORD flags=CREATE_NO_WINDOW;
	STARTUPINFOA si={sizeof(si)};
	PROCESS_INFORMATION pi={0};
	
	bbString tmp=BB_T( "cmd /S /C\"" )+BB_T( cmd )+BB_T( "\"" );
	
	if( GetStdHandle( STD_OUTPUT_HANDLE ) ){
	
		inherit=true;
		si.dwFlags=STARTF_USESTDHANDLES;
		si.hStdInput=GetStdHandle( STD_INPUT_HANDLE );
		si.hStdOutput=GetStdHandle( STD_OUTPUT_HANDLE );
		si.hStdError=GetStdHandle( STD_ERROR_HANDLE );
	}
	
	if( GetConsoleWindow() ){

		flags=0;
	}
	
	if( !CreateProcessA( 0,(LPSTR)tmp.c_str(),0,0,inherit,flags,0,0,&si,&pi ) ) return -1;

	WaitForSingleObject( pi.hProcess,INFINITE );
	
	int res=GetExitCodeProcess( pi.hProcess,(DWORD*)&res ) ? res : -1;
	
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return res;

#else

	return system( cmd );

#endif

}