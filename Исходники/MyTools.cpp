CString MyTools::GetFormatedTime(){
	CTime time = CTime::GetCurrentTime();
	//time.get
	CString str = time.Format("%X");
	return str;
}