void font_instance::InitTheFace()
{
#ifdef USE_PANGO_WIN32
    if ( !theFace ) {
        LOGFONT *lf=pango_win32_font_logfont(pFont);
        g_assert(lf != NULL);
        theFace=pango_win32_font_cache_load(daddy->pangoFontCache,lf);
        g_free(lf);
    }
    XFORM identity = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    SetWorldTransform(daddy->hScreenDC, &identity);
    SetGraphicsMode(daddy->hScreenDC, GM_COMPATIBLE);
    SelectObject(daddy->hScreenDC,theFace);
#else
    theFace=pango_ft2_font_get_face(pFont); // Deprecated, use pango_fc_font_lock_face() instead
    if ( theFace ) {
        FT_Select_Charmap(theFace,ft_encoding_unicode) && FT_Select_Charmap(theFace,ft_encoding_symbol);
    }
#endif
}