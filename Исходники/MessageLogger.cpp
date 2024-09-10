bool MessageLogger::Notify(char* msg)
{
	//Once we get a notify do something with it here
	//Send msg to windows notice for testing
	size_t converted = 0;
	wchar_t widechar[128];	//128 char max
	//mbstowcs_s(widechar, msg, strlen(msg)+1,);//Plus null
	mbstowcs_s(&converted, widechar, strlen(msg) + 1, msg, _TRUNCATE);
	MessageBox(System::Instance()->GetWindowsHandle(),
		widechar,
		L"MessageLogger Error",  
		MB_OK);
	return true;
}