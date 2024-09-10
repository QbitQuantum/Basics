HBITMAP MonitorImageSource::GetImage(int width, int height)
{
   DISPLAY_DEVICE named_device;
   named_device.cb = sizeof(DISPLAY_DEVICE);

   for (int deviceId = 0;;deviceId++) {
      DISPLAY_DEVICE device;
      device.cb = sizeof(DISPLAY_DEVICE);

      BOOL result = ::EnumDisplayDevices(NULL, deviceId, &device, 0);
      if (result == 0) break;

      if (device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
         result = ::EnumDisplayDevices(device.DeviceName, 0, &named_device, 0);
      }
   }

   HBITMAP hbmScreen = NULL;
   BITMAP bmpScreen;

   // Retrieve the handle to a display device context for the client 
   // area of the window.
   Win32::DisplayDeviceContext hdcScreen("DISPLAY");
   Win32::WindowDeviceContext hdcWindow(::GetDesktopWindow());

   // Create a compatible DC which is used in a BitBlt from the window DC
   Win32::MemoryDeviceContext hdcMemDC(hdcWindow); 

   //This is the best stretch mode
   ::SetStretchBltMode(hdcWindow,HALFTONE);

   //The source DC is the entire screen and the destination DC is the current window (HWND)
   if(!::StretchBlt(hdcWindow, 
      0,0, width, height, 
      hdcScreen,
      0, 0,
      GetSystemMetrics(SM_CXVIRTUALSCREEN),
      GetSystemMetrics(SM_CYVIRTUALSCREEN),
      SRCCOPY))
   {
   }

   // Create a compatible bitmap from the Window DC
   hbmScreen = CreateCompatibleBitmap(hdcWindow, width, height);
   if(!hbmScreen)
   {
      //TODO: Error handling
   }

   // Select the compatible bitmap into the compatible memory DC.
   SelectObject(hdcMemDC,hbmScreen);

   // Bit block transfer into our compatible memory DC.
   if(!BitBlt(hdcMemDC, 
      0,0, width, height, 
      hdcWindow, 
      0,0,
      SRCCOPY))
   {
      //TODO: Error handling
   }

   // Get the BITMAP from the HBITMAP
   GetObject(hbmScreen,sizeof(BITMAP),&bmpScreen);

   BITMAPFILEHEADER   bmfHeader;    
   BITMAPINFOHEADER   bi;

   bi.biSize = sizeof(BITMAPINFOHEADER);    
   bi.biWidth = bmpScreen.bmWidth;    
   bi.biHeight = bmpScreen.bmHeight;  
   bi.biPlanes = 1;    
   bi.biBitCount = 32;    
   bi.biCompression = BI_RGB;    
   bi.biSizeImage = 0;  
   bi.biXPelsPerMeter = 0;    
   bi.biYPelsPerMeter = 0;    
   bi.biClrUsed = 0;    
   bi.biClrImportant = 0;

   DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

   // Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
   // call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
   // have greater overhead than HeapAlloc.
   HANDLE hDIB = GlobalAlloc(GHND,dwBmpSize); 
   char *lpbitmap = (char *)GlobalLock(hDIB);    

   // Gets the "bits" from the bitmap and copies them into a buffer 
   // which is pointed to by lpbitmap.
   GetDIBits(hdcWindow, hbmScreen, 0,
      (UINT)bmpScreen.bmHeight,
      lpbitmap,
      (BITMAPINFO *)&bi, DIB_RGB_COLORS);

   // A file is created, this is where we will save the screen capture.
   HANDLE hFile = CreateFile(L"captureqwsx.bmp",
      GENERIC_WRITE,
      0,
      NULL,
      CREATE_ALWAYS,
      FILE_ATTRIBUTE_NORMAL, NULL);   

   // Add the size of the headers to the size of the bitmap to get the total file size
   DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

   //Offset to where the actual bitmap bits start.
   bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER); 

   //Size of the file
   bmfHeader.bfSize = dwSizeofDIB; 

   //bfType must always be BM for Bitmaps
   bmfHeader.bfType = 0x4D42; //BM   

   DWORD dwBytesWritten = 0;
   WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
   WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
   WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

   //Unlock and Free the DIB from the heap
   GlobalUnlock(hDIB);    
   GlobalFree(hDIB);

   //Close the handle for the file that was created
   CloseHandle(hFile);

   return 0;
};