static bool GetDataFromHFONT( HFONT hf, char** outFontBuffer, unsigned int& outFontBufferLen )
{
    HDC		hdc;

    if ( ( hdc = GetDC(0) ) == NULL ) {
        DeleteObject(hf);
        return false;
    }
    
    SelectObject(hdc, hf);

    outFontBufferLen = GetFontData(hdc, 0, 0, 0, 0);
    
    if (outFontBufferLen == GDI_ERROR) {
        ReleaseDC(0, hdc);
        DeleteObject(hf);
        return false;
    }
    
    *outFontBuffer = (char *) malloc( outFontBufferLen );
    
    if ( GetFontData( hdc, 0, 0, *outFontBuffer, (DWORD) outFontBufferLen ) == GDI_ERROR ) {
        free( *outFontBuffer );
        *outFontBuffer = NULL;
        outFontBufferLen = 0;
        ReleaseDC(0, hdc);
        DeleteObject(hf);
        return false;
    }
    
    ReleaseDC( 0, hdc );
    DeleteObject( hf );
    
    return true;
}