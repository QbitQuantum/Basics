//-----------------------------------------------------------------------------
// Name: create
// Desc: Initializes the font
//-----------------------------------------------------------------------------
bool GUIFont::create(LPDIRECT3DDEVICE9 d3dDevice, const char* fontName, DWORD height, bool bold, bool italic)
{
  // Validate parameters
  if (!d3dDevice || !fontName || !height) return false;

  // Make sure the font is clear
  destroy();

  // These variables are used within this method
  HFONT hFont = NULL;
  HFONT hFontOld = NULL;
  HDC hDC = NULL;
  HBITMAP hbmBitmap = NULL;
  HGDIOBJ hbmOld = NULL;

  // Assume that fonts drawn onto the texture do not need scaling unless the texture size
  // required is larger than the device's maximum
  myTextScale = 1.0f;

  // Create a device context for text to draw into
  hDC = CreateCompatibleDC(NULL);
  SetMapMode(hDC, MM_TEXT);

  // Generate the font
  if (!createGDIFont(hDC, &hFont, fontName, height, bold, italic ))
  {
    // Free our context
    DeleteDC(hDC);

    // Return failure
    return false;
  }

  // Set this new font up for use (but store the old one so we can restore it later
  hFontOld = (HFONT)SelectObject(hDC, hFont);

  // Get this device's ability information
  D3DCAPS9 d3dCaps;
  d3dDevice->GetDeviceCaps(&d3dCaps);

  // Usually the required texture is at least 128x128 pixels.
  myTexWidth = myTexHeight = 128;

  // Holds the result of painting the font
  PaintAlphabetResult par;

  // Calculate the size of the smallest power-of-two texture which will hold all the
  // printable characters we need.  First, we try making the texture larger until it gets
  // bigger than the device can support.  Then, we scale down the text to fit the largest
  // texture.
  do
  {
    // If the texture size matches the device's maximum and we've started another
    // iteration, that means the text is too big.  Scale it down.
    if (myTexWidth == d3dCaps.MaxTextureWidth)
      myTextScale *= 0.9f;

    // If this texture is smaller than the device's maximum size, scale it up
    if (myTexWidth < d3dCaps.MaxTextureWidth)
    {
      myTexWidth *= 2;
      myTexHeight *= 2;
    }

    // If the texture is larger than the device can support, scale the text a bit and
    // make the texture the maximum size.
    if (myTexWidth > d3dCaps.MaxTextureWidth)
    {
      // Calculate the text scaling amount
      myTextScale = (float)d3dCaps.MaxTextureWidth / (float)myTexWidth;
      myTexWidth = myTexHeight = d3dCaps.MaxTextureWidth;
    }

    // If we are at the maximum sized texture, the text has been scaled so it needs to
    // be recreated.
    if (myTexWidth == d3dCaps.MaxTextureWidth)
    {
      // Get rid of the new font and put the old font back in
      DeleteObject(SelectObject(hDC, hFontOld));

      // Create the new font
      if (!createGDIFont(hDC, &hFont, fontName, height, bold, italic))
      {
        // Free information
        DeleteDC(hDC);

        // Return failure
        return false;
      }

      // Select the new font
      hFontOld = (HFONT)SelectObject(hDC, hFont);
    }

  } while(PAR_FAILED_NOTENOUGHSPACE == (par = paintAlphabet(hDC, true)));

  // Check to make sure the function didn't fail
  if (par != PAR_SUCCEEDED)
  {
    // Put the old font back into the device context
    SelectObject(hDC, hFontOld);

    // Delete used information
    DeleteObject(hFont);
    DeleteDC(hDC);

    // Erase internal info
    zero();

    // This method failed
    return false;
  }

  // Create the font's texture
  if (FAILED(d3dDevice->CreateTexture(myTexWidth, myTexHeight, 1, 0, D3DFMT_A4R4G4B4,
                      D3DPOOL_MANAGED, &myTexture, NULL)))
  {
    // Put the old font back into the device context
    SelectObject(hDC, hFontOld);

    // Delete used information
    DeleteObject(hFont);
    DeleteDC(hDC);

    // Erase internal info
    zero();

    // Return failure
    return false;
  }

  // Prepare to create the bitmap
  DWORD* bitmapBits;
  BITMAPINFO bmi;
  ZeroMemory(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));
  bmi.bmiHeader.biSize    = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth     =  (int)myTexWidth;
  bmi.bmiHeader.biHeight    = -(int)myTexHeight;
  bmi.bmiHeader.biPlanes    = 1;
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biBitCount  = 32;

  // Create a bitmap for the font
  hbmBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (void**)&bitmapBits, NULL, 0);
  hbmOld = SelectObject(hDC, hbmBitmap);

  // Set up the text properties
  SetTextColor(hDC, RGB(255,255,255));
  SetBkColor(  hDC, 0x00000000);
  SetTextAlign(hDC, TA_TOP);

  // Actually draw the alphabet
  if (PAR_SUCCEEDED != paintAlphabet(hDC, false))
  {
    // Get rid of created Windows information
    SelectObject(hDC, hbmOld);
    SelectObject(hDC, hFontOld);
    DeleteObject(hbmBitmap);
    DeleteObject(hFont);
    DeleteDC(hDC);

    // Free internal data
    destroy();

    // Return error
    return false;
  }

  // Lock the surface and manually write the alpha values for the pixels
  D3DLOCKED_RECT d3dlr;
  if (FAILED(myTexture->LockRect(0, &d3dlr, 0, 0)))
  {
    // Get rid of created Windows information
    SelectObject(hDC, hbmOld);
    SelectObject(hDC, hFontOld);
    DeleteObject(hbmBitmap);
    DeleteObject(hFont);
    DeleteDC(hDC);

    // Free internal data
    destroy();

    // Return error
    return false;
  }

  // This data is used to fill in the texture
  BYTE* destRow;
  destRow = (BYTE*)d3dlr.pBits;
  WORD* dest16;
  BYTE alpha;
  DWORD x, y;

  // Write the alpha values
  for (y = 0; y < myTexHeight; ++y)
  {
    dest16 = (WORD*)destRow;
    for (x = 0; x < myTexWidth; ++x)
    {
      // Determine whether or not a pixel was written here
      alpha = (BYTE)((bitmapBits[myTexWidth * y + x] & 0xFF) >> 4);

      // Write the alpha value
      if (alpha > 0)
        *dest16++ = ((WORD)(alpha << 12) | 0x0FFF); // updated to remove alpha b/c it causes rendering artifacts
      else
        *dest16++ = 0x0000;
    }

    // Move to the next row
    destRow += d3dlr.Pitch;
  }

  // Unlock the texture
  myTexture->UnlockRect(0);

  // Restore states and delete temporary information
  SelectObject(hDC, hbmOld);
  SelectObject(hDC, hFontOld);
  DeleteObject(hbmBitmap);
  DeleteObject(hFont);
  DeleteDC(hDC);

  // Success
  return true;
}