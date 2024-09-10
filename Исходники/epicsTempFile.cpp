epicsShareFunc void epicsShareAPI epicsTempName ( 
	char * pNameBuf, size_t nameBufLength )
{
    if ( nameBufLength ) {
        pNameBuf[0] = '\0';
        char * pName = _tempnam ( "c:\\tmp", "epics" );
        if ( pName ) {
            if ( nameBufLength > strlen ( pName ) ) {
                strncpy ( pNameBuf, pName, nameBufLength );
            }
            free ( pName );
        }
    }
}