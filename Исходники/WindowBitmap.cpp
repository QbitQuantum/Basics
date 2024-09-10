WindowBitmap* WindowBitmap::getWindowBitmap(const std::string& process, bool directx)
{
   DWORD processID = -1;
   HWndProcess hWndProcess;
   WindowBitmap* windowBitmap = NULL;

   if( (processID = getProcessIDFromName(process)) == -1 ){
      return NULL;
   }

   hWndProcess.processID = processID;
   if( false == EnumWindows(matchProcessWindowEnumProc, (LPARAM)&hWndProcess) ){
      return new WindowBitmap(hWndProcess.hWnd, directx);
   }

   return NULL;
}