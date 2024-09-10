TBool CTestContainer::CompareScreenContentWithTestBitmapL(const CBitmapFrameData& aBkgdFrame, const CBitmapFrameData& aFrame1, const TPoint& aPos)
	{
	TSize size = aFrame1.Bitmap()->SizeInPixels();

	// Create test bitmap for comparison 
	CFbsBitmap* testBitmap = new (ELeave) CFbsBitmap;
	CleanupStack::PushL(testBitmap);
	User::LeaveIfError( testBitmap->Create(size, iEikonEnv->DefaultDisplayMode()));
	CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(testBitmap);
	CleanupStack::PushL(bitmapDevice);
	CFbsBitGc* bitmapGc = CFbsBitGc::NewL();
	CleanupStack::PushL(bitmapGc);
	bitmapGc->Activate(bitmapDevice);
	// Blit the background bitmap
	bitmapGc->BitBlt(aPos, aBkgdFrame.Bitmap());
	// Blit the frame bitmap with mask
	bitmapGc->BitBltMasked(aPos, aFrame1.Bitmap(), size, aFrame1.Mask(), ETrue);
	
	// Create bitmap and blit the screen contents into it for comparing it with test bitmap created above
	TRect rect(aPos,size);
	CFbsBitmap* scrBitmap = new (ELeave) CFbsBitmap;
	CleanupStack::PushL(scrBitmap);
	User::LeaveIfError(scrBitmap->Create(size, iEikonEnv->DefaultDisplayMode()) );
	User::LeaveIfError( iEikonEnv->ScreenDevice()->CopyScreenToBitmap(scrBitmap,rect) );
	
	TBool ret=CompareBitmapsL(testBitmap,scrBitmap);	

	CleanupStack::PopAndDestroy(4);	//scrBitmap, bitmapGc, bitmapDevice, testBitmap
	return ret;
	}