/*
 * This is a hack used by Chrome and WebKit to expose the fallback font used
 * by Uniscribe for some given text for use with custom shapers / font engines.
 */
static char *UniscribeFallback( const char *psz_family, uni_char_t codepoint )
{
    HDC          hdc          = NULL;
    HDC          meta_file_dc = NULL;
    HENHMETAFILE meta_file    = NULL;
    LPTSTR       psz_fbuffer  = NULL;
    char        *psz_result   = NULL;

    hdc = CreateCompatibleDC( NULL );
    if( !hdc )
        return NULL;

    meta_file_dc = CreateEnhMetaFile( hdc, NULL, NULL, NULL );
    if( !meta_file_dc )
        goto error;

    LOGFONT lf;
    memset( &lf, 0, sizeof( lf ) );

    psz_fbuffer = ToT( psz_family );
    if( !psz_fbuffer )
        goto error;
    _tcsncpy( ( LPTSTR ) &lf.lfFaceName, psz_fbuffer, LF_FACESIZE );
    free( psz_fbuffer );

    lf.lfCharSet = DEFAULT_CHARSET;
    HFONT hFont = CreateFontIndirect( &lf );
    if( !hFont )
        goto error;

    HFONT hOriginalFont = SelectObject( meta_file_dc, hFont );

    TCHAR text = codepoint;

    SCRIPT_STRING_ANALYSIS script_analysis;
    HRESULT hresult = ScriptStringAnalyse( meta_file_dc, &text, 1, 0, -1,
                            SSA_METAFILE | SSA_FALLBACK | SSA_GLYPHS | SSA_LINK,
                            0, NULL, NULL, NULL, NULL, NULL, &script_analysis );

    if( SUCCEEDED( hresult ) )
    {
        hresult = ScriptStringOut( script_analysis, 0, 0, 0, NULL, 0, 0, FALSE );
        ScriptStringFree( &script_analysis );
    }

    SelectObject( meta_file_dc, hOriginalFont );
    DeleteObject( hFont );
    meta_file = CloseEnhMetaFile( meta_file_dc );

    if( SUCCEEDED( hresult ) )
    {
        LOGFONT log_font;
        log_font.lfFaceName[ 0 ] = 0;
        EnumEnhMetaFile( 0, meta_file, MetaFileEnumProc, &log_font, NULL );
        if( log_font.lfFaceName[ 0 ] )
            psz_result = FromT( log_font.lfFaceName );
    }

    DeleteEnhMetaFile(meta_file);
    DeleteDC( hdc );
    return psz_result;

error:
    if( meta_file_dc ) DeleteEnhMetaFile( CloseEnhMetaFile( meta_file_dc ) );
    if( hdc ) DeleteDC( hdc );
    return NULL;
}