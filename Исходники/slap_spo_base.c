ANSC_STATUS
SlapSpoRemove
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSLAP_SRV_PROXY_OBJECT          pMyObject    = (PSLAP_SRV_PROXY_OBJECT)hThisObject;
    PSLAP_GOA_INTERFACE             pSlapGoaIf   = (PSLAP_GOA_INTERFACE   )pMyObject->hSlapGoaIf;

    pMyObject->Cancel((ANSC_HANDLE)pMyObject);
    pMyObject->Reset ((ANSC_HANDLE)pMyObject);

    switch ( pMyObject->ObjMode )
    {
        case    SLAP_SPO_OBJ_MODE_acquired :

                if ( pMyObject->hSlapGoaObj )
                {
                    returnStatus =
                        pSlapGoaIf->RelObjectAccess
                            (
                                pSlapGoaIf->hOwnerContext,
                                pMyObject->hSlapGoaObj
                            );
                }

                break;

        case    SLAP_SPO_OBJ_MODE_referenced :

                break;

        case    SLAP_SPO_OBJ_MODE_created :

                if ( pMyObject->hSlapGoaObj )
                {
                    returnStatus =
                        pSlapGoaIf->DeleteObject
                            (
                                pSlapGoaIf->hOwnerContext,
                                pMyObject->hSlapGoaObj
                            );
                }

                break;

        default :

                break;
    }

    if ( pMyObject->ObjName )
    {
        AnscFreeMemory(pMyObject->ObjName);

        pMyObject->ObjName = NULL;
    }

    AnscLcoRemove((ANSC_HANDLE)pMyObject);

    return  ANSC_STATUS_SUCCESS;
}