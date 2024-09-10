//--------------------------------------------------
void ofLaunchBrowser(string url){
	
	// http://support.microsoft.com/kb/224816
	
	//make sure it is a properly formatted url
	if(url.substr(0,7) != "http://"){
		printf("ofLaunchBrowser: url must begin http://\n");
		return;
	}

	//----------------------------
	#ifdef TARGET_WIN32
	//----------------------------
		
		#if (_MSC_VER)       
		// microsoft visual studio yaks about strings, wide chars, unicode, etc
		ShellExecuteA(NULL, "open", url.c_str(),
                NULL, NULL, SW_SHOWNORMAL);
		#else
		ShellExecute(NULL, "open", url.c_str(),
                NULL, NULL, SW_SHOWNORMAL);
		#endif

	//----------------------------
	#endif
	//----------------------------
	
	//--------------------------------------
	#ifdef TARGET_OSX
	//--------------------------------------
		// ok gotta be a better way then this, 
		// this is what I found...
		string commandStr = "open "+url;
		system(commandStr.c_str());
	//----------------------------
	#endif
	//----------------------------

}