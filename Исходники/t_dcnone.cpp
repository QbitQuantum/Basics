LOCAL_C void resourceRFiletest()
//
//
//
	{
	r=TheFs.SetSessionPath(restestname);
	test_KErrNone(r);

	r=file1.Temp(TheFs,restestname,fromTemp,EFileWrite);
	test_Value(r, r == KErrPermissionDenied);
	file1.Close();

	r=file1.Create(TheFs,KFileRes,EFileWrite);
	test_Value(r, r == KErrPermissionDenied);
	file1.Close();

	r=file1.Open(TheFs,KFileRes,EFileWrite);
	test_Value(r, r == KErrPermissionDenied);
	file1.Close();

	r=file1.Open(TheFs,KFileRes,EFileRead|EFileShareReadersOnly);
	test_Value(r, r == KErrNone || r==KErrPathNotFound);
	file1.Close();

	r=file1.Open(TheFs,KFileRes,EFileShareReadersOrWriters|EFileRead);
	test_Value(r, r == KErrNone || r==KErrPathNotFound);
	file1.Close();

	r=file1.Open(TheFs,KFileRes,EFileShareReadersOrWriters|EFileWrite);
	test_Value(r, r == KErrPermissionDenied);
	file1.Close();

	r=file1.Open(TheFs,KFileRes,EFileShareReadersOnly);
	test_Value(r, r == KErrNone || r==KErrPathNotFound);

	r=file1.ChangeMode(EFileShareExclusive);	//this is not illegal though will prevent shared access to resource which is nit my fault but may be desirable to prevent
	test_Value(r, r == KErrNone || r==KErrPathNotFound);

	//this operation is prevented as you can not open a file for write access in the resource directory
	r=file1.Rename(KFileRes3);
	test_Value(r, r == KErrPermissionDenied || r==KErrAccessDenied);

	file1.Close();

	r=file1.Replace(TheFs,KFileRes,EFileWrite);
	test_Value(r, r == KErrPermissionDenied);
	file1.Close();

	}