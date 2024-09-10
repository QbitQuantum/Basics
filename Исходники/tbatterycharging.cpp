void CDummyUsbDevice::OpenFileL()
	{
	RFs fs;
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TFindFile ff(fs);
	User::LeaveIfError(ff.FindByDir(_L("\\system\\data\\t_charging.txt"),KNullDesC));
	
	RFile file;
	TInt size;
	User::LeaveIfError(file.Open(fs,ff.File(),EFileStreamText|EFileRead|EFileShareReadersOnly));
	CleanupClosePushL(file);
	
	User::LeaveIfError(file.Size(size));

	iText = REINTERPRET_CAST(TText8*, User::AllocL(size));
	iPtr.Set(iText, size/sizeof(TText8), size/sizeof(TText8));
	TPtr8 dest(REINTERPRET_CAST(TUint8*,iText), 0, size);
	User::LeaveIfError(file.Read(dest)); 

	CleanupStack::PopAndDestroy(); // file
	CleanupStack::PopAndDestroy(); // fs
	}