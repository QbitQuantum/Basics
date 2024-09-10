void CTScreenDevice::TwipsCacheFlushL()
	{
	RWsSession session;
	CWsScreenDevice* device;
	CFont* font;
	CFont* font2;
	const TFontSpec fontspec(KTestFontTypefaceName,250);
	TPixelsTwipsAndRotation sizeAndRotation;

	// create a CWsScreenDevice instance
	User::LeaveIfError(session.Connect());
	device=new(ELeave) CWsScreenDevice(session);
	device->Construct(iTest->iScreenNumber);

	// Record a font height for use by latter tests
	User::LeaveIfError(device->GetNearestFontToDesignHeightInTwips(font,fontspec));
	const TInt height0=font->HeightInPixels();
	device->ReleaseFont(font);

	// 1. find font with best-matching height in twips,
	// 2. change twips size of the screen (leaving pixel-size same),
	// 3. find font with best-matching height in twips,
	// 4. make sure that the newly found font is not the same as previous and has the different height in pixels
	device->GetDefaultScreenSizeAndRotation(sizeAndRotation);
#if defined(EXTRA_LOGGING)
	_LIT(KLog1,"Font height: %d for unchanged device.   pixels=%d,%d  twips=%d,%d");
	LOG_MESSAGE6(KLog1,height0,sizeAndRotation.iPixelSize.iWidth,sizeAndRotation.iPixelSize.iHeight
						,sizeAndRotation.iTwipsSize.iWidth,sizeAndRotation.iTwipsSize.iHeight);
#endif
	sizeAndRotation.iTwipsSize.iHeight=2000;
	sizeAndRotation.iTwipsSize.iWidth =3000;
	device->SetScreenSizeAndRotation(sizeAndRotation);

	User::LeaveIfError(device->GetNearestFontToDesignHeightInTwips(font,fontspec));
	TInt height=font->HeightInPixels();
#if defined(EXTRA_LOGGING)
	_LIT(KLog2,"Font height: %d for device with twips set to 2000x3000");
	LOG_MESSAGE2(KLog2,height);
#endif
	TFontSpec returnedSpec=font->FontSpecInTwips();

	sizeAndRotation.iTwipsSize.iHeight=4000;
	sizeAndRotation.iTwipsSize.iWidth =6000;
	device->SetScreenSizeAndRotation(sizeAndRotation);

	User::LeaveIfError(device->GetNearestFontToDesignHeightInTwips(font2,fontspec));
	TInt height2=font2->HeightInPixels();
	TFontSpec returnedSpec2 = font2->FontSpecInTwips();
#if defined(EXTRA_LOGGING)
	_LIT(KLog3,"Font height: %d for device with twips set to 4000x6000");
	LOG_MESSAGE2(KLog3,height2);
#endif

	TEST(font!=font2);
	TEST(height!=height2);
	_LIT(KLogErrM,"Font Heights in pixels match unexpectantly, height=%d");
	if (height==height2)
		INFO_PRINTF2(KLogErrM,height);

	device->ReleaseFont(font2);
	device->ReleaseFont(font);

	// 1. find font with best-matching height in twips,
	// 2. change pixel size of the screen (leaving twip-size same),
	// 3. find font with best-matching height in twips,
	// 4. make sure that the newly found font is not the same as previous and has the different height in pixels
	device->GetDefaultScreenSizeAndRotation(sizeAndRotation);
	sizeAndRotation.iPixelSize.iHeight=240;
	sizeAndRotation.iPixelSize.iWidth =640;
	device->SetScreenSizeAndRotation(sizeAndRotation);

	User::LeaveIfError(device->GetNearestFontToDesignHeightInTwips(font,fontspec));
	height=font->HeightInPixels();
	returnedSpec=font->FontSpecInTwips();
#if defined(EXTRA_LOGGING)
	_LIT(KLog4,"Font height: %d for device with pixels set to 240x640   twips=%d,%d");
	LOG_MESSAGE4(KLog4,height,sizeAndRotation.iTwipsSize.iWidth,sizeAndRotation.iTwipsSize.iHeight);
#endif

	sizeAndRotation.iPixelSize.iHeight=480;
	sizeAndRotation.iPixelSize.iWidth =1280;
	device->SetScreenSizeAndRotation(sizeAndRotation);

	User::LeaveIfError(device->GetNearestFontToDesignHeightInTwips(font2,fontspec));
	height2=font2->HeightInPixels();
	returnedSpec2=font2->FontSpecInTwips();
#if defined(EXTRA_LOGGING)
	_LIT(KLog5,"Font height: %d for device with pixels set to 480x1280");
	LOG_MESSAGE2(KLog5,height2);
#endif

	TEST(font!=font2);
	TEST(height!=height2);
	if (height==height2)
		INFO_PRINTF2(KLogErrM,height);

	device->ReleaseFont(font2);
	device->ReleaseFont(font);

	// 1. double the width and height of screen in both pixels and twips
	// 2. find font with best-matching height in twips,
	// 3. make sure that the newly found font is the same as previous and has the same height in pixels
	device->GetDefaultScreenSizeAndRotation(sizeAndRotation);
	device->SetScreenSizeAndRotation(sizeAndRotation);
	User::LeaveIfError(device->GetNearestFontToDesignHeightInTwips(font,fontspec));
	sizeAndRotation.iPixelSize.iHeight*=2;
	sizeAndRotation.iPixelSize.iWidth *=2;
	sizeAndRotation.iTwipsSize.iHeight*=2;
	sizeAndRotation.iTwipsSize.iWidth *=2;
	device->SetScreenSizeAndRotation(sizeAndRotation);

	User::LeaveIfError(device->GetNearestFontToDesignHeightInTwips(font2,fontspec));
	height2=font2->HeightInPixels();
#if defined(EXTRA_LOGGING)
	_LIT(KLog6,"Font height: %d for device doubled size.   pixels=%d,%d  twips=%d,%d");
	LOG_MESSAGE6(KLog6,height2,sizeAndRotation.iPixelSize.iWidth,sizeAndRotation.iPixelSize.iHeight
							,sizeAndRotation.iTwipsSize.iWidth,sizeAndRotation.iTwipsSize.iHeight);
#endif

	TEST(font==font2);
	TEST(height0==height2);
	_LIT(KLogErrD,"Font Heights in pixels don't match, expected=%d, actual=%d");
	if (height0!=height2)
		INFO_PRINTF3(KLogErrD,height0,height2);

	device->ReleaseFont(font2);
	device->ReleaseFont(font);

	// 1. swap width and height sizes of screen for both pixels and twips
	// 2. find font with best-matching height in twips,
	// 3. make sure that the newly found font is the same as previous and has the same height in pixels
	device->GetDefaultScreenSizeAndRotation(sizeAndRotation);
	device->SetScreenSizeAndRotation(sizeAndRotation);
	User::LeaveIfError(device->GetNearestFontToDesignHeightInTwips(font,fontspec));
	TInt swap=sizeAndRotation.iPixelSize.iHeight;
	sizeAndRotation.iPixelSize.iHeight=sizeAndRotation.iPixelSize.iWidth;
	sizeAndRotation.iPixelSize.iWidth =swap;
	swap=sizeAndRotation.iTwipsSize.iHeight;
	sizeAndRotation.iTwipsSize.iHeight=sizeAndRotation.iTwipsSize.iWidth;
	sizeAndRotation.iTwipsSize.iWidth =swap;
	device->SetScreenSizeAndRotation(sizeAndRotation);
	User::LeaveIfError(device->GetNearestFontToDesignHeightInTwips(font2,fontspec));
	height2 = font2->HeightInPixels();
#if defined(EXTRA_LOGGING)
	_LIT(KLog7,"Font height: %d for device rotated size.   pixels=%d,%d  twips=%d,%d");
	LOG_MESSAGE6(KLog7,height2,sizeAndRotation.iPixelSize.iWidth,sizeAndRotation.iPixelSize.iHeight
							,sizeAndRotation.iTwipsSize.iWidth,sizeAndRotation.iTwipsSize.iHeight);
#endif

	TEST(font==font2);
	TEST(height0==height2);
	if (height0!=height2)
		INFO_PRINTF3(KLogErrD,height0,height2);

	device->ReleaseFont(font2);
	device->ReleaseFont(font);

	delete device;
	session.Close();
	}