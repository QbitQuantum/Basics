void Communicator::GetPipeNameStr(WCHAR ** buff,DWORD pid)
{
	WCHAR path[10];
	WCHAR  pid_str[10];
	wcscpy(path,L"\\\\.\\pipe\\");
	_itow(pid,pid_str,10);
	*buff=new WCHAR[20];
	wcscpy(*buff,path);
	wcscpy(*buff+9,pid_str);
}