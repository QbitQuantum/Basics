void open_console()
{
	BYTE Title[200]; 
	BYTE ClassName[200]; 
	LPTSTR  lpClassName=ClassName; 
	HANDLE hConWnd; 
	FILE *hf;
	static BYTE consolecreated=FALSE;
	static int hCrt=0;
	
	if(consolecreated==TRUE)
	{

		GetConsoleTitle(Title,sizeof(Title));
		hConWnd=FindWindow(NULL,Title);
		GetClassName(hConWnd,lpClassName,120);
		ShowWindow(hConWnd,SW_SHOW);
		SetForegroundWindow(hConWnd);
		hConWnd=GetStdHandle(STD_INPUT_HANDLE);
		FlushConsoleInputBuffer(hConWnd);
		return;
	}
	AllocConsole(); 
	hCrt=_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT);

	fflush(stdin);
	hf=_fdopen(hCrt,"w"); 
	*stdout=*hf; 
	setvbuf(stdout,NULL,_IONBF,0);

	GetConsoleTitle(Title,sizeof(Title));
	hConWnd=FindWindow(NULL,Title);
	GetClassName(hConWnd,lpClassName,120);
	ShowWindow(hConWnd,SW_SHOW); 
	SetForegroundWindow(hConWnd);
	consolecreated=TRUE;
}