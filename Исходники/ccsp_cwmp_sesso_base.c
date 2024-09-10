ANSC_HANDLE
CcspCwmpsoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_COMPONENT_OBJECT          pBaseObject  = NULL;
    PCCSP_CWMP_SESSION_OBJECT        pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PCCSP_CWMP_SESSION_OBJECT)CcspTr069PaAllocateMemory(sizeof(CCSP_CWMP_SESSION_OBJECT));

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
    /* AnscCopyString(pBaseObject->Name, CCSP_CWMP_SESSION_NAME); */

    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = CCSP_CWMP_SESSION_OID;
    pBaseObject->Create            = CcspCwmpsoCreate;
    pBaseObject->Remove            = CcspCwmpsoRemove;
    pBaseObject->EnrollObjects     = CcspCwmpsoEnrollObjects;
    pBaseObject->Initialize        = CcspCwmpsoInitialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    return  (ANSC_HANDLE)pMyObject;
}