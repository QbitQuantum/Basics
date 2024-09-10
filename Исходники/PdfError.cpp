void PdfError::LogMessageInternal( ELogSeverity eLogSeverity, const wchar_t* pszMsg, va_list & args )
{
    const wchar_t* pszPrefix = NULL;

    switch( eLogSeverity ) 
    {
        case eLogSeverity_Error:
            break;
        case eLogSeverity_Critical:
	    pszPrefix = L"CRITICAL: ";
            break;
        case eLogSeverity_Warning:
	    pszPrefix = L"WARNING: ";
            break;
	case eLogSeverity_Information:
            break;
	case eLogSeverity_Debug:
	    pszPrefix = L"DEBUG: ";
            break;
	case eLogSeverity_None:
	case eLogSeverity_Unknown:
        default:
            break;
    }

    if( pszPrefix )
        fwprintf( stderr, pszPrefix );

    vfwprintf( stderr, pszMsg, args );
}