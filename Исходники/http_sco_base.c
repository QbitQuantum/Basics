ANSC_HANDLE
HttpScoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_COMPONENT_OBJECT          pBaseObject  = NULL;
    PHTTP_SIMPLE_CLIENT_OBJECT      pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PHTTP_SIMPLE_CLIENT_OBJECT)AnscAllocateMemory(sizeof(HTTP_SIMPLE_CLIENT_OBJECT));

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
#ifndef _CCSP_CWMP_TCP_CONNREQ_HANDLER
    AnscCopyString(pBaseObject->Name, HTTP_SIMPLE_CLIENT_NAME);
#endif

    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = HTTP_SIMPLE_CLIENT_OID;
    pBaseObject->Create            = HttpScoCreate;
    pBaseObject->Remove            = HttpScoRemove;
    pBaseObject->EnrollObjects     = HttpScoEnrollObjects;
    pBaseObject->Initialize        = HttpScoInitialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    return  (ANSC_HANDLE)pMyObject;
}