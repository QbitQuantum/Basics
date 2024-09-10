ANSC_STATUS
CosaNatRegGetNatInfo
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus      = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_NAT             pMyObject         = ( PCOSA_DATAMODEL_NAT )hThisObject;

    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoNat      = (PPOAM_IREP_FOLDER_OBJECT )pMyObject->hIrepFolderNat;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoNatPt    = (PPOAM_IREP_FOLDER_OBJECT )pMyObject->hIrepFolderNatPt;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoEnumNat  = (PPOAM_IREP_FOLDER_OBJECT )NULL;
    PCOSA_CONTEXT_PMAPPING_LINK_OBJECT     pCosaNatContext   = NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pCosaNatPtContext   = NULL;
    PCOSA_DML_NAT_PMAPPING          pCosaNat          = NULL;
    PCOSA_DML_NAT_PTRIGGER          pCosaNatPt        = NULL;
    PSLAP_VARIABLE                  pSlapVariable     = NULL;
    ULONG                           ulEntryCount      = 0;
    ULONG                           ulIndex           = 0;
    ULONG                           uInstanceNumber   = 0;
    BOOL                            bNew              = FALSE;
    char*                           pAliasNat         = NULL;
    char*                           pFolderName       = NULL;

    CcspTraceWarning(("!!!!!! In CosaNatRegGetNatInfo !!!!!!\n"));

    if ( !pPoamIrepFoNat || !pPoamIrepFoNatPt )
    {
        CcspTraceWarning(("!!!!!! pPoamIrepFoNat: %p, pPoamIrepFoNatPt: %p !!!!!!\n", pPoamIrepFoNat, pPoamIrepFoNatPt));
        return ANSC_STATUS_FAILURE;
    }

    /* This is saved structure for nat
        *****************************************
              <Nat>
                  <1>
                       <alias>xxx</>
                       <bNew>false</>
                 </1>
                 <2>
                      <alias>xxx</>
                      <bNew>false</>
                 </2>
            </Nat>
      ****************************************************
      */

    /* enumerate Portmapping.{i} */
    ulEntryCount = pPoamIrepFoNat->GetFolderCount((ANSC_HANDLE)pPoamIrepFoNat);
    for ( ulIndex = 0; ulIndex < ulEntryCount; ulIndex++ )
    {
        /* Get i in Portmapping.{i} */
        pFolderName =
            pPoamIrepFoNat->EnumFolder
                (
                    (ANSC_HANDLE)pPoamIrepFoNat,
                    ulIndex
                );

        if ( !pFolderName )
        {
            continue;
        }

        uInstanceNumber = _ansc_atol(pFolderName);

        if ( uInstanceNumber == 0 )
        {
            AnscFreeMemory(pFolderName);
            continue;
        }

        pPoamIrepFoEnumNat = pPoamIrepFoNat->GetFolder((ANSC_HANDLE)pPoamIrepFoNat, pFolderName);

        AnscFreeMemory(pFolderName);

        if ( !pPoamIrepFoEnumNat )
        {
            continue;
        }

        /* Get PortMapping.{i}.Alias value*/
        if ( TRUE )
        {
            pSlapVariable =
                (PSLAP_VARIABLE)pPoamIrepFoEnumNat->GetRecord
                    (
                        (ANSC_HANDLE)pPoamIrepFoEnumNat,
                        COSA_DML_RR_NAME_NATAlias,
                        NULL
                    );

            if ( pSlapVariable )
            {
                pAliasNat = AnscCloneString(pSlapVariable->Variant.varString);

                SlapFreeVariable(pSlapVariable);
            }
        }

        /* Get PortMapping.{i}.bNew value*/
        if ( TRUE )
        {
            pSlapVariable =
                (PSLAP_VARIABLE)pPoamIrepFoEnumNat->GetRecord
                    (
                        (ANSC_HANDLE)pPoamIrepFoEnumNat,
                        COSA_DML_RR_NAME_NATbNew,
                        NULL
                    );

            if ( pSlapVariable )
            {
                bNew = pSlapVariable->Variant.varBool;

                SlapFreeVariable(pSlapVariable);
            }
            else
            {
                bNew = TRUE;
            }
        }

        /* Create one entry and keep this delay_added entry */
        pCosaNat = (PCOSA_DML_NAT_PMAPPING)AnscAllocateMemory(sizeof(COSA_DML_NAT_PMAPPING));
        if ( !pCosaNat )
        {
            returnStatus = ANSC_STATUS_FAILURE;
            goto EXIT1;
        }

        /* set some default value firstly */
        NAT_PORTMAPPING_SET_DEFAULTVALUE(pCosaNat);

        /* save alias and instanceNumber */
        pCosaNat->InstanceNumber = uInstanceNumber;
        AnscCopyString( pCosaNat->Alias, pAliasNat );

        /* Create one link point */
        pCosaNatContext = (PCOSA_CONTEXT_PMAPPING_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_PMAPPING_LINK_OBJECT));
        if ( !pCosaNatContext )
        {
            returnStatus = ANSC_STATUS_FAILURE;
            goto EXIT2;
        }

        NAT_PMAPPING_INITIATION_CONTEXT(pCosaNatContext)

        pCosaNatContext->InstanceNumber = pCosaNat->InstanceNumber;
        pCosaNatContext->hContext       = (ANSC_HANDLE)pCosaNat;
        pCosaNat                        = 0;
        pCosaNatContext->bNew           = bNew;

        CosaSListPushEntryByInsNum(&pMyObject->NatPMappingList, (PCOSA_CONTEXT_LINK_OBJECT)pCosaNatContext);

        /* release some memory */
        if (pAliasNat)
        {
            AnscFreeMemory(pAliasNat);
            pAliasNat = NULL;
        }

        pPoamIrepFoEnumNat->Remove((ANSC_HANDLE)pPoamIrepFoEnumNat);
        pPoamIrepFoEnumNat = NULL;
    }

    /* This is saved structure for nat port trigger
        *****************************************
              <Nat>
                <PortTrigger>
                  <Record>NextInsNumber</Record>
                  <1>
                       <alias>xxx</>
                       <bNew>true</>
                 </1>
                 <2>
                      <alias>xxx</>
                      <bNew>true</>
                 </2>
                 </PortTrigger>
            </Nat>
      ****************************************************
      */

    /* enumerate PortTrigger.{i} */
    ulEntryCount = pPoamIrepFoNatPt->GetFolderCount((ANSC_HANDLE)pPoamIrepFoNatPt);
    CcspTraceWarning(("!!!!!! ulEntryCount for PortTrigger: %d !!!!!!\n", ulEntryCount));

    for ( ulIndex = 0; ulIndex < ulEntryCount; ulIndex++ )
    {
        /* Get i in PortTrigger.{i} */
        pFolderName =
            pPoamIrepFoNatPt->EnumFolder
                (
                    (ANSC_HANDLE)pPoamIrepFoNatPt,
                    ulIndex
                );
        CcspTraceWarning(("!!!!!! pFolderName: %s !!!!!!\n", pFolderName));

        if ( !pFolderName )
        {
            continue;
        }

        uInstanceNumber = _ansc_atol(pFolderName);

        if ( uInstanceNumber == 0 )
        {
            AnscFreeMemory(pFolderName);
            continue;
        }

        pPoamIrepFoEnumNat = pPoamIrepFoNatPt->GetFolder((ANSC_HANDLE)pPoamIrepFoNatPt, pFolderName);

        AnscFreeMemory(pFolderName);

        if ( !pPoamIrepFoEnumNat )
        {
            continue;
        }

        /* Get PortTrigger.{i}.Alias value*/
        if ( TRUE )
        {
            pSlapVariable =
                (PSLAP_VARIABLE)pPoamIrepFoEnumNat->GetRecord
                    (
                        (ANSC_HANDLE)pPoamIrepFoEnumNat,
                        COSA_DML_RR_NAME_NATAlias,
                        NULL
                    );

            if ( pSlapVariable )
            {
                pAliasNat = AnscCloneString(pSlapVariable->Variant.varString);

                SlapFreeVariable(pSlapVariable);
            }
        }

        /* Get PortTrigger.{i}.bNew value*/
        if ( TRUE )
        {
            pSlapVariable =
                (PSLAP_VARIABLE)pPoamIrepFoEnumNat->GetRecord
                    (
                        (ANSC_HANDLE)pPoamIrepFoEnumNat,
                        COSA_DML_RR_NAME_NATbNew,
                        NULL
                    );

            if ( pSlapVariable )
            {
                bNew = pSlapVariable->Variant.varBool;

                SlapFreeVariable(pSlapVariable);
            }
            else
            {
                bNew = TRUE;
            }
        }

        /* Create one entry and keep this delay_added entry */
        pCosaNatPt = (PCOSA_DML_NAT_PTRIGGER)AnscAllocateMemory(sizeof(COSA_DML_NAT_PTRIGGER));

        if ( !pCosaNatPt )
        {
            returnStatus = ANSC_STATUS_RESOURCES;
            goto EXIT1;
        }

        /* set some default value firstly */
        COSA_DML_NAT_PTRIGGER_INIT(pCosaNatPt);

        /* save alias and instanceNumber */
        pCosaNatPt->InstanceNumber = uInstanceNumber;
        AnscCopyString( pCosaNatPt->Alias, pAliasNat );

        CcspTraceWarning(("!!!!!! pCosaNatPt->InstanceNumber: %d, pCosaNatPt->Alias: %s !!!!!!\n", pCosaNatPt->InstanceNumber, pCosaNatPt->Alias));

        /* Create one link point */
        pCosaNatPtContext = (PCOSA_CONTEXT_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_LINK_OBJECT));
        if ( !pCosaNatPtContext )
        {
            AnscFreeMemory(pCosaNatPt); /*RDKB-6742, CID-33206, Free unused resources after use*/
            pCosaNatPt = NULL;
            returnStatus = ANSC_STATUS_FAILURE;
            goto EXIT2;
        }

         COSA_CONTEXT_LINK_INITIATION_CONTENT(pCosaNatPtContext)

        pCosaNatPtContext->InstanceNumber = pCosaNatPt->InstanceNumber;
        pCosaNatPtContext->hContext       = (ANSC_HANDLE)pCosaNatPt;
        pCosaNatPtContext->bNew           = bNew;

        CosaSListPushEntryByInsNum(&pMyObject->NatPTriggerList, (PCOSA_CONTEXT_LINK_OBJECT)pCosaNatPtContext);

        /* release some memory */
        if (pAliasNat)
        {
            AnscFreeMemory(pAliasNat);
            pAliasNat = NULL;
        }

        pPoamIrepFoEnumNat->Remove((ANSC_HANDLE)pPoamIrepFoEnumNat);
        pPoamIrepFoEnumNat = NULL;
    }



EXIT2:
    if(pCosaNat)
        AnscFreeMemory(pCosaNat);

EXIT1:

    if(pAliasNat)
        AnscFreeMemory(pAliasNat);

    if ( pPoamIrepFoEnumNat )
        pPoamIrepFoEnumNat->Remove((ANSC_HANDLE)pPoamIrepFoEnumNat);

    return returnStatus;
}