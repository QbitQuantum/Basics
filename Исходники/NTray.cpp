HICON CTrayNotifyIcon::BitmapToIcon(CBitmap* pBitmap)
{
  //Validate our parameters
  ASSERT(pBitmap);

  //Get the width and height of a small icon
  int w = GetSystemMetrics(SM_CXSMICON);
  int h = GetSystemMetrics(SM_CYSMICON);

  //Create a 0 mask
  int nMaskSize = h*(w/8);
  unsigned char* pMask = new unsigned char[nMaskSize];
  ZeroMemory(pMask, nMaskSize);

  //Create a mask bitmap
  CBitmap maskBitmap;
  BOOL bSuccess = maskBitmap.CreateBitmap(w, h, 1, 1, pMask);

  //Free up the heap memory now that we have created the mask bitmap
  delete [] pMask;

  //Handle the error
  if (!bSuccess)
    return NULL;

  //Create an ICON base on the bitmap just created
  ICONINFO iconInfo;
  iconInfo.fIcon = TRUE;
  iconInfo.xHotspot = 0;
  iconInfo.yHotspot = 0;
  iconInfo.hbmMask = maskBitmap;
  iconInfo.hbmColor = *pBitmap; 
  return CreateIconIndirect(&iconInfo); 
}