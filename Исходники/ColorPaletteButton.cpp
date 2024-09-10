bool CColorPaletteButton::verifyColor()
{
   CDC* dc = GetDC();

   ASSERT(dc != NULL);
   ASSERT(dc->GetDeviceCaps(RASTERCAPS) & RC_BITBLT);

   CRect clientRect;
   GetClientRect(&clientRect);
   CPoint center((clientRect.left + clientRect.right)/2,(clientRect.top + clientRect.bottom)/2);

   COLORREF colorButtonColor = dc->GetPixel(center);

   m_appPalette.pushPalette(dc);

   PALETTEENTRY paletteEntry;
   CPalette* palette = dc->GetCurrentPalette();
   ASSERT(palette != NULL);
   int numEntries = palette->GetEntryCount();

   VERIFY(palette->GetPaletteEntries(m_appPalette.getEditIndex(),1,&paletteEntry) > 0);

   COLORREF paletteColor = RGB(paletteEntry.peRed,paletteEntry.peGreen,paletteEntry.peBlue);

   bool retval = (colorButtonColor == paletteColor);

   m_appPalette.popPalette(dc);

   if (!retval)
   {
      TRACE("CColorPaletteButton::verifyColor() - %s, buttonColor=0x%08x, paletteColor=0x%08x, \n",
         retval ? "success" : "failure",colorButtonColor,paletteColor);
   }
   else
   {
      TRACE("CColorPaletteButton::verifyColor() - %s, buttonColor=0x%08x, paletteColor=0x%08x, \n",
         retval ? "success" : "failure",colorButtonColor,paletteColor);
   }

   return retval;
}