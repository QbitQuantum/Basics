/*
-------------------------------------------------------------------------------
internal icon re-sizer function
-------------------------------------------------------------------------------
*/   
CGulIcon* CYBRecognizer1::GetListIconL(const TDesC& aFileName,TInt aImage,TInt aMask, TSize aSize)
{
	CGulIcon* RetIcon(NULL);
	TBool OkToAdd(EFalse);
	
	CFbsBitmap* MyBitmap = new(ELeave)CFbsBitmap();
	CleanupStack::PushL(MyBitmap);
	CFbsBitmap* MyMask = new(ELeave)CFbsBitmap();
	CleanupStack::PushL(MyMask);
	
	if(KErrNone == MyBitmap->Load(aFileName,aImage))
	{
		if(KErrNone == MyMask->Load(aFileName,aMask))
		{
			OkToAdd = ETrue;
		}
	}
	
	if(OkToAdd)
	{
		TSize ImgSiz = MyBitmap->SizeInPixels();
		if(aSize.iWidth != ImgSiz.iWidth
		|| aSize.iHeight!= ImgSiz.iHeight)
		{
			CFbsBitmap* TmpBackBitmap = new(ELeave)CFbsBitmap();
			CleanupStack::PushL(TmpBackBitmap);
			
			if(KErrNone == TmpBackBitmap->Create(aSize,MyBitmap->DisplayMode()))
			{	
				CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(TmpBackBitmap);
				CleanupStack::PushL(bitmapDevice);

				CFbsBitGc* graphicsContext = NULL;
				User::LeaveIfError(bitmapDevice->CreateContext(graphicsContext));
				CleanupStack::PushL(graphicsContext);

				graphicsContext->DrawBitmap(TRect(0,0,aSize.iWidth,aSize.iHeight),MyBitmap);
				
				CleanupStack::PopAndDestroy(2);//graphicsContext,bitmapDevice,
			}
			
			CFbsBitmap* TmpBackMask = new(ELeave)CFbsBitmap();
			CleanupStack::PushL(TmpBackMask);
			if(KErrNone == TmpBackMask->Create(aSize,MyMask->DisplayMode()))
			{	
				CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(TmpBackMask);
				CleanupStack::PushL(bitmapDevice);

				CFbsBitGc* graphicsContext = NULL;
				User::LeaveIfError(bitmapDevice->CreateContext(graphicsContext));
				CleanupStack::PushL(graphicsContext);

				graphicsContext->DrawBitmap(TRect(0,0,aSize.iWidth,aSize.iHeight),MyMask);
				
				CleanupStack::PopAndDestroy(2);//graphicsContext,bitmapDevice,
			}
		
			CleanupStack::Pop(2);//TmpBackBitmap, TmpBackMask
			RetIcon = CGulIcon::NewL(TmpBackBitmap, TmpBackMask);
		}
	}
	
	if(!RetIcon && OkToAdd)
	{
		CleanupStack::Pop(2);//MyBitmap, MyMask
		RetIcon = CGulIcon::NewL(MyBitmap, MyMask);
	}
	else
	{
		CleanupStack::PopAndDestroy(2);//MyBitmap, MyMask
	}
		
	return RetIcon;
}