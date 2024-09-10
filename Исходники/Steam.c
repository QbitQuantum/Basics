int STEAM_fputs(const char *string, FILE *stream)
{
	SteamHandle_t hndl = (SteamHandle_t)stream;
	int len = strlen(string);
	int n;
	TSteamError steamError;

	n = SteamWriteFile((void*)string, sizeof(char), len, hndl, &steamError);
	if ( n != len || steamError.eSteamError != eSteamErrorNone )
	{
		CheckError((FILE *)hndl, &steamError);
		return EOF;
	}
	return 1;
}