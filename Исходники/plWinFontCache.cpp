void    plWinFontCache::Clear( void )
{
    int     i;


    if( !fInShutdown )
        plStatusLog::AddLineS( "pipeline.log", "** Clearing Win32 font cache **" );

    for( i = 0; i < fFontCache.GetCount(); i++ )
        DeleteObject( fFontCache[ i ].fFont );
    fFontCache.Reset();

    for( i = 0; i < fFontNameCache.GetCount(); i++ )
        delete [] fFontNameCache[ i ];
    fFontNameCache.Reset();

    for( i = 0; i < fCustFonts.GetCount(); i++ )
    {
#if (_WIN32_WINNT >= 0x0500)
        if (plDynSurfaceWriter::CanHandleLotsOfThem())
            RemoveFontResourceExW(fCustFonts[i]->fFilename.AsString().ToWchar(), FR_PRIVATE, 0);
        else
#endif
            if (RemoveFontResourceW(fCustFonts[i]->fFilename.AsString().ToWchar()) == 0)
            {
                int q= 0;
                DWORD e = GetLastError();
            }
        delete fCustFonts[ i ];
    }
    fCustFonts.Reset();
}