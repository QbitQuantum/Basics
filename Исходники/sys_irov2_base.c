ANSC_HANDLE
SysIroV2Create
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_COMPONENT_OBJECT          pBaseObject  = NULL;
    PSYS_IROV2_OBJECT               pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PSYS_IROV2_OBJECT)AnscAllocateMemory(sizeof(SYS_IROV2_OBJECT));

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
    AnscCopyString(pBaseObject->Name, SYS_INFO_REPOSITORY_NAME);

    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = SYS_INFO_REPOSITORY_OID;
    pBaseObject->Create            = SysIroV2Create;
    pBaseObject->Remove            = SysIroV2Remove;
    pBaseObject->EnrollObjects     = SysIroV2EnrollObjects;
    pBaseObject->Initialize        = SysIroV2Initialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    return  (ANSC_HANDLE)pMyObject;
}