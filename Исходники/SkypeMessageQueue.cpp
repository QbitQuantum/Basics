DWORD WINAPI SkypeProcess (LPVOID lpSkypeMessageQueue) 
{
//	CoInitialize(NULL);
	
	CSkypeMessageQueue * pQueue = (CSkypeMessageQueue *) lpSkypeMessageQueue;
	pQueue->CreateMessageWindow();
	MSG msg;
	int iCtr = 0;

	for(;;) {
		if(iCtr++ < 5) {
			if(PeekMessage(& msg, 0, 0, 0, PM_REMOVE)) {
				AtlTrace("Message: %d, WPARAM: %d, LPARAM: %d\n", msg.message, msg.wParam, msg.lParam);
				if(msg.message == WM_QUIT) {
					PostQuitMessage(0);	//11.02.26 paak
					break;
				}
				TranslateMessage(& msg);
				DispatchMessage(& msg);
			}
		} else {
			iCtr = 0;
		}
		pQueue->ProcessQueue();
		Sleep(1);
	};

	pQueue->DeleteMessageWindow();
	return 0;
}