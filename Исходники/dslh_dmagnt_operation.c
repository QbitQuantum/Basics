ANSC_STATUS
DslhDmagntEngage
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus           = ANSC_STATUS_SUCCESS;
    PDSLH_DATAMODEL_AGENT_OBJECT    pMyObject              = (PDSLH_DATAMODEL_AGENT_OBJECT)hThisObject;
    PANSC_ATOM_TABLE_OBJECT         pAtomFunctions         = (PANSC_ATOM_TABLE_OBJECT)pMyObject->hAtomFunctions;
    PDSLH_CPE_CONTROLLER_OBJECT     pDslhCpeController     = (PDSLH_CPE_CONTROLLER_OBJECT)pMyObject->hDslhCpeController;
    PSLAP_OBJECT_DESCRIPTOR         pObjDescriptor         = (PSLAP_OBJECT_DESCRIPTOR    )NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoRoot        = (PPOAM_IREP_FOLDER_OBJECT   )NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoProvision   = (PPOAM_IREP_FOLDER_OBJECT   )NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoCOSA        = (PPOAM_IREP_FOLDER_OBJECT   )pMyObject->hIrepFolderCOSA;

    PDSLH_MWS_INTERFACE             pDslhMwsIf             = (PDSLH_MWS_INTERFACE        )pMyObject->hDslhMwsIf;

    if ( pMyObject->bActive )
    {
        return  ANSC_STATUS_SUCCESS;
    }

    if( pDslhMwsIf != NULL)
    {
        pDslhCpeController->AddInterface(pDslhCpeController, pMyObject->hDslhMwsIf);
    }

    pMyObject->hDslhCcdIf = pDslhCpeController->GetInterfaceByName(pDslhCpeController, CCSP_CCD_INTERFACE_NAME);
    pMyObject->hDslhLcbIf = pDslhCpeController->GetInterfaceByName(pDslhCpeController, CCSP_LIBCBK_INTERFACE_NAME);

    /* register internal apis */
    if( pAtomFunctions == NULL)
    {
        pMyObject->hAtomFunctions =
            AnscCreateAtomTable
                (
                    pMyObject->hContainerContext,
                    (ANSC_HANDLE)pMyObject,
                    NULL
                );

        pAtomFunctions    = (PANSC_ATOM_TABLE_OBJECT)pMyObject->hAtomFunctions;
    }

    if( pAtomFunctions != NULL)
    {                                                                                         
        /* Register the API exported by framework */
        pMyObject->RegisterInternalApi(pMyObject, "COSANotifyValueChange",            COSANotifyValueChange);
        pMyObject->RegisterInternalApi(pMyObject, "COSANotifyDiagComplete",           COSANotifyDiagComplete);
        pMyObject->RegisterInternalApi(pMyObject, "COSAValidateHierarchyInterface",   COSAValidateHierarchyInterface);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetParamValueBool",            COSAGetParamValueBool);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetParamValueInt",             COSAGetParamValueInt);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetParamValueUlong",           COSAGetParamValueUlong);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetParamValueString",          COSAGetParamValueString);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetParamValue",                COSAGetParamValue);
        pMyObject->RegisterInternalApi(pMyObject, "COSASetParamValueBool",            COSASetParamValueBool);
        pMyObject->RegisterInternalApi(pMyObject, "COSASetParamValueInt",             COSASetParamValueInt);
        pMyObject->RegisterInternalApi(pMyObject, "COSASetParamValueUlong",           COSASetParamValueUlong);
        pMyObject->RegisterInternalApi(pMyObject, "COSASetParamValueString",          COSASetParamValueString);

        pMyObject->RegisterInternalApi(pMyObject, "COSAGetRegistryRootFolder",        COSAGetRegistryRootFolder);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetInstanceNumberByIndex",     COSAGetInstanceNumberByIndex);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetInterfaceByName",           COSAGetInterfaceByName);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetMessageBusHandle",          COSAGetMessageBusHandle);
        pMyObject->RegisterInternalApi(pMyObject, "COSARegisterCallBackAfterInitDml", COSARegisterCallBackAfterInitDml);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetSubsystemPrefix",           COSAGetSubsystemPrefix);
        pMyObject->RegisterInternalApi(pMyObject, "COSARepopulateTable",              COSARepopulateTable);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetParamValueByPathName",      COSAGetParamValueByPathName);
        pMyObject->RegisterInternalApi(pMyObject, "COSASetParamValueByPathName",      COSASetParamValueByPathName);
        pMyObject->RegisterInternalApi(pMyObject, "COSAGetInstanceNumbers",           COSAGetInstanceNumbers);

        /* Register the API  for CCSP Common Components*/
#if 0
        pMyObject->RegisterInternalApi(pMyObject, "CcspComp_GetParamUlongValue",      CcspComp_GetParamUlongValue);
        pMyObject->RegisterInternalApi(pMyObject, "CcspComp_GetParamStringValue",     CcspComp_GetParamStringValue);
#endif
        pMyObject->RegisterInternalApi(pMyObject, "CcspComp_GetBulkParamValues",      CcspComp_GetBulkParamValues);
        pMyObject->RegisterInternalApi(pMyObject, "CcspComp_SetParamBoolValue",       CcspComp_SetParamBoolValue);

        pMyObject->RegisterInternalApi(pMyObject, "CcspLog_GetParamBoolValue",        CcspLog_GetParamBoolValue);
        pMyObject->RegisterInternalApi(pMyObject, "CcspLog_GetParamUlongValue",       CcspLog_GetParamUlongValue);
        pMyObject->RegisterInternalApi(pMyObject, "CcspLog_SetParamBoolValue",        CcspLog_SetParamBoolValue);
        pMyObject->RegisterInternalApi(pMyObject, "CcspLog_SetParamUlongValue",       CcspLog_SetParamUlongValue);
        pMyObject->RegisterInternalApi(pMyObject, "CcspLog_Validate",                 CcspLog_Validate );
        pMyObject->RegisterInternalApi(pMyObject, "CcspLog_Commit",                   CcspLog_Commit );
        pMyObject->RegisterInternalApi(pMyObject, "CcspLog_Rollback",                 CcspLog_Rollback );
        pMyObject->RegisterInternalApi(pMyObject, "CcspMem_GetParamUlongValue",       CcspMem_GetParamUlongValue);
        pMyObject->RegisterInternalApi(pMyObject, "CcspLog_GetBulkParamValues",       CcspLog_GetBulkParamValues);
        pMyObject->RegisterInternalApi(pMyObject, "CcspLog_SetBulkParamValues",       CcspLog_SetBulkParamValues);

    }

    /*
     * Enroll and create PoamIrepFolder object.
     */
    if ( TRUE )
    {

        pPoamIrepFoRoot =
            (PPOAM_IREP_FOLDER_OBJECT)PoamIrepFoCreate(NULL, NULL, ""); 

        if ( !pPoamIrepFoRoot )
        {
            AnscTrace("DslhDataModelAgent: Cannot access Root Folder!!\n");

            returnStatus = ANSC_STATUS_FAILURE;

            goto  EXIT2;
        }

        pPoamIrepFoProvision =
            (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoRoot->GetFolder
                (
                    (ANSC_HANDLE)pPoamIrepFoRoot,
                    "Provision"
                );

        if ( !pPoamIrepFoProvision )
        {
            AnscTrace("DslhDataModelAgent: Cannot access /Configuration/Provision folder!!\n");

            returnStatus = ANSC_STATUS_FAILURE;

            goto  EXIT3;
        }

        pPoamIrepFoCOSA =
            (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoProvision->GetFolder
                (
                    (ANSC_HANDLE)pPoamIrepFoProvision,
                    COSA_IREP_FOLDER_NAME
                );

        if ( !pPoamIrepFoCOSA )
        {
            pPoamIrepFoCOSA =
                pPoamIrepFoProvision->AddFolder
                    (
                        (ANSC_HANDLE)pPoamIrepFoProvision,
                        COSA_IREP_FOLDER_NAME,
                        0
                    );
        }

        if ( !pPoamIrepFoCOSA )
        {
            AnscTrace("DslhDataModelAgent: Cannot access /Configuration/Provision/%s folder!!\n", COSA_IREP_FOLDER_NAME);

            returnStatus = ANSC_STATUS_FAILURE;

            goto  EXIT4;
        }
        else
        {
            pMyObject->hIrepFolderCOSA = (ANSC_HANDLE)pPoamIrepFoCOSA;
        }
    }

    pMyObject->bActive = TRUE;

    returnStatus = ANSC_STATUS_SUCCESS;


    /******************************************************************
                GRACEFUL ROLLBACK PROCEDURES AND EXIT DOORS
    ******************************************************************/

EXIT4:

    if ( pPoamIrepFoProvision )
    {
        pPoamIrepFoProvision->Remove((ANSC_HANDLE)pPoamIrepFoProvision);
    }

EXIT3:

    if ( pPoamIrepFoRoot )
    {
        pPoamIrepFoRoot->Remove((ANSC_HANDLE)pPoamIrepFoRoot);
    }

EXIT2:

    return  returnStatus;
}