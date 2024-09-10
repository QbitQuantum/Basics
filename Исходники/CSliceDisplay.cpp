extern Graphics::TBitmap* CreateBitmap(int width, int height, TPixelFormat pixelFormat)
{
  if (pixelFormat != pf1bit &&
      pixelFormat != pf8bit &&
      pixelFormat != pf24bit) return NULL;

  Graphics::TBitmap *Bitmap;

  RGBQUAD *oldColors;
  LOGPALETTE* pal = NULL;
  try
  {
    Bitmap = new Graphics::TBitmap();
    if (Bitmap == NULL) return NULL;
    Bitmap->PixelFormat = pixelFormat;
    Bitmap->HandleType = bmDIB;
    Bitmap->Width = width;
    Bitmap->Height = height;

    if (pixelFormat == pf8bit)
    {
      pal = (LOGPALETTE*) malloc( sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256);
      pal->palVersion = 0x300;
      pal->palNumEntries = 256;
      for(short i = 0 ; i < 256 ; i++)
      {
        pal->palPalEntry[i].peRed =  (Byte)i;
        pal->palPalEntry[i].peGreen = (Byte)i;
        pal->palPalEntry[i].peBlue = (Byte)i;
      }

      HPALETTE hpal = CreatePalette(pal);
      if(hpal) Bitmap->Palette = hpal;
    }
  }
  __finally
  {
    if (pal != NULL) delete pal;
  }

  return Bitmap;
}