void change_dir(std::string dir)
{
	#ifdef _WIN32
		wchar_t* wdir = new wchar_t[strlen(dir.c_str()) + 1];
		mbstowcs(wdir, dir.c_str(), strlen(dir.c_str()) + 1);
		_wchdir(wdir);
		//SetCurrentDirectory(wdir);
	#else
		
	#endif
	
}