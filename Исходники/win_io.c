int _urename(const char* oldname, const char* newname){
	wchar_t* woldname, *wnewname;
	int status;
	if(!(woldname = utf8_to_ucs2(oldname)))
		return 1;
	if(!(wnewname = utf8_to_ucs2(newname))){
		free(woldname);
		return 1;
	}
	status = _wrename(woldname, wnewname);
	free(woldname);
	free(wnewname);
	return status;
}