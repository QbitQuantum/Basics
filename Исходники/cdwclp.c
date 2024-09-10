/* 
%F cdPlay para Clipboard.
Interpreta os dados do clipboard, seja metafile ou bitmap.
*/
static int cdplay(cdCanvas* canvas, int xmin, int xmax, int ymin, int ymax, void *data)
{
  char filename[10240]; 
  HANDLE hFile;
  DWORD dwSize, nBytesWrite;
  int err;
  unsigned char* buffer;
  (void)data;
  
  if (IsClipboardFormatAvailable(CF_TEXT))
  {
    HANDLE Handle;
    
    if (!cdStrTmpFileName(filename))
      return CD_ERROR;
    
    OpenClipboard(NULL);
    Handle = GetClipboardData(CF_TEXT);
    if (Handle == NULL)
    {
      CloseClipboard();
      return CD_ERROR;
    }
    
    buffer = (unsigned char*)GlobalLock(Handle);
    dwSize = (DWORD)GlobalSize(Handle); 
    
    hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    WriteFile(hFile, buffer, dwSize, &nBytesWrite, NULL);
    CloseHandle(hFile);
    
    GlobalUnlock(Handle);
    
    CloseClipboard();
    
    err = cdCanvasPlay(canvas, CD_METAFILE, xmin, xmax, ymin, ymax, filename);
    
    DeleteFile(filename);
    
    if (err == CD_OK)
      return err;
  }
  
  if (IsClipboardFormatAvailable(CF_ENHMETAFILE))
  {
    HENHMETAFILE Handle;
    
    if (!cdStrTmpFileName(filename))
      return CD_ERROR;
    
    OpenClipboard(NULL);
    Handle = (HENHMETAFILE)GetClipboardData(CF_ENHMETAFILE);
    if (Handle == NULL)
    {
      CloseClipboard();
      return CD_ERROR;
    }
    
    dwSize = GetEnhMetaFileBits(Handle, 0, NULL);
    
    buffer = (unsigned char*)malloc(dwSize);
    
    GetEnhMetaFileBits(Handle, dwSize, buffer);
    
    hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    WriteFile(hFile, buffer, dwSize, &nBytesWrite, NULL);
    CloseHandle(hFile);
    
    free(buffer);
    
    CloseClipboard();
    
    err = cdCanvasPlay(canvas, CD_EMF, xmin, xmax, ymin, ymax, filename);
    
    DeleteFile(filename);
    
    return err;
  }
  
  if (IsClipboardFormatAvailable(CF_METAFILEPICT))
  {
    HANDLE Handle;
    METAFILEPICT* lpMFP;
    
    if (!cdStrTmpFileName(filename))
      return CD_ERROR;
    
    OpenClipboard(NULL);
    Handle = GetClipboardData(CF_METAFILEPICT);
    if (Handle == NULL)
    {
      CloseClipboard();
      return CD_ERROR;
    }
    
    lpMFP = (METAFILEPICT*) GlobalLock(Handle);
    
    dwSize = GetMetaFileBitsEx(lpMFP->hMF, 0, NULL);
    buffer = (unsigned char*)malloc(dwSize);
    
    GetMetaFileBitsEx(lpMFP->hMF, dwSize, buffer);
    
    hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    wmfWritePlacebleFile(hFile, buffer, dwSize, lpMFP->mm, lpMFP->xExt, lpMFP->yExt);
    CloseHandle(hFile);
    
    GlobalUnlock(Handle);
    free(buffer);
    
    CloseClipboard();
    
    err = cdCanvasPlay(canvas, CD_WMF, xmin, xmax, ymin, ymax, filename);
    
    DeleteFile(filename);
    
    return err;
  }
  
  if (IsClipboardFormatAvailable(CF_DIB))
  {
    HANDLE Handle;
    int size;
    cdwDIB dib;
    
    OpenClipboard(NULL);
    Handle = GetClipboardData(CF_DIB);
    if (Handle == NULL)
    {
      CloseClipboard();
      return CD_ERROR;
    }
    
    cdwDIBReference(&dib, (BYTE*) GlobalLock(Handle), NULL);
    
    if (dib.type == -1)
    {
      GlobalUnlock(Handle);
      CloseClipboard();
      return CD_ERROR;
    }
    
    if (cdsizecb)
    {
      int err;
      err = cdsizecb(canvas, dib.w, dib.h, dib.w, dib.h);
      if (err)
      {
        GlobalUnlock(Handle);
        CloseClipboard();
        return CD_ERROR;
      }
    }
    
    size = dib.w*dib.h;
    
    if (xmax == 0) xmax = dib.w + xmin - 1;
    if (ymax == 0) ymax = dib.h + ymin - 1;
      
    if (dib.type == 0)
    {
      unsigned char *r, *g, *b;
      
      r = (unsigned char*)malloc(size);
      g = (unsigned char*)malloc(size);
      b = (unsigned char*)malloc(size);
      
      cdwDIBDecodeRGB(&dib, r, g, b);

      cdCanvasPutImageRectRGB(canvas, dib.w, dib.h, r, g, b, xmin, ymin, xmax - xmin + 1, ymax - ymin + 1, 0, 0, 0, 0);
      
      free(r);
      free(g);
      free(b);
    }
    else
    {
      unsigned char *index;
      long *colors;
      
      index = (unsigned char*)malloc(size);
      colors = (long*)malloc(256*sizeof(long));
      
      cdwDIBDecodeMap(&dib, index, colors);
      
      cdCanvasPutImageRectMap(canvas, dib.w, dib.h, index, colors, xmin, ymin, xmax - xmin + 1, ymax - ymin + 1, 0, 0, 0, 0);
      
      free(index);
      free(colors);
    }
    
    GlobalUnlock(Handle);
    
    CloseClipboard();
    
    return CD_ERROR;
  }
  
  if (IsClipboardFormatAvailable(CF_BITMAP))
  {
    HBITMAP Handle;
    int size, type;
    cdwDIB dib;
    HDC ScreenDC;
    SIZE sz;
    
    OpenClipboard(NULL);
    Handle = GetClipboardData(CF_BITMAP);
    if (Handle == NULL)
    {
      CloseClipboard();
      return CD_ERROR;
    }
    
    GetBitmapDimensionEx(Handle, &sz);
    
    ScreenDC = GetDC(NULL);
    if (GetDeviceCaps(ScreenDC, BITSPIXEL) > 8)
      type = 0;
    else
      type = 1;
    
    dib.w = sz.cx;
    dib.h = sz.cy;
    dib.type = type; 
    
    if (cdsizecb)
    {
      int err;
      err = cdsizecb(canvas, dib.w, dib.h, dib.w, dib.h);
      if (err)
      {
        ReleaseDC(NULL, ScreenDC);
        CloseClipboard();
        return CD_ERROR;
      }
    }
    
    cdwCreateDIB(&dib);
    
    GetDIBits(ScreenDC, Handle, 0, sz.cy, dib.bits, dib.bmi, DIB_RGB_COLORS);	
    ReleaseDC(NULL, ScreenDC);
    
    size = dib.w*dib.h;
    
    if (dib.type == 0)
    {
      unsigned char *r, *g, *b;
      
      r = (unsigned char*)malloc(size);
      g = (unsigned char*)malloc(size);
      b = (unsigned char*)malloc(size);
      
      cdwDIBDecodeRGB(&dib, r, g, b);
      
      cdCanvasPutImageRectRGB(canvas, dib.w, dib.h, r, g, b, 0, 0, dib.w, dib.h, 0, 0, 0, 0);
      
      free(r);
      free(g);
      free(b);
    }
    else
    {
      unsigned char *index;
      long *colors;
      
      index = (unsigned char*)malloc(size);
      colors = (long*)malloc(256*sizeof(long));
      
      cdwDIBDecodeMap(&dib, index, colors);
      
      cdCanvasPutImageRectMap(canvas, dib.w, dib.h, index, colors, 0, 0, dib.w, dib.h, 0, 0, 0, 0);
      
      free(index);
      free(colors);
    }
    
    cdwKillDIB(&dib);
    
    CloseClipboard();
    
    return CD_ERROR;
  }
  
  return CD_ERROR;
}