ANSC_HANDLE
WebMcoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_COMPONENT_OBJECT          pBaseObject  = NULL;
    PWEB_MODULE_CONTAINER_OBJECT    pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PWEB_MODULE_CONTAINER_OBJECT)AnscAllocateMemory(sizeof(WEB_MODULE_CONTAINER_OBJECT));

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
    AnscCopyString(pBaseObject->Name, WEB_MODULE_CONTAINER_NAME);

    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = WEB_MODULE_CONTAINER_OID;
    pBaseObject->Create            = WebMcoCreate;
    pBaseObject->Remove            = WebMcoRemove;
    pBaseObject->EnrollObjects     = WebMcoEnrollObjects;
    pBaseObject->Initialize        = WebMcoInitialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    return  (ANSC_HANDLE)pMyObject;
}