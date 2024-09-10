/* then they will all use the same context and avoid overhead  */
int
readersManagerConnect(
                    tReaderManager *pManager
                    )
{
    LONG 		    rv;

    if ( pManager == NULL )
        return( SCARD_E_INVALID_PARAMETER );

    rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, (LPSCARDCONTEXT)&(pManager->hContext) );
    if (rv != SCARD_S_SUCCESS)
    {
        PCSC_ERROR( pManager, rv, "SCardEstablishContext");
        pManager->hContext = NULL;

        eventDispatch( PCSCD_FAIL, NULL, 0, pManager );

        return( rv );
    }

    eventDispatch( PCSCD_CONNECT, NULL, 0, pManager );

    /* Find all the readers and fill the readerManager data structure */
    rv = readersEnumerate( pManager );

    return (rv);

}