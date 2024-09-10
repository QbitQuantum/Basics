ANSC_STATUS
CosaBridgingInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus        = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_BRIDGING        pMyObject           = (PCOSA_DATAMODEL_BRIDGING)hThisObject;
    PSLAP_VARIABLE                  pSlapVariable       = (PSLAP_VARIABLE             )NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoCOSA     = (PPOAM_IREP_FOLDER_OBJECT   )NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoBRG      = (PPOAM_IREP_FOLDER_OBJECT   )NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoBRGHA    = (PPOAM_IREP_FOLDER_OBJECT   )NULL;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoNextIns  = (PPOAM_IREP_FOLDER_OBJECT   )NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pCosaContext        = (PCOSA_CONTEXT_LINK_OBJECT  )NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pCosaContext2       = (PCOSA_CONTEXT_LINK_OBJECT  )NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pCosaContext3       = (PCOSA_CONTEXT_LINK_OBJECT  )NULL;
    PCOSA_DML_BRG_FULL_ALL          pDmlBridge          = (PCOSA_DML_BRG_FULL_ALL     )NULL;
    PCOSA_DML_BRG_PORT_FULL         pPort               = (PCOSA_DML_BRG_PORT_FULL    )NULL;
    ULONG                           ulBridgeCount       = 0;
    ULONG                           ulSubCount          = 0;
    ULONG                           ulIndex             = 0;
    ULONG                           ulSubIndex          = 0;
    char                            FolderName[32]      = {0};
    PCOSA_DML_BRG_VLAN_FULL         pVLAN           = (PCOSA_DML_BRG_VLAN_FULL  )NULL;

    /* Initiation all functions */

//$HL 4/24/2013
    pMyObject->ulNextBridgeInstance = 1;

	AnscSListInitializeHeader(&pMyObject->BridgeList);

    //$HL 4/25/2013
    pMyObject->BridgeList.Depth = 0;
    
    pMyObject->hIrepFolderCOSA = g_GetRegistryRootFolder(g_pDslhDmlAgent);

    pPoamIrepFoCOSA = (PPOAM_IREP_FOLDER_OBJECT)pMyObject->hIrepFolderCOSA;

    if ( !pPoamIrepFoCOSA )
    {
        returnStatus = ANSC_STATUS_FAILURE;

        goto EXIT;
    }

    pPoamIrepFoBRG =
        (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoCOSA->GetFolder
            (
			    (ANSC_HANDLE)pPoamIrepFoCOSA,
                COSA_IREP_FOLDER_NAME_BRIDGING
            );

    if ( !pPoamIrepFoBRG )
    {
        pPoamIrepFoBRG =
            pPoamIrepFoCOSA->AddFolder
                (
                    (ANSC_HANDLE)pPoamIrepFoCOSA,
                    COSA_IREP_FOLDER_NAME_BRIDGING,
                    0
                );
    }

    if ( !pPoamIrepFoBRG )
    {
        returnStatus = ANSC_STATUS_FAILURE;

        goto  EXIT;
    }
    else
    {
        pMyObject->hIrepFolderBRG = (ANSC_HANDLE)pPoamIrepFoBRG;
    }

    pPoamIrepFoBRGHA = 
        (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoBRG->GetFolder
            (
                (ANSC_HANDLE)pPoamIrepFoCOSA,
                COSA_IREP_FOLDER_NAME_BRIDGINGHA
            );

    if ( !pPoamIrepFoBRGHA )
    {
        pPoamIrepFoBRGHA =
            pPoamIrepFoBRG->AddFolder
                (
                    (ANSC_HANDLE)pPoamIrepFoBRG,
                    COSA_IREP_FOLDER_NAME_BRIDGINGHA,
                    0
                );
    }

    if ( !pPoamIrepFoBRGHA )
    {
        returnStatus = ANSC_STATUS_FAILURE;

        goto  EXIT;
    }
    else
    {
        pMyObject->hIrepFolderBRGHA = (ANSC_HANDLE)pPoamIrepFoBRGHA;
    }

    if ( TRUE )
    {
        _ansc_sprintf
        (
            FolderName, 
            "%s%d", 
            COSA_DML_RR_NAME_Bridge_NextInsNunmber,
            0
        );
        
        pPoamIrepFoNextIns = (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoBRG->GetFolder
                                (
                                    (ANSC_HANDLE)pPoamIrepFoBRG,
                                    FolderName
                                );

        AnscZeroMemory(FolderName, 32);

        if ( pPoamIrepFoNextIns )
        {
            pSlapVariable = (PSLAP_VARIABLE)pPoamIrepFoNextIns->GetRecord
                                (
                                    (ANSC_HANDLE)pPoamIrepFoNextIns,
                                    COSA_DML_RR_NAME_Bridge_NextInsNunmber,
                                    NULL
                                );

            if ( pSlapVariable )
            {
                pMyObject->ulNextBridgeInstance = pSlapVariable->Variant.varUint32;
                
                SlapFreeVariable(pSlapVariable);
            }

            pPoamIrepFoNextIns->Remove((ANSC_HANDLE)pPoamIrepFoNextIns);
            pPoamIrepFoNextIns = NULL;
        }
    }

    ulBridgeCount = CosaDmlBrgGetNumberOfEntries(NULL);

    for ( ulIndex = 0; ulIndex < ulBridgeCount; ulIndex++ )
    {
        pDmlBridge = (PCOSA_DML_BRG_FULL_ALL)AnscAllocateMemory(sizeof(COSA_DML_BRG_FULL_ALL));
        _ansc_memset(pDmlBridge, 0, sizeof(COSA_DML_BRG_FULL_ALL));
        if ( !pDmlBridge )
        {
            returnStatus = ANSC_STATUS_RESOURCES;

            goto EXIT;
        }

        AnscSListInitializeHeader(&pDmlBridge->PortList);
        AnscSListInitializeHeader(&pDmlBridge->VLANList);
        AnscSListInitializeHeader(&pDmlBridge->VLANPortList);

        pDmlBridge->ulNextPortInsNum = 1;
        pDmlBridge->ulNextVLANInsNum = 1;
        pDmlBridge->ulNextVLANPortInsNum = 1;

        //$HL 4/25/2013
        if (CosaDmlBrgGetEntry(NULL, ulIndex, (PCOSA_DML_BRG_FULL)pDmlBridge)!= ANSC_STATUS_SUCCESS)
        {
            AnscFreeMemory(pDmlBridge);
            break;    
        }
        else
        //if ( TRUE )
        {
            pCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_LINK_OBJECT));
            _ansc_memset(pCosaContext, 0, sizeof(COSA_CONTEXT_LINK_OBJECT));
            if ( !pCosaContext )
            {
                AnscFreeMemory(pDmlBridge);

                returnStatus = ANSC_STATUS_RESOURCES;

                AnscTraceFlow(("<HL>%s cannot allocate pCosaContext\n", __FUNCTION__));
                goto  EXIT;
            }
            
            if ( pDmlBridge->Cfg.InstanceNumber !=0 )
            {
                pCosaContext->InstanceNumber = pDmlBridge->Cfg.InstanceNumber;

                if ( pMyObject->ulNextBridgeInstance <= pDmlBridge->Cfg.InstanceNumber )
                {
                    pMyObject->ulNextBridgeInstance = pDmlBridge->Cfg.InstanceNumber + 1;

                    if ( pMyObject->ulNextBridgeInstance == 0 )
                    {
                        pMyObject->ulNextBridgeInstance = 1;
                    }
                }
            }
            else
            {
                pDmlBridge->Cfg.InstanceNumber = pCosaContext->InstanceNumber = pMyObject->ulNextBridgeInstance;

                pMyObject->ulNextBridgeInstance++;

                if ( pMyObject->ulNextBridgeInstance == 0)
                {
                    pMyObject->ulNextBridgeInstance = 1;
                }

                _ansc_sprintf(pDmlBridge->Cfg.Alias, "DmlBridge%d", pMyObject->ulNextBridgeInstance);

                CosaDmlBrgSetValues(NULL, ulIndex, pDmlBridge->Cfg.InstanceNumber, pDmlBridge->Cfg.Alias);
            }

            pCosaContext->hContext     = (ANSC_HANDLE)pDmlBridge;
            pCosaContext->hParentTable = NULL;
            pCosaContext->bNew         = FALSE;
            //$HL 4/29/2013
            //pCosaContext->hPoamIrepUpperFo = NULL;
            CosaSListPushEntryByInsNum(&pMyObject->BridgeList, pCosaContext);
        }

        /* Port */
        
        if ( TRUE )
        {
            _ansc_sprintf
                (
                    FolderName, 
                    "%s%d", 
                    COSA_DML_RR_NAME_Bridge_Port_NextInsNumber, 
                    pDmlBridge->Cfg.InstanceNumber
                );

            pPoamIrepFoNextIns = 
                (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoBRG->GetFolder
                    (
                        (ANSC_HANDLE)pPoamIrepFoBRG,
                        FolderName
                    );

            if ( pPoamIrepFoNextIns )
            {
                pSlapVariable =
                    (PSLAP_VARIABLE)pPoamIrepFoNextIns->GetRecord
                        (
                            (ANSC_HANDLE)pPoamIrepFoNextIns,
                            COSA_DML_RR_NAME_Bridge_Port_NextInsNumber,
                            NULL
                        );

                if ( pSlapVariable )
                {
                    
                    pDmlBridge->ulNextPortInsNum = pSlapVariable->Variant.varUint32;
                    SlapFreeVariable(pSlapVariable);
                }
                else
                {
                    AnscTraceFlow(("<HL>%s pSlapVariable == NULL\n", __FUNCTION__));
                }

                pPoamIrepFoNextIns->Remove((ANSC_HANDLE)pPoamIrepFoNextIns);
                pPoamIrepFoNextIns = NULL;
            }
            else
            {
                AnscTraceFlow(("<HL>%s pPoamIrepFoNextIns == NULL\n", __FUNCTION__));
            }            
        }

        ulSubCount = CosaDmlBrgPortGetNumberOfEntries(NULL, pDmlBridge->Cfg.InstanceNumber);

        for ( ulSubIndex = 0; ulSubIndex < ulSubCount; ulSubIndex++ )
        {
            pPort = (PCOSA_DML_BRG_PORT_FULL)AnscAllocateMemory(sizeof(COSA_DML_BRG_PORT_FULL));

            if ( !pPort )
            {
                returnStatus = ANSC_STATUS_RESOURCES;

                goto EXIT;
            }

            _ansc_memset(pPort, 0, sizeof(COSA_DML_BRG_PORT_FULL));

            if(CosaDmlBrgPortGetEntry(NULL, pDmlBridge->Cfg.InstanceNumber, ulSubIndex, pPort)
                != ANSC_STATUS_SUCCESS)
            {
                AnscFreeMemory(pPort);
                break;
            }
            else 
            {
                pCosaContext2 = (PCOSA_CONTEXT_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_LINK_OBJECT));

                if ( !pCosaContext2 )
                {  
                    AnscFreeMemory(pPort);
                    returnStatus = ANSC_STATUS_RESOURCES;
                    AnscTraceFlow(("<$HL> %s bridge instance:%d cannot allocate any memory for pCosaContext2\n",__FUNCTION__,
                        pDmlBridge->Cfg.InstanceNumber));
                    AnscFreeMemory(pPort);
                    goto EXIT;
                }

                _ansc_memset(pCosaContext2, 0, sizeof(COSA_CONTEXT_LINK_OBJECT));

                if ( pPort->Cfg.InstanceNumber != 0 )
                {
                    pCosaContext2->InstanceNumber = pPort->Cfg.InstanceNumber;

                    if ( pDmlBridge->ulNextPortInsNum <= pPort->Cfg.InstanceNumber )
                    {
                        pDmlBridge->ulNextPortInsNum = pPort->Cfg.InstanceNumber + 1;

                        if ( pDmlBridge->ulNextPortInsNum == 0 )
                        {
                            pDmlBridge->ulNextPortInsNum = 1;
                        }
                    }
                }
                else
                {
                    pCosaContext2->InstanceNumber = pPort->Cfg.InstanceNumber = pDmlBridge->ulNextPortInsNum;

                    pDmlBridge->ulNextPortInsNum++;

                    if ( pDmlBridge->ulNextPortInsNum == 0 )
                    {
                        pDmlBridge->ulNextPortInsNum = 1;
                    }

                    _ansc_sprintf(pPort->Cfg.Alias, "Port%d", pCosaContext2->InstanceNumber);

                    CosaDmlBrgPortSetValues
                        (
                            NULL,
                            pDmlBridge->Cfg.InstanceNumber,
                            ulSubIndex,
                            pPort->Cfg.InstanceNumber,
                            pPort->Cfg.Alias
                        );
                }

                pCosaContext2->hContext     = (ANSC_HANDLE)pPort;
                pCosaContext2->hParentTable = (ANSC_HANDLE)pDmlBridge;
                pCosaContext2->bNew         = FALSE;

                CosaSListPushEntryByInsNum(&pDmlBridge->PortList, pCosaContext2);
            }
        }
    

        //$HL 7/3/2013
        /* VLAN */
        
        if ( TRUE )
        {
            _ansc_sprintf
                (
                    FolderName, 
                    "%s%d", 
                    COSA_DML_RR_NAME_Bridge_VLAN_NextInsNumber, 
                    pDmlBridge->Cfg.InstanceNumber
                );

            pPoamIrepFoNextIns = 
                (PPOAM_IREP_FOLDER_OBJECT)pPoamIrepFoBRG->GetFolder
                    (
                        (ANSC_HANDLE)pPoamIrepFoBRG,
                        FolderName
                    );

            if ( pPoamIrepFoNextIns )
            {
                pSlapVariable =
                    (PSLAP_VARIABLE)pPoamIrepFoNextIns->GetRecord
                        (
                            (ANSC_HANDLE)pPoamIrepFoNextIns,
                            COSA_DML_RR_NAME_Bridge_VLAN_NextInsNumber,
                            NULL
                        );

                if ( pSlapVariable )
                {
                    
                    pDmlBridge->ulNextVLANInsNum = pSlapVariable->Variant.varUint32;
                    SlapFreeVariable(pSlapVariable);
                }
                else
                {
                    AnscTraceFlow(("<HL>%s pSlapVariable == NULL\n", __FUNCTION__));
                }

                pPoamIrepFoNextIns->Remove((ANSC_HANDLE)pPoamIrepFoNextIns);
                pPoamIrepFoNextIns = NULL;
            }
            else
            {
                AnscTraceFlow(("<HL>%s pPoamIrepFoNextIns == NULL\n", __FUNCTION__));
            }            
        }

        ulSubCount = CosaDmlBrgVlanGetNumberOfEntries(NULL, pDmlBridge->Cfg.InstanceNumber);

        for ( ulSubIndex = 0; ulSubIndex < ulSubCount; ulSubIndex++ )
        {
            pVLAN = (PCOSA_DML_BRG_VLAN_FULL)AnscAllocateMemory(sizeof(COSA_DML_BRG_VLAN_FULL));

            if ( !pVLAN )
            {
                returnStatus = ANSC_STATUS_RESOURCES;

                goto EXIT;
            }

            _ansc_memset(pVLAN, 0, sizeof(COSA_DML_BRG_VLAN_FULL));

            if(CosaDmlBrgVlanGetEntry(NULL, pDmlBridge->Cfg.InstanceNumber, ulSubIndex, pVLAN)
                != ANSC_STATUS_SUCCESS)
            {
                AnscFreeMemory(pVLAN);
                break;
            }
            else 
            {
                pCosaContext3 = (PCOSA_CONTEXT_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_LINK_OBJECT));

                if ( !pCosaContext3 )
                {  
                    returnStatus = ANSC_STATUS_RESOURCES;
                    AnscTraceFlow(("<$HL> %s bridge instance:%d cannot allocate any memory for pCosaContext3\n",__FUNCTION__,
                        pDmlBridge->Cfg.InstanceNumber));
                    AnscFreeMemory(pVLAN);
                    goto EXIT;
                }

                _ansc_memset(pCosaContext3, 0, sizeof(COSA_CONTEXT_LINK_OBJECT));

                if ( pVLAN->Cfg.InstanceNumber != 0 )
                {
                    pCosaContext3->InstanceNumber = pVLAN->Cfg.InstanceNumber;

                    if ( pDmlBridge->ulNextVLANInsNum <= pVLAN->Cfg.InstanceNumber )
                    {
                        pDmlBridge->ulNextVLANInsNum = pVLAN->Cfg.InstanceNumber + 1;

                        if ( pDmlBridge->ulNextVLANInsNum == 0 )
                        {
                            pDmlBridge->ulNextVLANInsNum = 1;
                        }
                    }
                }
                else
                {
                    pCosaContext2->InstanceNumber = pVLAN->Cfg.InstanceNumber = pDmlBridge->ulNextPortInsNum;

                    pDmlBridge->ulNextVLANInsNum++;

                    if ( pDmlBridge->ulNextVLANInsNum == 0 )
                    {
                        pDmlBridge->ulNextVLANInsNum = 1;
                    }

                    _ansc_sprintf(pVLAN->Cfg.Alias, "VLAN%d", pCosaContext2->InstanceNumber);

                    CosaDmlBrgVlanSetValues //new sbAPI
                        (
                            NULL,
                            pDmlBridge->Cfg.InstanceNumber,
                            ulSubIndex,
                            pVLAN->Cfg.InstanceNumber,
                            pVLAN->Cfg.Alias
                        );
                }

                pCosaContext3->hContext     = (ANSC_HANDLE)pVLAN;
                pCosaContext3->hParentTable = (ANSC_HANDLE)pDmlBridge;
                pCosaContext3->bNew         = FALSE;

                CosaSListPushEntryByInsNum(&pDmlBridge->VLANList, pCosaContext3);
            }
        }
    }
    //$HL 4/29/2013
    CosaBridgingRegGetInfo((ANSC_HANDLE)pMyObject);

EXIT:

    return returnStatus;
}