CFbsBitmap* CMobiStegoChooseImgView::loadImageL()
	{
	RFs fs;
	TRequestStatus status;
	CFbsBitmap* bitmap = NULL;
	CImageDecoder* aImageDecoder = NULL;
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);
	RFbsSession::Connect(fs);
	RFbsSession* rfbs = RFbsSession::GetSession();

	aImageDecoder = CImageDecoder::FileNewL(fs, _L("c:\\Data\\Images\\red.jpg"));
	CleanupStack::PushL(aImageDecoder);
	bitmap = new (ELeave) CFbsBitmap();
	CleanupStack::PushL(bitmap);
	TSize sizeImage = aImageDecoder->FrameInfo().iOverallSizeInPixels;
	TInt aa = KErrCouldNotConnect;//////INDAGA!!!!!!!!!!!!!!!!
	TInt ppp = bitmap->Create(sizeImage,
			aImageDecoder->FrameInfo().iFrameDisplayMode);
	aImageDecoder->Convert(&status, *bitmap);
	CleanupStack::Pop(3);
	return bitmap;

	/*CImageDecoder* iImageDecoder = CImageDecoder::FileNewL( iFs, aFileName );
	 
	 // create the destination bitmap
	 result = new (ELeave) CFbsBitmap();
	 result->Create( iImageDecoder->FrameInfo().iOverallSizeInPixels,
	 iImageDecoder->FrameInfo().iFrameDisplayMode ); 

	 // start conversion to bitmap
	 
	 iImageDecoder->Convert( &iStatus, *result );
	 
	 return result;*/
	}