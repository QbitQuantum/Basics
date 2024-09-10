PrintContext_t Print_Create(BOOL bPrintConsole, UINT32 u32InitBufferSize, UINT32 u32BufferBlockSize)
	{

	PrintContext_t hPrint;

	if ((hPrint = WcmMalloc(sizeof(stPrintContext_t))) == NULL)
		return NULL;

	if ((hPrint->bszTextBuffer = WcmMalloc(BCHARS2BYTES(u32InitBufferSize))) == NULL)
		return NULL;

	// Initialize the text buffer
	hPrint->u32TextBufferSize = u32InitBufferSize;
	hPrint->u32NextBufferChar = 0;
	b_memset(hPrint->bszTextBuffer, 0, u32InitBufferSize);

	hPrint->u32BufferBlockSize = u32BufferBlockSize;

	// Initialize the rest
	hPrint->hLogFile       = NULL;
	hPrint->bszLogFileName = NULL;
	hPrint->bEnabled       = TRUE;
	hPrint->bBuffered      = FALSE;
	hPrint->bPrintConsole  = bPrintConsole;

	if (bPrintConsole)
#ifdef WIN32
		hPrint->fPrintConsole = stdout;
#else
#ifdef ENABLE_WIDE_CHAR
		{
		if (fwide(stdout,0) > 0)
			hPrint->fPrintConsole = stdout;
		else 
			{
			hPrint->fPrintConsole = fopen("/dev/tty", "w");
			if (hPrint->fPrintConsole != NULL)
				fwide(hPrint->fPrintConsole, 1);
			}
		}
#else
		{
		hPrint->fPrintConsole = stdout;
		}
#endif
#endif
	else