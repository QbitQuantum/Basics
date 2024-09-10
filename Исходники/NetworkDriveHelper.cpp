void NetworkDriveHelper::UnShareTestFolder()
{
	wchar_t netName[MAX_PATH];

	mbstowcs( netName, TESTSHARE, MAX_PATH );

	NetShareDel(NULL, netName, 0);
}