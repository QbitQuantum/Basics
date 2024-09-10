ANSC_STATUS
CosaUsersRegGetUserInfo
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus      = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_USERS           pMyObject         = ( PCOSA_DATAMODEL_USERS )hThisObject;

    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoUser      = (PPOAM_IREP_FOLDER_OBJECT )pMyObject->hIrepFolderUser;
    PPOAM_IREP_FOLDER_OBJECT        pPoamIrepFoEnumUser  = (PPOAM_IREP_FOLDER_OBJECT )NULL;
    PCOSA_CONTEXT_LINK_OBJECT       pCosaUserContext  = NULL;
    PCOSA_DML_USER                  pCosaUser         = NULL;
    
    PSLAP_VARIABLE                  pSlapVariable     = NULL;
    ULONG                           ulEntryCount      = 0;
    ULONG                           ulIndex           = 0;
    ULONG                           uInstanceNumber   = 0;
    BOOL                            bNew              = FALSE;
    char*                           pAliasUser        = NULL;
    char*                           pFolderName       = NULL;


    if ( !pPoamIrepFoUser )
    {
        return ANSC_STATUS_FAILURE;
    }

    /* This is saved structure for user
        *****************************************
              <User>
                  <NextInstanceNumber> xxx </>
                  <1>
                       <alias>xxx</>
                       <bNew>false</>
                 </1>
                 <2>
                      <alias>xxx</>
                      <bNew>false</>
                </2>
            </User>
      ****************************************************
      */

    /* Get Maximum number */
    if ( TRUE )
    {
        pSlapVariable =
            (PSLAP_VARIABLE)pPoamIrepFoUser->GetRecord
                (
                    (ANSC_HANDLE)pPoamIrepFoUser,
                    COSA_DML_RR_NAME_UserNextInsNunmber,
                    NULL
                );

        if ( pSlapVariable )
        {
            pMyObject->maxInstanceOfUser = pSlapVariable->Variant.varUint32;

            SlapFreeVariable(pSlapVariable);
        }
    }

    /* enumerate user.{i} */
    ulEntryCount = pPoamIrepFoUser->GetFolderCount((ANSC_HANDLE)pPoamIrepFoUser);
    for ( ulIndex = 0; ulIndex < ulEntryCount; ulIndex++ )
    {
        /* Get i in user.{i} */
        pFolderName =
            pPoamIrepFoUser->EnumFolder
                (
                    (ANSC_HANDLE)pPoamIrepFoUser,
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

        pPoamIrepFoEnumUser = pPoamIrepFoUser->GetFolder((ANSC_HANDLE)pPoamIrepFoUser, pFolderName);

        AnscFreeMemory(pFolderName);

        if ( !pPoamIrepFoEnumUser )
        {
            continue;
        }

        /* Get user.{i}.Username value*/
        if ( TRUE )
        {
            pSlapVariable =
                (PSLAP_VARIABLE)pPoamIrepFoEnumUser->GetRecord
                    (
                        (ANSC_HANDLE)pPoamIrepFoEnumUser,
                        COSA_DML_RR_NAME_UserAlias,
                        NULL
                    );

            if ( pSlapVariable )
            {
                pAliasUser = AnscCloneString(pSlapVariable->Variant.varString);

                SlapFreeVariable(pSlapVariable);
            }
        }

        /* Get user.{i}.bNew value*/
        if ( TRUE )
        {
            pSlapVariable =
                (PSLAP_VARIABLE)pPoamIrepFoEnumUser->GetRecord
                    (
                        (ANSC_HANDLE)pPoamIrepFoEnumUser,
                        COSA_DML_RR_NAME_UserbNew,
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
        pCosaUser = (PCOSA_DML_USER)AnscAllocateMemory(sizeof(COSA_DML_USER));
        if ( !pCosaUser )
        {
            returnStatus = ANSC_STATUS_FAILURE;            
            goto EXIT1;
        }

        /* set some default value firstly */
        USERS_USER_SET_DEFAULTVALUE(pCosaUser);

        /* save alias and instanceNumber */
        pCosaUser->InstanceNumber = uInstanceNumber;
        AnscCopyString( pCosaUser->Username, pAliasUser );

        /* Create one link point */
        pCosaUserContext = (PCOSA_CONTEXT_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_LINK_OBJECT));
        if ( !pCosaUserContext )
        {
            returnStatus = ANSC_STATUS_FAILURE;
            goto EXIT2;
        }

        COSA_CONTEXT_LINK_INITIATION_CONTENT(pCosaUserContext)

        pCosaUserContext->InstanceNumber = uInstanceNumber;
        pCosaUserContext->hContext       = (ANSC_HANDLE)pCosaUser;
        pCosaUser                        = 0;
        pCosaUserContext->bNew           = bNew;

        CosaSListPushEntryByInsNum(&pMyObject->UserList, (PCOSA_CONTEXT_LINK_OBJECT)pCosaUserContext);

        /* release some memory */
        if (pAliasUser)
        {
            AnscFreeMemory(pAliasUser);
            pAliasUser = NULL;
        }
        
        pPoamIrepFoEnumUser->Remove((ANSC_HANDLE)pPoamIrepFoEnumUser);
        pPoamIrepFoEnumUser = NULL;
    }


    
EXIT2:
    if(pCosaUser)
        AnscFreeMemory(pCosaUser);
        
EXIT1:
    
    if(pAliasUser)
        AnscFreeMemory(pAliasUser);
        
    if ( pPoamIrepFoEnumUser )
        pPoamIrepFoEnumUser->Remove((ANSC_HANDLE)pPoamIrepFoEnumUser);

    return returnStatus;
}