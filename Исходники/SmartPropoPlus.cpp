/* Test if this is a Vista machine or higher */
int isVista(void)
{
	OSVERSIONINFOEX InfoStruct;
	DWORD Mask;
	DWORDLONG ConditionMask=0;

	// Init
	InfoStruct.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	InfoStruct.dwMajorVersion = 6; // Vista
	Mask = VER_MAJORVERSION;
	VerSetConditionMask(ConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);

	return VerifyVersionInfo(&InfoStruct, Mask, ConditionMask);
}