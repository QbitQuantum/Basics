//--------------------------------------------------------------------
// ThreadProc() - 本例之 5 個 threads 共用之 thread procedure
//--------------------------------------------------------------------
VOID ThreadProc(DWORD *ThreadArg)
{
RECT rect;
HDC  hDC;
HANDLE hBrush, hOldBrush;
DWORD dwThreadHits = 0;
char  cBuf[80];
int   iThreadNo, i;

   GetClientRect (_hWnd, &rect);
   hDC = GetDC (_hWnd);
   hBrush = CreateSolidBrush(RGB(*(ThreadArg), *(ThreadArg), *(ThreadArg)));  // 變化畫刷顏色
   hOldBrush = SelectObject(hDC, hBrush);

   switch (*ThreadArg) {
     case HIGHEST_THREAD   : iThreadNo = 0; break;
     case ABOVE_AVE_THREAD : iThreadNo = 1; break;
     case NORMAL_THREAD    : iThreadNo = 2; break;
     case BELOW_AVE_THREAD : iThreadNo = 3; break;
     case LOWEST_THREAD    : iThreadNo = 4; break;
   }

   // 顯示 thread 號碼及其優先權 (priority)
   wsprintf(cBuf, "T%d", iThreadNo);
   TextOut(hDC, *(ThreadArg), rect.bottom-150, cBuf, lstrlen(cBuf));
   wsprintf(cBuf, "P=%d", GetThreadPriority(_hThread[iThreadNo]));
   TextOut(hDC, *(ThreadArg), rect.bottom-130, cBuf, lstrlen(cBuf));

   do
   {
     dwThreadHits++;       // 計數器

     // 畫出四方形，代表 thread 的進行
     Rectangle(hDC, *(ThreadArg), rect.bottom-(dwThreadHits/10),
               *(ThreadArg)+0x40, rect.bottom);

     // 延遲...
     if (_uDelayType == SLEEPDELAY)
         Sleep(10);
     else if (_uDelayType == FORLOOPDELAY)
         for (i=0; i<30000; i++);
     else // _uDelayType == NODELAY)
         {   }
   } while (dwThreadHits < 1000);      // 巡迴  1000 次

   hBrush = SelectObject(hDC, hOldBrush);   // 恢復畫刷顏色
   DeleteObject (hBrush);
   ReleaseDC (_hWnd, hDC);
}