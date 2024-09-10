static void TestWithCaps(TUint32 aCaps, TInt aExpectedError, const TDesC& aFileName)
/**
	Helper function for TestWithCaps(TUint32, TInt).  This function invokes
	a helper executable with the supplied capabilities and tells it to delete
	the supplied filename.
	
 	@param	aCapMask		Capabilities of process which calls RLoader::Delete.
	@param	aExpectedError	Expected error reason.  The launched executable is expected
							to panic with category KTldPanicCat and this reason, which
							is the expected return code from RLoader::Delete.
	@param	aFileName		The helper executable is told to delete this file.
*/
	{
	test.Printf(
		_L("TestWithCaps,aCaps=0x%x,aExpectedError=%d,aFileName=\"%S\"\n"),
		aCaps, aExpectedError, &aFileName);

	TInt r;

	// create the file to delete
	RFs fs;
	r = fs.Connect();
	test(r == KErrNone);

	// if this file is expected to exist then create it
	TPtrC dirName;
	TBool shouldExist = (aFileName == KTldTcbFile || aFileName == KTldAllFilesFile);
	if (shouldExist)
		{
		TParsePtrC pp(aFileName);
		dirName.Set(pp.DriveAndPath());
		r = fs.MkDirAll(dirName);
		test(r == KErrNone || r == KErrAlreadyExists);
		CreateTestFile(fs, aFileName);
		}

	SetHelperCaps(aCaps);
	RunHelper(aFileName, aExpectedError);

	if (shouldExist)
		{
		// if the file could not be deleted then delete it now
		TEntry e;
		// a C++ bool for the following equality operator
		bool exists = (fs.Entry(aFileName, e) == KErrNone);
		test(exists == (aExpectedError != KErrNone));
		
		if (exists)
			{
			r = fs.Delete(aFileName);
			test(r == KErrNone);
			}

		// delete the immediate containing directory.  The error code is not
		// used because the directory may be used for something else.
		fs.RmDir(dirName);
		}

	// delete the generated different-caps file
	r = fs.Delete(_L("c:\\sys\\bin\\tld_helper_caps.exe"));
	test(r == KErrNone);
	r = fs.Delete(_L("c:\\sys\\hash\\tld_helper_caps.exe"));
	test(r == KErrNone || r == KErrNotFound || r == KErrPathNotFound);

	fs.Close();
	}