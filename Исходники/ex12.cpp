// ------------------------------------------------------------------------------------------
// WinMain
// ------------------------------------------------------------------------------------------
int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if(!InitApp(hInst, nCmdShow))
        CDXError( NULL , "could not initialize CDX application" );

	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!GetMessage(&msg, NULL, 0, 0 )) return msg.wParam;
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else if(bActive)
		{
            // clear screen
			Screen->GetBack()->Fill(0);

            // draw menu
			CurrentMenu->Draw(300, 150);

            // display back buffer
			Screen->Flip();
		}
		else WaitMessage();
	}
}