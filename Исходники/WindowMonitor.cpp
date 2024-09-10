////////////////////////////////////////////////////////////////////////////////////////
///                                                                                   //
/// WindowMonitorThreadProc(LPVOID arg);                                                    //            
///                                                                                   //
////////////////////////////////////////////////////////////////////////////////////////
static DWORD WINAPI WindowMonitorThreadProc(LPVOID arg) 
{
 MSG         msg ; 
 _tsetlocale(LC_CTYPE, _T(""));
 MSG_DISPLAY_HOOK = RegisterWindowMessage(DISPLAY_HOOK_MSG);
 if (EnumWindows(EnumWindowsProc,NULL)==FALSE)
 {
  printf("Could not save all previously opened windows\n");
 }
 HookHiddenWindow=AllocateWindow(NULL,WndProc);
 PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
 
 if (HookHiddenWindow==NULL)
   {
    printf("Can't allocate window\n");
	return(0);
   }
   if (HookDisplayFptr(HookHiddenWindow->WindowHandle))
   {
    BOOL bRet;
	printf("Display Hooked\n");
	fflush(stdout);
	SetEvent(ThreadReady);
	SetTimer(HookHiddenWindow->WindowHandle,0xBEEF,1000,(TIMERPROC) NULL);    
    while (1)
          { 
		   bRet=GetMessage (&msg, NULL, 0, 0);
		   if ((bRet != -1) && (bRet!=0))
		   {
            TranslateMessage (&msg) ; 
            DispatchMessage (&msg) ;
		   }
		   else if ((bRet==0)&&(msg.wParam==0xDEADBEEF)) break; 
          } 
	KillTimer(HookHiddenWindow->WindowHandle,0xBEEF);
	if (UnhookDisplayFptr(HookHiddenWindow->WindowHandle))
	 {
      printf("Display Unhooked\n");
	  fflush(stdout);
	 }

   FreeWindow(HookHiddenWindow);
   DeleteAllWindows();
  }
  else  SetEvent(ThreadReady); // FIX ME should use timeout
	return 0;
}