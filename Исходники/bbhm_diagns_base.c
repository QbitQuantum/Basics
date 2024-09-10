ANSC_HANDLE
BbhmDiagnsCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_COMPONENT_OBJECT          pBaseObject  = NULL;
    PBBHM_DIAG_NS_LOOKUP_OBJECT     pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PBBHM_DIAG_NS_LOOKUP_OBJECT)AnscAllocateMemory(sizeof(BBHM_DIAG_NS_LOOKUP_OBJECT));

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
    AnscCopyString(pBaseObject->Name, BBHM_DIAG_NS_LOOKUP_NAME);

    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = BBHM_DIAG_NS_LOOKUP_OID;

    pBaseObject->Create            = BbhmDiagnsCreate;
    pBaseObject->Remove            = BbhmDiagnsRemove;
    pBaseObject->EnrollObjects     = BbhmDiagnsEnrollObjects;
    pBaseObject->Initialize        = BbhmDiagnsInitialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    g_DiagNSLookupObj = pMyObject;

    return  (ANSC_HANDLE)pMyObject;
}