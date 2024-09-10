/**
Compare the window with the bitmap.
@param aScreen The screen device object
@param aBitmap The bitmap object for comparison
@return ETrue if the window and the bitmap is identified. Otherwise return EFalse.
*/
TBool CT_WServGenericpluginStepLoad::CompareDisplayL(CWsScreenDevice* aScreen, CFbsBitmap* aBitmap)
	{
	// Capture window display to bitmap
	CFbsBitmap* screenBitmap = new(ELeave) CFbsBitmap();
	CleanupStack::PushL(screenBitmap);
	User::LeaveIfError(screenBitmap->Create(KWinRect.Size(), iDisplayMode));
	User::LeaveIfError(aScreen->CopyScreenToBitmap(screenBitmap, KWinRect));	
	
	//Compare the window bitmap with the bitmap pass in for comparison
	TBool ret = ETrue;
	
	const TReal KErrorLimit = 0.05;
	
	TInt mismatchedPixels = 0;
	TRgb testWinPix = TRgb(0,0,0,0);
	TRgb checkWinPix = TRgb(0,0,0,0);
	for (TInt x = 0; x < KWinRect.Width(); x++)
		{
		for (TInt y = 0; y < KWinRect.Height(); y++)
			{
			screenBitmap->GetPixel(testWinPix, TPoint(x,y));
			aBitmap->GetPixel(checkWinPix, TPoint(x,y));
			
			//check if there are differeces between test Window colors and check Window colors
			if(((TReal)abs(testWinPix.Red() - checkWinPix.Red())/255) > KErrorLimit || 
					((TReal)abs(testWinPix.Blue() - checkWinPix.Blue())/255) > KErrorLimit || 
					((TReal)abs(testWinPix.Green() - checkWinPix.Green())/255) > KErrorLimit || 
					((TReal)abs(testWinPix.Alpha() - checkWinPix.Alpha())/255) > KErrorLimit)
				{
				mismatchedPixels++;  // -- Useful for debugging
				ret = EFalse;
				break;
				}
			}
		}
	
	/* INFO_PRINTF2(_L("Number of different pixels: %i"), mismatchedPixels); */ // -- Useful for debugging
	

	CleanupStack::PopAndDestroy(screenBitmap);	
	
	
	
	return ret;
	}