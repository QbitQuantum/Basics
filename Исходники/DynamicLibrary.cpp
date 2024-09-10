std::string DynamicLibrary::getVersionStr() {
	std::string ret = "missing";
	DWORD infoHandle;
	LONG sz = GetFileVersionInfoSizeA(name.c_str(),&infoHandle);
	if (!sz) return ret;

	VS_FIXEDFILEINFO * fileInf;
	std::vector<BYTE> buf(sz*2);
	if (!GetFileVersionInfoA(name.c_str(),0,sz,&buf[0])) return ret;
	UINT len;
	if (!VerQueryValueA(&buf[0],"\\",(LPVOID *) &fileInf,&len)) return ret;

	std::ostringstream strb;
	strb << HIWORD(fileInf->dwFileVersionMS) << "."
		 << LOWORD(fileInf->dwFileVersionMS) << "."
		 << HIWORD(fileInf->dwFileVersionLS) << "."
		 << LOWORD(fileInf->dwFileVersionLS);
	return strb.str();
	}