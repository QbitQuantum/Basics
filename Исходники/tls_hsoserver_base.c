ANSC_HANDLE
TlsHsoServerCreate
(
    ANSC_HANDLE                 hContainerContext,
    ANSC_HANDLE                 hOwnerContext,
    ANSC_HANDLE                 hAnscReserved
)
{
    PANSC_COMPONENT_OBJECT          pBaseObject  = NULL;
    PTLS_HSO_SERVER_OBJECT          pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PTLS_HSO_SERVER_OBJECT)AnscAllocateMemory(sizeof(TLS_HSO_SERVER_OBJECT));

    if ( !pMyObject )
    {
        return  (ANSC_HANDLE)NULL;
    }
    else
    {
        pBaseObject = (PANSC_COMPONENT_OBJECT)pMyObject;
    }

    /*
     * Initialize the common variables and functions for a container object.
     */
    /* AnscCopyString(pBaseObject->Name, TLS_HSO_SERVER_NAME); */

    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = TLS_HSO_SERVER_OID;
    pBaseObject->Create            = TlsHsoServerCreate;
    pBaseObject->Remove            = TlsHsoServerRemove;
    pBaseObject->EnrollObjects     = TlsHsoServerEnrollObjects;
    pBaseObject->Initialize        = TlsHsoServerInitialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    return  (ANSC_HANDLE)pMyObject;
}