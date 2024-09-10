void CHostWndMgr::test()
{
	CHostWnd *pWnd;
	CWnd * pMain;
	for(int i = 0 ; i<10; i++)
	{
		pWnd = new CHostWnd();
		if(i == 0)
		{
			pWnd->SetMainWnd(true);
			pMain = pWnd;
		}
		int x = i*150;
		if(i == 0)
			pWnd->Create(IDD_HOST, ::AfxGetMainWindow());
		else
			pWnd->Create(IDD_HOST, pMain);
		pWnd->ShowWindow(SW_SHOW);
		pWnd->MoveWindow(CRect(x, x, x + 200 , x+ 100));
	}

	// Another improved PeekMessage() loop
	MSG msg;
	for (;;)   
	{
		for (;;)    
		{        
			if (false)//IfBackgroundProcessingRequired())  
			{          
				if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))           
					break;     
			}       
			else      
				GetMessage(&msg, NULL, 0, 0);

            if (msg.message == WM_QUIT)    
				return;
			TranslateMessage(&msg);      
			DispatchMessage(&msg);      
		}     
		//BackgroundProcessing();
	}	

}