void OpConvertFileFormats::Do(OpDescriptor*)
{
	ERROR3 ("Please read the following comments BEFORE using this op!");	// comment this out to use the op

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// set up the search path, file util allows us just to pass the path/*.xar
	String_256 SearchPath = TEXT ("d:\\clipart\\xara\\");		// YOU MUST CHANGE THIS PATH
	
	String_256 FileSpecifier = SearchPath;						// YOU MUST CHANGE THIS EXTENSION
				FileSpecifier += TEXT("*.art");
	String_256 FileSpecifier2 = TEXT("xar");					// YOU MUST CHANGE THIS EXTENSION

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

	BOOL ok = FileUtil::StartFindingFiles(&FileSpecifier);
	active = TRUE;
	String_256 Filename;
	while (ok)
	{
		// fileutil will give us the next filename
		ok = FileUtil::FindNextFile(&Filename);
		String_256 FilePath = SearchPath;
		FilePath += Filename;
		PathName Path (FilePath);

		if (ok)
		{
			CDocument* pDoc = theApp.OpenDocumentFile((TCHAR*)FilePath);
			if (pDoc!=NULL)
			{
				// Make sure that the files name is sensible
				theApp.MakeDocumentNative(pDoc, &Path);
				
				Path.SetType (FileSpecifier2);
				String_256 newPath = Path.GetPath ();
				pDoc->DoSave ((TCHAR*) newPath, TRUE);

				FileCloseAction ();
			}
		}
	}
	active = FALSE;
	FileUtil::StopFindingFiles ();
}