void CDesktopHotKeyAppUi::About()
	{
	TFileName filename;
	GetAppPath(filename);
	HBufC* textResource = StringLoader::LoadLC(R_ABOUT_FILE);
	filename.Append(textResource->Des());
	CleanupStack::PopAndDestroy(textResource);

	RFile file;
	TInt nErr = file.Open(CEikonEnv::Static()->FsSession(), filename, EFileRead
			| EFileShareAny);
	if (nErr != KErrNone)
		return;

	TFileText fileText;
	fileText.Set(file);
	TBuf<128> linePtr;
	HBufC* iText = NULL;

	while (fileText.Read(linePtr) == KErrNone)
		{
		if (iText!=NULL)
			{
			iText = iText->ReAllocL(iText->Length() + linePtr.Length() + 2);
			iText->Des().Append(linePtr);
			}
		else
			{
			iText = HBufC::NewL(linePtr.Length() + 2);
			iText->Des().Append(linePtr);
			}
		iText->Des().Append(CEditableText::ELineBreak);
		}
	file.Close();

	ShowModalAboutDlgL(R_ABOUT_DIALOG_TITLE,iText->Des());
	
	
	delete iText;
	}