ANSC_STATUS
CosaRAInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus    = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_RA              pMyObject       = (PCOSA_DATAMODEL_RA)hThisObject;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoCOSA = (PPOAM_IREP_FOLDER_OBJECT)NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoRAIF = (PPOAM_IREP_FOLDER_OBJECT)NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoRAHA = (PPOAM_IREP_FOLDER_OBJECT)NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoNextIns 
                                                    = (PPOAM_IREP_FOLDER_OBJECT)NULL;
    PSLAP_VARIABLE                  pSlapVariable   = (PSLAP_VARIABLE          )NULL;
    PCOSA_DML_RA_IF_FULL2           pRAInterface    = (PCOSA_DML_RA_IF_FULL2   )NULL;
    PCOSA_DML_RA_OPTION             pRAOption       = (PCOSA_DML_RA_OPTION     )NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pCosaContext    = (PCOSA_CONTEXT_LINK_OBJECT)NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pSubCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)NULL;
    char                            FolderName[32]  = {0};
    ULONG                           ulEntryCount    = 0;
    ULONG                           ulIndex         = 0;
    ULONG                           ulSubEntryCount = 0;
    ULONG                           ulSubIndex      = 0;

    CosaDmlRAInit(NULL, NULL);

    /* Initiation all functions */
    pMyObject->ulInterfaceCount                = 0;
    pMyObject->ulNextInterfaceInsNum           = 1;
    
    AnscSListInitializeHeader(&pMyObject->InterfaceList);

    pMyObject->hIrepFolderCOSA = g_GetRegistryRootFolder(g_pDslhDmlAgent);

    pPoamIrepFoCOSA = (PPOAM_IREP_FOLDER_OBJECT)pMyObject->hIrepFolderCOSA;
    
    if ( !pPoamIrepFoCOSA )
    {
        returnStatus = ANSC_STATUS_FAILURE;
        
        goto  EXIT;
    }

    pPoamIrepFoRAIF = (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoCOSA->GetFolder
                        (
                            (ANSC_HANDLE)pPoamIrepFoCOSA,
                            COSA_IREP_FOLDER_NAME_RAIF
                        );

    if ( !pPoamIrepFoRAIF )
    {
        pPoamIrepFoRAIF = pPoamIrepFoCOSA->AddFolder
                            (
                                (ANSC_HANDLE)pPoamIrepFoCOSA,
                                COSA_IREP_FOLDER_NAME_RAIF,
                                0
                            );
    }

    if ( !pPoamIrepFoRAIF )
    {
        returnStatus = ANSC_STATUS_FAILURE;
        
        goto  EXIT;
    }
    else
    {        
        pMyObject->hIrepFolderRAInterface = (ANSC_HANDLE)pPoamIrepFoRAIF;
    }

    pPoamIrepFoRAHA = (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoRAIF->GetFolder
                        (
                            (ANSC_HANDLE)pPoamIrepFoCOSA,
                            COSA_IREP_FOLDER_NAME_RAIF_HA
                        );

    if ( !pPoamIrepFoRAHA )
    {
        pPoamIrepFoRAHA = pPoamIrepFoRAIF->AddFolder
                            (
                                (ANSC_HANDLE)pPoamIrepFoRAIF,
                                COSA_IREP_FOLDER_NAME_RAIF_HA,
                                0
                            );
    }

    if ( !pPoamIrepFoRAHA )
    {
        returnStatus = ANSC_STATUS_FAILURE;
        
        goto  EXIT;
    }
    else
    {
        pMyObject->hIrepFolderRAInterfaceHA = (ANSC_HANDLE)pPoamIrepFoRAHA;
    }

    /* Retrieve the next Instance Number for RA interface */
    
    if ( TRUE )
    {
        _ansc_sprintf
        (
            FolderName, 
            "%s%d", 
            COSA_DML_RR_NAME_RAIF_NextInsNum,
            0
        );
        
        pPoamIrepFoNextIns = (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoRAIF->GetFolder
                                (
                                    (ANSC_HANDLE)pPoamIrepFoRAIF,
                                    FolderName
                                );

        AnscZeroMemory(FolderName, 32);

        if ( pPoamIrepFoNextIns )
        {
            pSlapVariable = (PSLAP_VARIABLE)pPoamIrepFoNextIns->GetRecord
                                (
                                    (ANSC_HANDLE)pPoamIrepFoNextIns,
                                    COSA_DML_RR_NAME_RAIF_NextInsNum,
                                    NULL
                                );

            if ( pSlapVariable )
            {
                pMyObject->ulNextInterfaceInsNum = pSlapVariable->Variant.varUint32;
                
                SlapFreeVariable(pSlapVariable);
            }

            pPoamIrepFoNextIns->Remove((ANSC_HANDLE)pPoamIrepFoNextIns);
            pPoamIrepFoNextIns = NULL;
        }
    }

    /* Initialize middle layer for Device.RouterAdvertisement.InterfaceSetting.{i}. */

    ulEntryCount = CosaDmlRaIfGetNumberOfEntries(NULL);
    
    for ( ulIndex = 0; ulIndex < ulEntryCount; ulIndex++ )
    {
        pRAInterface = (PCOSA_DML_RA_IF_FULL2)AnscAllocateMemory(sizeof(COSA_DML_RA_IF_FULL2));

        if ( !pRAInterface )
        {
            returnStatus = ANSC_STATUS_RESOURCES;
            
            goto  EXIT;
        }

        AnscSListInitializeHeader(&pRAInterface->OptionList);
        
        pRAInterface->ulNextOptionInsNum = 1;
                
        CosaDmlRaIfGetEntry(NULL, ulIndex,(PCOSA_DML_RA_IF_FULL)pRAInterface);

        if ( TRUE )
        {
            pCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_LINK_OBJECT));

            if ( !pCosaContext )
            {
                AnscFreeMemory(pRAInterface);               
                
                returnStatus = ANSC_STATUS_RESOURCES;
                
                goto  EXIT;
            }

            if ( 0 != pRAInterface->Cfg.InstanceNumber )
            {
                pCosaContext->InstanceNumber = pRAInterface->Cfg.InstanceNumber;
                
                if ( pMyObject->ulNextInterfaceInsNum <=  pRAInterface->Cfg.InstanceNumber )
                {
                    pMyObject->ulNextInterfaceInsNum =  pRAInterface->Cfg.InstanceNumber + 1;

                    if ( 0 == pMyObject->ulNextInterfaceInsNum )
                    {
                        pMyObject->ulNextInterfaceInsNum = 1;
                    }
                }
            }
            else
            {
                pCosaContext->InstanceNumber = pMyObject->ulNextInterfaceInsNum;  
                
                pRAInterface->Cfg.InstanceNumber = pCosaContext->InstanceNumber ;
                
                pMyObject->ulNextInterfaceInsNum++;
                
                if ( 0 == pMyObject->ulNextInterfaceInsNum )
                {
                    pMyObject->ulNextInterfaceInsNum = 1;
                }

                /* Generate Alias */
                _ansc_sprintf(pRAInterface->Cfg.Alias, "Interface%d", (int)pMyObject->ulNextInterfaceInsNum);

                CosaDmlRaIfSetValues
                (
                    NULL,
                    ulIndex,
                    pRAInterface->Cfg.InstanceNumber,
                    pRAInterface->Cfg.Alias
                );
            }

            pCosaContext->hContext      = (ANSC_HANDLE)pRAInterface;            
            pCosaContext->hParentTable  = NULL;            
            pCosaContext->bNew          = FALSE;

            CosaSListPushEntryByInsNum(&pMyObject->InterfaceList, pCosaContext);
                  
        }

        /* Initialize middle layer for Device.RouterAdvertisement.InterfaceSetting.{i}.Option.{i}.  */
        if ( TRUE )
        {
            _ansc_sprintf
            (
                FolderName, 
                "%s%d", 
                COSA_DML_RR_NAME_RAIF_OPTION_NextInsNum, 
                (int)pRAInterface->Cfg.InstanceNumber
            );
            
            pPoamIrepFoNextIns = 
                (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoRAIF->GetFolder
                    (
                        (ANSC_HANDLE)pPoamIrepFoRAIF,
                        FolderName
                    );

            if ( pPoamIrepFoNextIns )
            {
                pSlapVariable =
                    (PSLAP_VARIABLE)pPoamIrepFoNextIns->GetRecord
                        (
                            (ANSC_HANDLE)pPoamIrepFoNextIns,
                            COSA_DML_RR_NAME_RAIF_OPTION_NextInsNum,
                            NULL
                        );

                if ( pSlapVariable )
                {
                    pRAInterface->ulNextOptionInsNum = pSlapVariable->Variant.varUint32;
                    
                    SlapFreeVariable(pSlapVariable);
                }

                pPoamIrepFoNextIns->Remove((ANSC_HANDLE)pPoamIrepFoNextIns);
                pPoamIrepFoNextIns = NULL;
            } 
        }
        
        ulSubEntryCount = CosaDmlRaIfGetNumberOfOptions(NULL, pRAInterface->Cfg.InstanceNumber);

        for ( ulSubIndex = 0; ulSubIndex < ulSubEntryCount; ulSubIndex++ )
        {
            pRAOption = (PCOSA_DML_RA_OPTION)AnscAllocateMemory(sizeof(COSA_DML_RA_OPTION));
        
            if ( !pRAOption )
            {
                returnStatus = ANSC_STATUS_RESOURCES;
                
                goto  EXIT;
            }
        
            CosaDmlRaIfGetOption(NULL, pRAInterface->Cfg.InstanceNumber, ulSubIndex, pRAOption);
        
            if ( TRUE )
            {
                pSubCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_LINK_OBJECT));

                if ( !pSubCosaContext )
                {
                    AnscFreeMemory(pRAOption);

                    returnStatus = ANSC_STATUS_RESOURCES;
                    
                    goto  EXIT;  
                }

                if ( 0 != pRAOption->InstanceNumber )
                {
                    pSubCosaContext->InstanceNumber = pRAOption->InstanceNumber;

                    if ( pRAInterface->ulNextOptionInsNum <= pRAOption->InstanceNumber )
                    {
                        pRAInterface->ulNextOptionInsNum = pRAOption->InstanceNumber + 1;

                        if ( pRAInterface->ulNextOptionInsNum == 0 )
                        {
                            pRAInterface->ulNextOptionInsNum = 1;
                        }
                    }  
                }
                else
                {
                    pSubCosaContext->InstanceNumber = pRAOption->InstanceNumber = pRAInterface->ulNextOptionInsNum;

                    pRAInterface->ulNextOptionInsNum++;

                    if ( pRAInterface->ulNextOptionInsNum == 0 )
                    {
                        pRAInterface->ulNextOptionInsNum = 1;
                    }

                    /* Generate Alias */
                    _ansc_sprintf(pRAOption->Alias, "Option%d", (int)pSubCosaContext->InstanceNumber);

                    /* TODO: Set InstanceNumber Alias back */
                    CosaDmlRaIfSetOptionValues
                    (
                        NULL, 
                        pRAInterface->Cfg.InstanceNumber, 
                        ulSubIndex, 
                        pRAOption->InstanceNumber,
                        pRAOption->Alias
                    );
                }                

                pSubCosaContext->hContext     = (ANSC_HANDLE)pRAOption;
                pSubCosaContext->hParentTable = (ANSC_HANDLE)pRAInterface;
                pSubCosaContext->bNew         = FALSE;

                CosaSListPushEntryByInsNum(&pRAInterface->OptionList, pSubCosaContext);

            }
        }

    }

    CosaRaRegGetInfo((ANSC_HANDLE)pMyObject);

    EXIT:
        
    return returnStatus;
}