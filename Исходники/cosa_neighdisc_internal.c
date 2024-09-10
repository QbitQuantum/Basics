ANSC_STATUS
CosaNeighdiscRemove
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus    = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_NEIGHDISC       pMyObject       = (PCOSA_DATAMODEL_NEIGHDISC)hThisObject;
    PSLIST_HEADER                   pNeighdiscIFHead       = (PSLIST_HEADER)&pMyObject->InterfaceList;
    PCOSA_DML_NEIGHDISC_IF_FULL     pNeighdiscInterface    = (PCOSA_DML_NEIGHDISC_IF_FULL)NULL;
    PSINGLE_LINK_ENTRY              pLink           = (PSINGLE_LINK_ENTRY )NULL;
    PSINGLE_LINK_ENTRY              pSubLink        = (PSINGLE_LINK_ENTRY )NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pCosaContext    = (PCOSA_CONTEXT_LINK_OBJECT)NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pSubCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoTemp = (PPOAM_IREP_FOLDER_OBJECT)NULL;

    /*free the back end memory*/
    CosaDmlNeighdiscIfBERemove();

    /* Neighdisc Interface List */
    pLink = AnscSListGetFirstEntry(pNeighdiscIFHead);

    while ( pLink )
    {
        pCosaContext = ACCESS_COSA_CONTEXT_LINK_OBJECT(pLink);
        pLink   = AnscSListGetNextEntry(pLink);

        pNeighdiscInterface = (PCOSA_DML_NEIGHDISC_IF_FULL)pCosaContext->hContext;

        if ( pNeighdiscInterface )
        {
            AnscSListPopEntryByLink(pNeighdiscIFHead, &pCosaContext->Linkage);

            AnscFreeMemory(pNeighdiscInterface);
            AnscFreeMemory(pCosaContext);
        }
    }


    /* Remove self */
    pPoamIrepFoTemp = (PPOAM_IREP_FOLDER_OBJECT)pMyObject->hIrepFolderNeighdiscInterfaceHA;
    if ( pPoamIrepFoTemp )
    {
        pPoamIrepFoTemp->Remove(pPoamIrepFoTemp);
    }

    
    pPoamIrepFoTemp = (PPOAM_IREP_FOLDER_OBJECT)pMyObject->hIrepFolderNeighdiscInterface;
    if ( pPoamIrepFoTemp )
    {
        pPoamIrepFoTemp->Remove(pPoamIrepFoTemp);
    }
 

    AnscFreeMemory((ANSC_HANDLE)pMyObject);

    return returnStatus;
}