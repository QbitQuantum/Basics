TVerdict CImportDrmArchive::doTestStepL()
	{
	// SetTestStepResult(EInconclusive) is a bad idea.
	// It makes the TEST macroes unusable.

	TPtrC source;
	TPtrC target;
	TPtrC importerMode;

	GetStringFromConfig(ConfigSection(),_L("source"),source);
	GetStringFromConfig(ConfigSection(),_L("target"),target);

	// importerMode is optional in ini file. If the token exist and its
	// value == ClientCreateFiles, then RTAUtils will hide the output
	// filename from CImportFile and handle opening the output file
	// and receipt files itself.
	GetStringFromConfig(ConfigSection(),_L("importerMode"),importerMode);
	
	_LIT(KClientCreateFiles, "ClientCreateFiles");
	TBool doFileCreate = (importerMode.CompareF(KClientCreateFiles) == 0);

	INFO_PRINTF2(_L("Importing DRM archive : %S "), &source);
	INFO_PRINTF2(_L("Writing output archive: %S "), &target);

	TPtrC outputPath;
	TPtrC suggestedOutFileName;

	TParsePtrC parser(target);
	outputPath.Set( parser.DriveAndPath() );
	suggestedOutFileName.Set( parser.NameAndExt() );

	__UHEAP_MARK;	
	TInt numpushed(0);

	// create a supplier session
	CSupplier *mySupplier = CSupplier::NewLC();
	numpushed++;

	mySupplier->SetOutputDirectoryL(outputPath);

	// fill in a metadata array with just the mime type
	CMetaDataArray *metaDataArray = CMetaDataArray::NewL();
	CleanupStack::PushL(metaDataArray);
	numpushed++;

	_LIT8(KContentType,"content-type");
	metaDataArray->AddL(KContentType(), KRtaMimeRights);
	metaDataArray->AddL(KContentType(), KRtaMimeContentRights);

	CImportFile* import = NULL;
	if (doFileCreate)
		{
		import = mySupplier->ImportFileL(KRtaMimeContentRights, *metaDataArray);
		}
	else
		{
		import = mySupplier->ImportFileL(KRtaMimeContentRights, *metaDataArray, suggestedOutFileName);
		}

	CleanupStack::PopAndDestroy(metaDataArray);  // numpushed--
	CleanupStack::PushL(import);  // numpushed++, so cancel with line above

	RFs fs;
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);
	numpushed++;
	
#ifdef SYMBIAN_ENABLE_64_BIT_FILE_SERVER_API 
	RFile64 sourcefile;
#else
	RFile sourcefile;
#endif // SYMBIAN_ENABLE_64_BIT_FILE_SERVER_API
	
	User::LeaveIfError(sourcefile.Open(fs, source, EFileRead | EFileStream | EFileShareReadersOnly));
	CleanupClosePushL(sourcefile);
	numpushed++;
#ifdef SYMBIAN_ENABLE_64_BIT_FILE_SERVER_API 
	RFile64 targetfile;
#else
	RFile targetfile;
#endif // SYMBIAN_ENABLE_64_BIT_FILE_SERVER_API
	
	TBool targetFileOpen = EFalse;
	TInt err(KErrNone);
	TFileName fn;

	const TInt KMyBufSize = 1024;
	TBuf8 <KMyBufSize> buffer;
	TInt length = KMyBufSize;
	while(length > 0)
		{
		User::LeaveIfError(sourcefile.Read(buffer, buffer.MaxLength()));
		length = buffer.Length();
		err = import->WriteData(buffer);
		
		if(err != KErrNone)
			{
			if(err == KErrCANewFileHandleRequired)
				{
				TESTL(doFileCreate);
				TESTL(!targetFileOpen);

				import->GetSuggestedOutputFileName(fn);
				fn.Insert(0, outputPath);

				INFO_PRINTF3(_L("Agent suggested name is %S, target is %S."), &fn, &target);

				User::LeaveIfError(targetfile.Create(fs, target, EFileStream | EFileWrite | EFileShareAny));
				CleanupClosePushL(targetfile);
				numpushed++;
				targetFileOpen = ETrue;
				User::LeaveIfError(import->ContinueWithNewOutputFile(targetfile, fn));
				}
			else
				{					
				INFO_PRINTF2(_L("Error writing data, Error code is: %d"),err);
				User::LeaveIfError(err);
				}
			}
		}

	if(targetFileOpen)
		{
		CleanupStack::PopAndDestroy(&targetfile);	
		numpushed--;
		}

	// process the rights that were received alongside the content
	err = import->WriteDataComplete();
	while(err == KErrCANewFileHandleRequired)
		{
		TEST(doFileCreate);

		import->GetSuggestedOutputFileName(fn);
		fn.Insert(0, outputPath);
		
		INFO_PRINTF2(_L("Creating Receipt File: %S "), &fn);								
		RFile receiptFile;
		User::LeaveIfError(receiptFile.Replace(fs, fn, EFileStream | EFileWrite | EFileShareAny));
		CleanupClosePushL(receiptFile);
		err = import->ContinueWithNewOutputFile(receiptFile, fn);
		CleanupStack::PopAndDestroy(&receiptFile);	
		}

	User::LeaveIfError(err);

	TPtrC importOutFileName;
	TPtrC contentOutputName(KNullDesC);
	for (TInt i = 0; i < import->OutputFileCountL(); i++)
		{
		importOutFileName.Set( import->OutputFileL(i).FileName() );

		if (import->OutputFileL(i).OutputType() == EContent)
			{
			contentOutputName.Set(importOutFileName);
			}
		else
			{
			// delete the receipt we just created
			// they only get in the way when importing files using the utility
			INFO_PRINTF2(_L("Receipt files %S deleted (not important) when using ImportDrmArchive step"), &importOutFileName);										
			fs.Delete(importOutFileName); // ignore return code
			}
		}

	/**
	 * Added doFileCreate check while fixing DEF132876. On using
	 * importerMode=ClientCreateFiles if target is not set as 
	 * "RTATest001.content" in the ini file, the comparison below
	 * succeeds and "fs.Rename(contentOutputName, target)" fails,
	 * causing test case to fail.
	 * In all other case, contentOutputName and target are always
	 * same and the if condition is not entered.
	 */
	if (!doFileCreate && contentOutputName.CompareF(target) != 0)
		{
		// This must be the case that RTA automatically create
		// output file. See the line targetfile.Create(fs, target, ...).

		// Before DEF088475, users of RTAUtils test harness can
		// specify whatever extension for the output file. The 
		// defect fix changed the importer from CRefTestAgentImport
		// (unit test) to CImportFile (end-to-end test). CImportFile
		// converts non-standard ext to .content. To maintain backward
		// compatibility, we need to rename the generated output.

		fs.Delete(target); // ignore return code
		TEST(fs.Rename(contentOutputName, target) == 0);
		}
	
	CleanupStack::PopAndDestroy(numpushed);

	__UHEAP_MARKEND;
	
	return TestStepResult();
	}