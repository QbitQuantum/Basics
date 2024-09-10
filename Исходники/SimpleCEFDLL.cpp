//We must call in WM_SIZE event, hWnd will be the our window handle
void SimpleCEFDLL_ResizeBrowser( HWND hWnd )
{
	//Get the CEF handle
	CefRefPtr<zSimpleCefHandler> simpleCefHandler; 
	if( !g_App->GetCEFHandler( hWnd, simpleCefHandler ) )
		return;

	if( !simpleCefHandler.get() )
		return;

	if( !simpleCefHandler->GetBrowser().get() )
		return;

	if( !simpleCefHandler->GetBrowser()->GetHost().get() )
		return;
	
	CefWindowHandle hWndBrowser = simpleCefHandler->GetBrowser()->GetHost()->GetWindowHandle();
	if( hWndBrowser )
	{
		//Get the size of our window
		RECT rect;
		GetClientRect( hWnd, &rect );
		
		//Set the size to the browser
		HDWP hdwp = BeginDeferWindowPos (1);
		hdwp = DeferWindowPos (hdwp, hWndBrowser, NULL,rect.left, 
			rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
		EndDeferWindowPos (hdwp);
	}
}