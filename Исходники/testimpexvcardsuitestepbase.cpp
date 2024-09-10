void CTestImpExvCardSuiteStepBase::ExportItemL(TBuf<80> aPath, TBool aAddBDay)
	{
	OpenDBL();
	
	TContactItemId itemId;
	RFs fsSession;
	RFileWriteStream fileStream;

	CContactIdArray* idArray = NULL;
	CContactCard* contactAdded = NULL;
	TTime now;
	
	User::LeaveIfError(fsSession.Connect());
	CleanupClosePushL(fsSession);
	
	idArray = CContactIdArray::NewL();

	CleanupStack::PushL(idArray);   // idArray

	fsSession.MkDirAll(aPath);
	User::LeaveIfError(fileStream.Replace(fsSession, aPath, EFileWrite));

	contactAdded = CContactCard::NewL();

	CleanupStack::PushL(contactAdded);   // contactAdded
	
	contactAdded->IncAccessCount();
	
	// ADD BDAY
	if (aAddBDay)
		{
		CContactItemFieldSet& fieldSet=contactAdded->CardFields();
		const TInt pos=fieldSet.Find(KUidContactFieldBirthday);
	
		if (pos!=KErrNotFound)
			{
			fieldSet[pos].DateTimeStorage()->SetTime(iBDayLocal);
			}
		else
			{
			CContactItemField* field=CContactItemField::NewLC(KStorageTypeDateTime,KUidContactFieldBirthday);
   			field->SetMapping(KUidContactFieldVCardMapBDAY);
			field->DateTimeStorage()->SetTime(iBDayLocal);
			contactAdded->AddFieldL(*field);
	
			CleanupStack::Pop(); // field
			}
		}
	
	SetNameL(*contactAdded, KUidContactFieldGivenName, _L("toby"), ETrue);
	SetNameL(*contactAdded, KUidContactFieldPhoneNumber, _L("6041233214"), ETrue);

	User::After(3000000);

	// There is no need to call SetLastModifed because
	// That function will be call by ExportSelectedContactsL below
	now.UniversalTime();
	iRecordedTime = now;
	
	INFO_PRINTF1(_L("Adding contact to Database....."));
	itemId = iDb->AddNewContactL(*contactAdded);
	INFO_PRINTF1(_L("Contact Added to Database"));
	CleanupStack::PopAndDestroy(contactAdded);  // contactAdded
	contactAdded = NULL;

	idArray->InsertL(0, itemId);

	INFO_PRINTF1(_L("Exporting Contact....."));
	iDb->ExportSelectedContactsL(TUid::Uid(KUidVCardConvDefaultImpl), *idArray, fileStream, CContactVCardConverter::EDefault, ETrue);
	INFO_PRINTF1(_L("Exported Contact"));
	fileStream.CommitL();
	fileStream.Close();
	
	CleanupStack::PopAndDestroy(idArray);  // idArray
	fsSession.Close();
	CleanupStack::PopAndDestroy();  // fsSession
	CloseDB();
	}