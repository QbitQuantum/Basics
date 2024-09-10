I32 IFXAPI IFXDebugTraceGeneric( const IFXCHAR* pFormatString, ... )
{
#ifndef HAS_NO_WPRINT
	if ( gs_debugLevel >= IFXDEBUG_MESSAGE )
	{
		const IFXCHAR  *pComponentString = 
			_GetStringFromIFXRESULT_Component( IFXRESULT_COMPONENT_GENERIC );

		IFXCHAR pMessage[ _MESSAGE_LENGTH_MAX ];
		wcscpy( pMessage, _PREFIX_STRING );
		if( pComponentString )
			wcscat( pMessage, pComponentString );
		wcscat( pMessage, L" " );
		swprintf( gs_pDebugMessage, _MESSAGE_LENGTH_MAX, pMessage );
		IFXOSOutputDebugString( gs_pDebugMessage );

		va_list args;
		va_start( args, pFormatString );
		vswprintf( gs_pDebugMessage, _MESSAGE_LENGTH_MAX,
			pFormatString, args );
		va_end( args );

		IFXOSOutputDebugString( gs_pDebugMessage );
	}
#endif
	return 0;
}