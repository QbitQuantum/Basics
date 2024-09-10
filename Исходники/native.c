void SND_InitSoundTrack(char* filename)
{
	char command[256];
	int cmdResult;

	Log_Printf("[SND_InitSoundTrack] start '%s'.\n",filename);

	sprintf(command,format,filename);

	Log_Printf(command);
	Log_Printf("\n");

	cmdResult = mciSendStringA(command, NULL, 0, 0);

	if (cmdResult)
		SND_LogMCI_Error(command,cmdResult);
}