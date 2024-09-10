/*
 * SetRGBValues - set the RGB values for the initialized images
 */
void SetRGBValues( RGBQUAD *argbvals, int upperlimit )
{
    int                 i;
    RGBQUAD             *argb;
    PALETTEENTRY        *pe;
    int                 num;
    HDC                 hdc;

    hdc = GetDC( HColorPalette );
    pe = MemAlloc( upperlimit * sizeof( PALETTEENTRY ) );
    num = GetSystemPaletteEntries( hdc, 0, upperlimit, pe );
    ReleaseDC( HColorPalette, hdc );

    argb = argbvals;
    if( num > upperlimit )
        num = upperlimit;
    for( i = 0; i < num; i++ ) {
        argb[i].rgbBlue = pe[i].peBlue;
        argb[i].rgbGreen = pe[i].peGreen;
        argb[i].rgbRed = pe[i].peRed;
        argb[i].rgbReserved = 0;
    }
    MemFree( pe );

} /* SetRGBValues */