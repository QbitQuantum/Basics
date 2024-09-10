int Game_Main(void * parms = NULL, int num_parms = 0)
{

	if (KEYDOWN(VK_ESCAPE))
	{
		PostMessage(gameBox.g_Mainhwnd,WM_CLOSE,0,0);
	}
	
	if (GameOver==0 && nWin==0)
	{
		BltTime();
	}
	else
	{
		char szTemp[50];
		memset(szTemp,0,50);	

		if (nWin==1)
		{
			WNDCLASSEX wcexsub;
			
			wcexsub.cbSize = sizeof(WNDCLASSEX); 
			
			wcexsub.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;	
			wcexsub.lpfnWndProc	    = WndProcSub;
			wcexsub.cbClsExtra		= 0;
			wcexsub.cbWndExtra		= 0;
			wcexsub.hInstance		= gameBox.g_hInstance;
			wcexsub.hIcon			= LoadIcon(gameBox.g_hInstance, IDC_ICON);
			wcexsub.hCursor			= LoadCursor(gameBox.g_hInstance, IDC_ARROW);
			wcexsub.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
			wcexsub.lpszMenuName	= NULL;//MAKEINTRESOURCE(MainMenu);
			wcexsub.lpszClassName	= WINDOW_SUB_CLASS_NAME;
			wcexsub.hIconSm			= LoadIcon(wcexsub.hInstance, IDI_APPLICATION);
			
			if (!RegisterClassEx(&wcexsub))
			{
				return 0;
			}
			
			if (!(g_subhwnd = CreateWindow(WINDOW_SUB_CLASS_NAME, 
				WINDOW_TITLE, 
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				100,100,  // initial x,y
				400,400,  // initial width, height
				NULL, 
				NULL, 
				gameBox.g_hInstance, 
				NULL)))
			{
				return 0;
			}
			
		}
	}
	

	gameBox.BitBlt();
	
	if(NeedRefresh==2)
	{
		ReInit();
	}
	
	Sleep(10);
	return 0;
}