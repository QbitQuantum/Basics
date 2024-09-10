/// Function name  : drawSplashWindow
// Description     : Paints the splash window and the progress of the load game data operation
// 
// HWND  hWnd  : [in] Splash window
// 
VOID  drawSplashWindow(SPLASH_WINDOW_DATA*  pWindowData)
{
   BLENDFUNCTION  oBlendData;             // Alpha blending data
   DC_STATE*      pDCState;               // DC state
   POINT          ptOrigin;               // Drawing origin into the memory DC
   SIZE           siWindowSize;           // Size of the splash window
   RECT           rcProgressText;         // Progress stage text drawing rectangle
   TCHAR*         szProgressText;         // Progress stage text
   HDC            hScreenDC,
                  hMemoryDC;              // Memory DC
   UINT           iCurrentProgress,       // Operation progress : 0 <= n <= 10000
                  iProgressBarLength;     // Length of the progress bar, in pixels

   // Prepare
   utilZeroObject(&oBlendData, BLENDFUNCTION);
   siWindowSize = siLogoBitmap;
   ptOrigin.x = 0;
   ptOrigin.y = 0;

   /// Create DC, Pen, Font, Bitmap and progress text
   hScreenDC      = GetDC(NULL);
   hMemoryDC      = CreateCompatibleDC(hScreenDC);
   pDCState       = utilCreateDeviceContextState(hMemoryDC);
   szProgressText = loadString(getCurrentOperationStageID(getMainWindowData()->pOperationPool), 128);

   /// Create bitmap
   pWindowData->hLogoBitmap = (HBITMAP)LoadImage(getResourceInstance(), TEXT("LOGO_BITMAP"), IMAGE_BITMAP, siLogoBitmap.cx, siLogoBitmap.cy, LR_CREATEDIBSECTION);
   
   // Setup DC
   utilSetDeviceContextBitmap(pDCState, pWindowData->hLogoBitmap);
   utilSetDeviceContextPen(pDCState, pWindowData->hProgressPen);
   utilSetDeviceContextFont(pDCState, pWindowData->hProgressFont, clProgressBar);
   utilSetDeviceContextBackgroundMode(pDCState, TRANSPARENT);

   // Request per-pixel alpha blending
   oBlendData.BlendOp             = AC_SRC_OVER;
   oBlendData.AlphaFormat         = AC_SRC_ALPHA;
   oBlendData.SourceConstantAlpha = 255;

   // Calculate progress and text rectangles
   iCurrentProgress   = getCurrentOperationProgress(getMainWindowData()->pOperationPool);
   iProgressBarLength = (ptProgressBarEnd.x - ptProgressBarStart.x) * iCurrentProgress / iProgressBarMaximum;
   SetRect(&rcProgressText, ptProgressBarStart.x - 20, ptProgressBarStart.y + 3, ptProgressBarEnd.x + 20, ptProgressBarEnd.y + 20);

   /// [PROGRESS] Draw progress bar
   MoveToEx(hMemoryDC, ptProgressBarStart.x, ptProgressBarStart.y, NULL);
   LineTo(hMemoryDC, (ptProgressBarStart.x + iProgressBarLength), ptProgressBarEnd.y);

   /// [TEXT] Draw progress text
   DrawText(hMemoryDC, szProgressText, lstrlen(szProgressText), &rcProgressText, DT_SINGLELINE WITH DT_CENTER);

   /// [LOGO] Paint alpha-blended logo
   if (!UpdateLayeredWindow(pWindowData->hWnd, NULL, NULL, &siWindowSize, hMemoryDC, &ptOrigin, 0, &oBlendData, ULW_ALPHA))
      ERROR_CHECK("updating layered window", FALSE);

   // [CHECK] Are we running in windows 7 or newer?
   if (getAppWindowsVersion() >= WINDOWS_7)
      /// [WINDOWS 7] Display progress in the taskbar
      utilSetWindowProgressValue(getAppWindow(), iCurrentProgress, iProgressBarMaximum);

   // Cleanup
   utilDeleteDeviceContextState(pDCState);
   DeleteDC(hMemoryDC);
   DeleteBitmap(pWindowData->hLogoBitmap);
   ReleaseDC(NULL, hScreenDC);
   utilDeleteString(szProgressText);
}