/****WinMain()**************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
/*HINSTANCE hInstance;     current instance
HINSTANCE hPrevInstance;   previous instance
LPSTR lpCmdLine;           command line
int nCmdShow;              show-window type (open/icon) */
{
    MSG msg;                             /* message*/

    if (*lpCmdLine != '\0') filearg = lpCmdLine;
    else filearg = NULL;

	IPC = 1;
	IMAC = 0;

    /*Ltestprint = TRUE;*/  /*test option, compile as TRUE to invoke,*/
    Ltestprint = 0;  /* as FALSE for distribution, can also set in Kludges */  
    Lerr =0;

	initialvalues(); /*starting general values */
	getversion();

	if (filearg) 
   {
      dissectcommandline(filearg);
   }
   
   if (Lquiet == 0)
	{/*running with GUI*/
		if (!InitInstance(hInstance, nCmdShow)) 
      {
         return (FALSE);
      }
		beginnings();
	}
	else 
   {/*running quiet from commandline*/
      for (;;) 
      {
         mainlooprouter();
         if(Lerr) break;   /*030228 to fail gracefully*/
      }
      return(0);
   }

   /*Drop through to here if running NOT Lquiet, i.e. using GUI */
   /*Acquire and dispatch messages until a WM_QUIT message is received.*/
   /* Master endless loop for GUI*/
   /*this GetMessage stuff should be equivalent to Mac HandleEvent stuff*/
   /* besides working as the endless Loop */
   while (GetMessage(&msg,    /* message structure                     */
        NULL,              /* handle of window receiving the message*/
        0,              /* lowest message to examine */
        0))             /* highest message to examine*/
   {
      mainlooprouter(); /*PKININIT, common router*/
      if(Lerr) break;
      if(Lquiet==0) /*was Lcommanded 990402*/
      {
         if (!TranslateAccelerator (PrekinWindow, PrekinAccel, &msg))
         {
            TranslateMessage(&msg);    /* Translates virtual key codes */
            DispatchMessage(&msg);     /* Dispatches message to window */
         }
      }
   }
   return (msg.wParam); /* Returns the value from PostQuitMessage*/
}