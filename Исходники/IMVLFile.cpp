string IMVLFile::GetCompName() 
{
	char buf[1024];
	DWORD dwCompNameLen = 1024;
	GetComputerNameA(buf, &dwCompNameLen);
	return string(buf);
}