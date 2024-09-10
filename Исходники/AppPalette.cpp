void CAppPalette::animatePaletteEntry(int index,COLORREF color)
{
   PALETTEENTRY* paletteEntry = getPaletteEntry(index);

   paletteEntry->peRed   = GetRValue(color);
   paletteEntry->peGreen = GetGValue(color);
   paletteEntry->peBlue  = GetBValue(color);
   paletteEntry->peFlags = PC_RESERVED;

   if (m_paletteDevice)
   {
      AnimatePalette(index,1,paletteEntry);
   }
}