/**
Auxilary function called to Copy the screen to bitmap (mbm) file.
@param aHashIndex contains hashID. Bitmap is created with the aHashIndex as name
*/
EXPORT_C void CTHashReferenceImages::CopyScreenToBitmapL(const TDesC& aHashIndex)
	{
	CFbsBitmap *bitmap = new(ELeave)CFbsBitmap();
	CleanupStack::PushL(bitmap);
	User::LeaveIfError(bitmap->Create(iBitmapDevice->SizeInPixels(), iBitmapDevice->DisplayMode()));
	TRect rect = TRect(iBitmapDevice->SizeInPixels());
	CFbsBitmapDevice *device=CFbsBitmapDevice::NewL(bitmap);
	CleanupStack::PushL(device);
	CFbsBitGc *gc;
	User::LeaveIfError(device->CreateContext(gc));
	gc->SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha);
	gc->BitBlt(TPoint(), iBitmap, rect);
	TFileName mbmFile;
	mbmFile.Format(iPath->Des(), &aHashIndex);
	bitmap->Save(mbmFile);
	delete gc;
	CleanupStack::PopAndDestroy(2);
	}