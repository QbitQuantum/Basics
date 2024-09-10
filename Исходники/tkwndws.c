void tkSetOneColor(int index, float r, float g, float b)
{
    PALETTEENTRY PalEntry;
    HPALETTE Palette;
    if ( NULL != (Palette = CreateCIPalette( tkhdc )) )
    {
        PalEntry.peRed   = (BYTE)(r*(float)255.0 + (float)0.5);
        PalEntry.peGreen = (BYTE)(g*(float)255.0 + (float)0.5);
        PalEntry.peBlue  = (BYTE)(b*(float)255.0 + (float)0.5);
        PalEntry.peFlags = 0;
        SetPaletteEntries( Palette, index, 1, &PalEntry);
        DelayPaletteRealization();
    }
}