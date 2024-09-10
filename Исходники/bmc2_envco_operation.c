ANSC_STATUS
Bmc2EnvcoCloseEnv
(
    ANSC_HANDLE                 hThisObject
)
{
    ANSC_STATUS                     returnStatus   = ANSC_STATUS_SUCCESS;
    PBMC2_ENV_CONTROLLER_OBJECT     pMyObject      = (PBMC2_ENV_CONTROLLER_OBJECT)hThisObject;
    PSLAP_GOA_INTERFACE             pSlapGoaIf     = (PSLAP_GOA_INTERFACE        )pMyObject->hSlapGoaIf;
    PSLAP_OBJECT_DESCRIPTOR         pObjDescriptor = (PSLAP_OBJECT_DESCRIPTOR    )NULL;

    if ( TRUE )
    {
        returnStatus =
            pSlapGoaIf->DeleteContainer
            (
                pSlapGoaIf->hOwnerContext,
                pMyObject->hSlapContainerApp
            );
    }

    if ( TRUE )
    {
        pObjDescriptor = (PSLAP_OBJECT_DESCRIPTOR)SlapBmc2AppoGetSlapObjDescriptor(pMyObject->hContainerContext);
        returnStatus   =
            pSlapGoaIf->UnbindObjDescriptor
            (
                pSlapGoaIf->hOwnerContext,
                pObjDescriptor->ObjName
            );
    }

    if ( TRUE )
    {
        pObjDescriptor = (PSLAP_OBJECT_DESCRIPTOR)SlapBmc2SrvoGetSlapObjDescriptor(pMyObject->hContainerContext);
        returnStatus   =
            pSlapGoaIf->UnbindObjDescriptor
            (
                pSlapGoaIf->hOwnerContext,
                pObjDescriptor->ObjName
            );
    }

    if ( TRUE )
    {
        pObjDescriptor = (PSLAP_OBJECT_DESCRIPTOR)SlapBmc2TermoGetSlapObjDescriptor(pMyObject->hContainerContext);
        returnStatus   =
            pSlapGoaIf->UnbindObjDescriptor
            (
                pSlapGoaIf->hOwnerContext,
                pObjDescriptor->ObjName
            );
    }

    if ( TRUE )
    {
        pObjDescriptor = (PSLAP_OBJECT_DESCRIPTOR)SlapBmc2DomoGetSlapObjDescriptor(pMyObject->hContainerContext);
        returnStatus   =
            pSlapGoaIf->UnbindObjDescriptor
            (
                pSlapGoaIf->hOwnerContext,
                pObjDescriptor->ObjName
            );
    }

    if ( TRUE )
    {
        pObjDescriptor = (PSLAP_OBJECT_DESCRIPTOR)SlapBmc2ComoGetSlapObjDescriptor(pMyObject->hContainerContext);
        returnStatus   =
            pSlapGoaIf->UnbindObjDescriptor
            (
                pSlapGoaIf->hOwnerContext,
                pObjDescriptor->ObjName
            );
    }

    if ( TRUE )
    {
        pObjDescriptor = (PSLAP_OBJECT_DESCRIPTOR)SlapBmc2OutoGetSlapObjDescriptor(pMyObject->hContainerContext);
        returnStatus   =
            pSlapGoaIf->UnbindObjDescriptor
            (
                pSlapGoaIf->hOwnerContext,
                pObjDescriptor->ObjName
            );
    }

    if ( TRUE )
    {
        pObjDescriptor = (PSLAP_OBJECT_DESCRIPTOR)SlapBmc2InoGetSlapObjDescriptor(pMyObject->hContainerContext);
        returnStatus   =
            pSlapGoaIf->UnbindObjDescriptor
            (
                pSlapGoaIf->hOwnerContext,
                pObjDescriptor->ObjName
            );
    }

    if ( pMyObject->hSlapVarEntity )
    {
        returnStatus =
            pSlapGoaIf->DeleteObject
            (
                pSlapGoaIf->hOwnerContext,
                pMyObject->hSlapVarEntity
            );
    }

    if ( pMyObject->hSlapVarConverter )
    {
        returnStatus =
            pSlapGoaIf->DeleteObject
            (
                pSlapGoaIf->hOwnerContext,
                pMyObject->hSlapVarConverter
            );
    }

    return  ANSC_STATUS_SUCCESS;
}