/**
Copy a source bitmap into a new bitmap with the specified display mode
*/
CFbsBitmap* CTe_graphicsperformanceSuiteStepBase::CopyIntoNewBitmapL(CFbsBitmap* aSrc, TDisplayMode aDisplayMode)
	{
	CFbsBitmap* dstBmp = new(ELeave) CFbsBitmap;
	CleanupStack::PushL(dstBmp);
	TInt ret=dstBmp->Create(aSrc->SizeInPixels(), aDisplayMode);
	User::LeaveIfError(ret);
	CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(dstBmp);
	CleanupStack::PushL(bitmapDevice);
	CFbsBitGc* gc;
	ret = bitmapDevice->CreateContext(gc);
	User::LeaveIfError(ret);
	CleanupStack::PushL(gc);
	gc->BitBlt(TPoint(0,0), aSrc);
	CleanupStack::PopAndDestroy(2, bitmapDevice); // gc, bitmapDevice
	CleanupStack::Pop(dstBmp);
	return dstBmp;
	}