//===========================================================================
int APIENTRY WinMain (HINSTANCE passinstance,
					  HINSTANCE previnstance,
					  LPSTR     lpCmdLine,
					  int       nCmdShow)
{
#ifdef CPUDEBUG
	char nomearq[MAX_PATH];
#endif

	char imagefilename[MAX_PATH];

	// DO ONE-TIME INITIALIZATION
	instance = passinstance;

	// Initialize COM
	CoInitialize( NULL );

	GdiSetBatchLimit(512);
	GetProgramDirectory();
	RegisterExtensions();
	FrameRegisterClass();
	Inicializar1();

	strcpy(imagefilename, progdir);
	strcat(imagefilename, NOMEARQTKDOS);

	if (lpCmdLine[0] != '\0')
	{
		CharLowerBuff(&lpCmdLine[strlen(lpCmdLine)-3],3);
		strcpy(imagefilename, lpCmdLine);
	}

#ifdef CPUDEBUG
	strcpy(nomearq, progdir);
	strcat(nomearq, "debugCPU.txt");
	DeleteFile(nomearq);
	arquivocpu = fopen(nomearq, "wb");
#endif


	do
	{
		// DO INITIALIZATION THAT MUST BE REPEATED FOR A RESTART
		restart = 0;
		mode    = MODE_LOGO;
		LoadConfiguration();
		DebugInitialize();
		JoyInitialize();
		MemInitialize();
		VideoInitialize();
		Timer_InitTimer();

		FrameCreateWindow();
		MemAtualizaSlotAux();

		if (imagefilename[0] != '\0')
		{
			DiskInsert(0, imagefilename, FALSE, FALSE);
			imagefilename[0] = '\0';
		}

		// ENTER THE MAIN MESSAGE LOOP
		EnterMessageLoop();
	}
	while (restart);

#ifdef CPUDEBUG
	//CloseHandle(arquivocpu);
	fclose(arquivocpu);
#endif

	// Release COM
	CoUninitialize();

	return 0;
}