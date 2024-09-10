ANSC_HANDLE
AnscObjectArrayCOCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_COMPONENT_OBJECT          pBaseObject  = NULL;
    PANSC_OBJECT_ARRAY_OBJECT       pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PANSC_OBJECT_ARRAY_OBJECT)AnscAllocateMemory(sizeof(ANSC_OBJECT_ARRAY_OBJECT));

    if ( !pMyObject )
    {
        return  (ANSC_HANDLE)NULL;
    }
    else
    {
        pBaseObject = (PANSC_COMPONENT_OBJECT)pMyObject;
    }

    /*
     * Initialize the common variables and functions for a component object.
     */
    AnscCopyString(pBaseObject->Name, ANSC_OBJECT_ARRAY_COMPONENT_NAME);

    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = ANSC_OBJECT_ARRAY_COMPONENT_OID;
    pBaseObject->Create            = AnscObjectArrayCOCreate;
    pBaseObject->Remove            = AnscObjectArrayCORemove;
    pBaseObject->EnrollObjects     = AnscObjectArrayCOEnrollObjects;
    pBaseObject->Initialize        = AnscObjectArrayCOInitialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    return  (ANSC_HANDLE)pMyObject;
}