/**
  Function : doTestStepL
  Description : Fetches the srvice ID using the IMAP account name and sets
  				the full download limit fields of the setting object corresponding to it. 
  @return : TVerdict - Test step result
  @leave  :	KMsvNullIndexEntryId	If valid IMAP account name is not specified or
									If valid remote folder name is not specified
*/
TVerdict CT_MsgSetImap4FullDownloadLimits::doTestStepL()
	{
	INFO_PRINTF1(KInfoTestStepName);
	TPtrC imapAccountName;
	
	/* Reads IMAP Account Name from ini file */
	if(!GetStringFromConfig(ConfigSection(), KImapAccountName, imapAccountName))
		{
		ERR_PRINTF1(KAcntNameNtSpecified);
		SetTestStepResult(EFail);
		}		
	else
		{
		TPtrC destFolderName;

		/* Reads the destination Folder Name */
		if(!GetStringFromConfig(ConfigSection(), KFolderName, destFolderName))
			{
			ERR_PRINTF1(KDestFolderNtSpecified);
			SetTestStepResult(EFail);
			}	
		else
			{
			TInt maxEmailSize = KMaxTInt;
			/* Reads the size of the Email to be set,where default is KMaxTInt */
			GetIntFromConfig(ConfigSection(), KMaxEmailSize, maxEmailSize);
			
			TPtrC mailOption;
			/* Reads the mail option to be set from the ini file */
			if(!GetStringFromConfig(ConfigSection(), KImapMailOption, mailOption))
				{
				ERR_PRINTF1(KGetMailOptNtSpecified);
				SetTestStepResult(EFail);
				}
			else
				{
				TMsvId destFolderId = -1;
				/* Retrieves the IMAP service Id based on the IMAP account name*/
				TMsvId imapServiceId = CT_MsgUtilsCentralRepository::GetImapServiceIdL((TDes&) imapAccountName);
				if(imapServiceId == KMsvNullIndexEntryId)
					{
					ERR_PRINTF2(KAcntNtExist, &imapAccountName);
					SetTestStepResult(EFail);
					}
				else
					{
					/* 
					 * Retrieves the mail options and the remote destination folder Id
					 * based on the IMAP account name and the remote folder name given
					 */
					TImap4GetMailOptions imapMailOption = CT_MsgUtilsEnumConverter::ConvertDesToTImap4GetMailOptions(mailOption);
		
					destFolderId = CT_MsgUtils::GetRemoteFolderIdByNameL(iSharedDataIMAP.iSession,
												imapAccountName,destFolderName);
			
					if(destFolderId == KMsvNullIndexEntryId)
						{
						ERR_PRINTF1(_L("Invalid remote folder name specified"));
						SetTestStepResult(EFail);
						}
					else
						{																						
						INFO_PRINTF2(KFolderId,destFolderId);		
						
						/* Stores the fulll donwload limit values */
						TImImap4GetMailInfo  imap4GetMailInfo;
						imap4GetMailInfo.iMaxEmailSize      = maxEmailSize;	
						imap4GetMailInfo.iGetMailBodyParts  = imapMailOption;
						imap4GetMailInfo.iDestinationFolder = destFolderId;
						
						/* Loads the Imap account settings and save the download limits */
						CEmailAccounts* emailAccounts = CEmailAccounts::NewLC();
						CImImap4Settings* imapSettings =  new(ELeave) CImImap4Settings();
						CleanupStack::PushL(imapSettings);

						TImapAccount imapAccount;
						emailAccounts->GetImapAccountL(imapServiceId, imapAccount);
						emailAccounts->LoadImapSettingsL(imapAccount, *imapSettings);
						
						
						TBool deleteFlag;
						if(GetBoolFromConfig(ConfigSection(),KDeleteFlag,deleteFlag))	
							{
							imapSettings->SetDeleteEmailsWhenDisconnecting(deleteFlag);
							}
						TBool updateFlag;
						if(GetBoolFromConfig(ConfigSection(),KUpdateFlag,updateFlag))	
							{
							imapSettings->SetUpdatingSeenFlags(updateFlag);
							}
							
						TInt fetchSizeLimit = 20480;
						if(GetIntFromConfig(ConfigSection(),KFetchSizeLimit,fetchSizeLimit))
							{
							imapSettings->SetFetchSizeL(fetchSizeLimit);		
							}
							
						TInt inboxSyncLimit;
						if(GetIntFromConfig(ConfigSection(),KInboxSyncLimit,inboxSyncLimit))
							{
							imapSettings->SetInboxSynchronisationLimit(inboxSyncLimit);
							}
						
						TInt mailboxSyncLimit;
						if(GetIntFromConfig(ConfigSection(),KMailboxSyncLimit,mailboxSyncLimit))
							{
							imapSettings->SetMailboxSynchronisationLimit(mailboxSyncLimit);
							}
						
						TPtrC searchString;
						if(GetStringFromConfig(ConfigSection(),KSearchString,searchString))
							{
							HBufC8* string = HBufC8::NewLC(searchString.Length());
							string->Des().Copy(searchString);
							imapSettings->SetSearchStringL(string->Des());
							CleanupStack::PopAndDestroy(string);
							}
						
						TPtrC folderSubTypeName;
						if(GetStringFromConfig(ConfigSection(),KFolderSubType,folderSubTypeName))
							{
							TFolderSubscribeType folderSubType =  CT_MsgUtilsEnumConverter::ConvertDesToTFolderSubscribeType
												((TDesC&)folderSubTypeName);
							imapSettings->SetSubscribe(folderSubType);
							}
							
						TPtrC folderSyncTypeName;
						if(GetStringFromConfig(ConfigSection(),KFolderSyncType,folderSyncTypeName))
							{
							TFolderSyncType  folderSyncType = CT_MsgUtilsEnumConverter::ConvertDesToTFolderSyncType
												((TDesC&)folderSyncTypeName);
							imapSettings->SetSynchronise(folderSyncType);
							}
										
						/* Sets the download limts in the settings object created */
						imapSettings->SetMaxEmailSize( imap4GetMailInfo.iMaxEmailSize );
						imapSettings->SetGetMailOptions( imap4GetMailInfo.iGetMailBodyParts );
						
						/* Saves the settings */
						emailAccounts->SaveImapSettingsL(imapAccount, *imapSettings);
						
						CleanupStack::PopAndDestroy(2,emailAccounts);/* imapSettings, emailAccounts */
						
						INFO_PRINTF2(KInfoCompletionStatus, &KSetImap4FullDownloadLimits);
						}
					}
				}
			}
		}
	return TestStepResult();
	}