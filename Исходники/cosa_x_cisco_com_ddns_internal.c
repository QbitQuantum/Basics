ANSC_STATUS
CosaDdnsRegGetDdnsInfo
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PCOSA_DATAMODEL_DDNS            pMyObject         = (PCOSA_DATAMODEL_DDNS     )hThisObject;
    PSLIST_HEADER                   pListHead         = (PSLIST_HEADER            )&pMyObject->ContextHead;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoDdns   = (PPOAM_IREP_FOLDER_OBJECT )pMyObject->hIrepFolderDdns;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoDdnsSp = (PPOAM_IREP_FOLDER_OBJECT )NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pCosaContext      = (PCOSA_CONTEXT_LINK_OBJECT)NULL;
    PCOSA_DML_DDNS_SERVICE          pDdnsService      = (PCOSA_DML_DDNS_SERVICE   )NULL;
    PSINGLE_LINK_ENTRY              pSLinkEntry       = (PSINGLE_LINK_ENTRY       )NULL;
    PSLAP_VARIABLE                  pSlapVariable     = (PSLAP_VARIABLE           )NULL;
    ULONG                           ulEntryCount      = 0;
    ULONG                           ulIndex           = 0;
    ULONG                           ulInstanceNumber  = 0;
    char*                           pFolderName       = NULL;
    char*                           pAlias            = NULL;

    if ( !pPoamIrepFoDdns )
    {
        return ANSC_STATUS_FAILURE;
    }

    /* Load the newly added but not yet commited entries */

    ulEntryCount = pPoamIrepFoDdns->GetFolderCount((ANSC_HANDLE)pPoamIrepFoDdns);

    for ( ulIndex = 0; ulIndex < ulEntryCount; ulIndex++ )
    {
        pFolderName =
            pPoamIrepFoDdns->EnumFolder
                (
                    (ANSC_HANDLE)pPoamIrepFoDdns,
                    ulIndex
                );

        if ( !pFolderName )
        {
            continue;
        }

        pPoamIrepFoDdnsSp = pPoamIrepFoDdns->GetFolder((ANSC_HANDLE)pPoamIrepFoDdns, pFolderName);

        AnscFreeMemory(pFolderName);

        if ( !pPoamIrepFoDdnsSp )
        {
            continue;
        }

        if ( TRUE )
        {
            pSlapVariable =
                (PSLAP_VARIABLE)pPoamIrepFoDdnsSp->GetRecord
                    (
                        (ANSC_HANDLE)pPoamIrepFoDdnsSp,
                        COSA_DML_RR_NAME_DdnsServiceInsNum,
                        NULL
                    );

            if ( pSlapVariable )
            {
                ulInstanceNumber = pSlapVariable->Variant.varUint32;

                SlapFreeVariable(pSlapVariable);
            }
        }

        if ( TRUE )
        {
            pSlapVariable =
                (PSLAP_VARIABLE)pPoamIrepFoDdnsSp->GetRecord
                    (
                        (ANSC_HANDLE)pPoamIrepFoDdnsSp,
                        COSA_DML_RR_NAME_DdnsServiceAlias,
                        NULL
                    );

            if ( pSlapVariable )
            {
                pAlias = AnscCloneString(pSlapVariable->Variant.varString);

                SlapFreeVariable(pSlapVariable);
            }

            if ( pAlias == NULL )
            {
                continue;
            }
        }

        pPoamIrepFoDdnsSp->Remove((ANSC_HANDLE)pPoamIrepFoDdnsSp);

        pCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_LINK_OBJECT));

        if ( !pCosaContext )
        {
            AnscFreeMemory(pAlias);

            return ANSC_STATUS_RESOURCES;
        }

        pDdnsService = (PCOSA_DML_DDNS_SERVICE)AnscAllocateMemory(sizeof(COSA_DML_DDNS_SERVICE));

        if ( !pDdnsService )
        {
            AnscFreeMemory(pCosaContext);
            AnscFreeMemory(pAlias);

            return ANSC_STATUS_RESOURCES;
        }

        pDdnsService->InstanceNumber = ulInstanceNumber;
        AnscCopyString(pDdnsService->Alias, pAlias);

        AnscFreeMemory(pAlias);

        pCosaContext->InstanceNumber   = ulInstanceNumber;
        pCosaContext->bNew             = TRUE;
        pCosaContext->hContext         = (ANSC_HANDLE)pDdnsService;
        pCosaContext->hParentTable     = NULL;
        pCosaContext->hPoamIrepUpperFo = (ANSC_HANDLE)pPoamIrepFoDdns;
        pCosaContext->hPoamIrepFo      = (ANSC_HANDLE)pPoamIrepFoDdnsSp;

        CosaSListPushEntryByInsNum(pListHead, pCosaContext);    
    }

    return ANSC_STATUS_SUCCESS;
}