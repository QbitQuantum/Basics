rtl_TextEncoding SAL_CALL osl_getTextEncodingFromLocale( rtl_Locale * pLocale )
{
    struct EnumLocalesParams params = { L"", L"", 0 };

    /* initialise global TLS id */
    if( (DWORD) -1 == g_dwTLSLocaleEncId )
    {
        oslMutex globalMutex = * osl_getGlobalMutex();

        /* initializing must be thread save */
        osl_acquireMutex( globalMutex );

        if( (DWORD) -1 == g_dwTLSLocaleEncId )
            g_dwTLSLocaleEncId = TlsAlloc();

        osl_releaseMutex( globalMutex );
    }

    /* if pLocale is NULL, use process locale as default */
    if( NULL == pLocale )
        osl_getProcessLocale( &pLocale );

    /* copy in parameters to structure */
    if( pLocale && pLocale->Language && pLocale->Language->length < ELP_LANGUAGE_FIELD_LENGTH )
    {
        wcscpy( params.Language, pLocale->Language->buffer );

        if( pLocale->Country && pLocale->Country->length < ELP_COUNTRY_FIELD_LENGTH )
            wcscpy( params.Country, pLocale->Country->buffer );

        /* save pointer to local structure in TLS */
        TlsSetValue( g_dwTLSLocaleEncId, &params );

        /* enum all locales known to Windows */
        EnumSystemLocalesA( EnumLocalesProcA, LCID_SUPPORTED );

        /* use the LCID found in iteration */
        return GetTextEncodingFromLCID( params.Locale );
    }

    return RTL_TEXTENCODING_DONTKNOW;
}