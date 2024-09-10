void CTap2MenuAppUi::CopyBitmapL(CFbsBitmap *aSource, CFbsBitmap *aTarget)
	{
	if(aSource != NULL && aTarget != NULL)
		{
		if(aSource->SizeInPixels() != aTarget->SizeInPixels() || aSource->DisplayMode() != aTarget->DisplayMode())
			{User::Leave(KErrArgument);}
		CFbsBitmapDevice* device = CFbsBitmapDevice::NewL(aTarget);
		CleanupStack::PushL(device);
		CFbsBitGc* gc = NULL;
		User::LeaveIfError(device->CreateContext(gc));
		CleanupStack::PushL(gc);
		gc->BitBlt(TPoint(0, 0), aSource);
		CleanupStack::PopAndDestroy(gc);
		CleanupStack::PopAndDestroy(device);
		}
	}