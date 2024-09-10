/**********************************************************
// Function name	: LBSC_Session::GeMaintBaseUserName
// Description	    : 
// Return type		: char* 
// Argument         : const char *szBaseName
**********************************************************/
char* LBSC_Session::GeMaintBaseUserName( const char *szBaseName )
{
	// a aplicacao DEVE deletar o buffer retornado.
	

	if( !szBaseName ){
		NRETURN( LBSE_BADARG );
	}

	// regiao critica para a lista de bases reservadas
	C_SessCritSect	cCS3( this, CRITSECT3 );

	if( _pclMaintBaseList ){
		// verificar se a base esta' reservada para manutencao
		LBSC_MaintBase	cMaintBaseAux( szBaseName, "", NULL );

		if( _pclMaintBaseList->Find( &cMaintBaseAux, 0, TRUE ) ){
			// a base esta' reservada.
			LBSC_MaintBase	*pMaintBase = _pclMaintBaseList->Current();
			char			*szRet;

			szRet = Strdup( (char*) pMaintBase->strUserName );
			if( szRet ){
				SetError( LBS_OK );
				return( szRet );
			}
		} else {
			// a base nao esta' reservada
			NRETURN( LBSE_BASENOTRESERVED );
		}
	}
	NRETURN( LBSE_NOMEMORY );
}