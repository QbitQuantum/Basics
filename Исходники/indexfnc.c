void
setPaletteIndex(int i, float r, float g, float b)
{
    PALETTEENTRY pe;

    pe.peRed = (BYTE) (255.0F * r);
    pe.peGreen = (BYTE) (255.0F * g);
    pe.peBlue = (BYTE) (255.0F * b);
    pe.peFlags = PC_NOCOLLAPSE;
    SetPaletteEntries(hPalette, i, 1, &pe);
    UnrealizeObject(hPalette);
}