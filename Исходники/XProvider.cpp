// Use a secondary thread to work the windows message pump.
DWORD WINAPI SecondaryThread(LPVOID pInputParam)
{

   MSG msg;

   // msg-pump.
   while (GetMessage(&msg, NULL, 0, 0))
   {
	   //debugString(8,"SecondaryThread","msg-pump",_where());
	   g_hWnd = msg.hwnd;

	   if(msg.message == WM_USER + 1)
	   {	// shutDown was called, shutdown TAPI and return.
		   if( g_hTAPI != NULL)
		   {
			   debugString(4,"SecondaryThread","lineShutdown",_where());
				lineShutdown( g_hTAPI );
				g_hTAPI = NULL;
		   }
		   return 0;
	   }
	   else
	   {
		   TranslateMessage(&msg);
		   DispatchMessage(&msg);
	   }
   }
   return 0;
}