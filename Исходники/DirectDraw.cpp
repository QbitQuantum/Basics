Drawable::Drawable(DirectDrawWriter &writer) :
	isOK(false), isOverlay(false), paused(false),
	writer(writer),
	flip(0),
	DDraw(NULL), DDClipper(NULL), DDSPrimary(NULL), DDSSecondary(NULL), DDSBackBuffer(NULL), DDrawColorCtrl(NULL),
	DwmEnableComposition(NULL)
{
	setMouseTracking(true);
	grabGesture(Qt::PinchGesture);
	if (DirectDrawCreate(NULL, &DDraw, NULL) == DD_OK && DDraw->SetCooperativeLevel(NULL, DDSCL_NORMAL) == DD_OK)
	{
		DDSURFACEDESC ddsd_primary = { sizeof ddsd_primary };
		ddsd_primary.dwFlags = DDSD_CAPS;
		ddsd_primary.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		if (DDraw->CreateSurface(&ddsd_primary, &DDSPrimary, NULL) == DD_OK)
		{
			LPDIRECTDRAWSURFACE DDrawTestSurface;
			DDSURFACEDESC ddsd_test = { sizeof ddsd_test };
			ddsd_test.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
			ddsd_test.dwWidth  = 8;
			ddsd_test.dwHeight = 2;
			ddsd_test.ddpfPixelFormat.dwSize = sizeof ddsd_test.ddpfPixelFormat;
			ddsd_test.ddpfPixelFormat.dwFlags = DDPF_FOURCC;
			ddsd_test.ddpfPixelFormat.dwFourCC = MAKEFOURCC('Y', 'V', '1', '2');

			/* Overlay YV12 test */
			if (QSysInfo::windowsVersion() < QSysInfo::WV_6_2) //Windows 8 and 10 can't disable DWM, so overlay won't work
			{
				DDCAPS ddCaps = { sizeof ddCaps };
				DDraw->GetCaps(&ddCaps, NULL);
				if (ddCaps.dwCaps & (DDCAPS_OVERLAY | DDCAPS_OVERLAYFOURCC | DDCAPS_OVERLAYSTRETCH))
				{
					ddsd_test.ddsCaps.dwCaps = DDSCAPS_OVERLAY | DDSCAPS_VIDEOMEMORY;
					if (DDraw->CreateSurface(&ddsd_test, &DDrawTestSurface, NULL) == DD_OK)
					{
						RECT destRect = { 0, 0, 1, 1 };
						HRESULT res = DDrawTestSurface->UpdateOverlay(NULL, DDSPrimary, &destRect, DDOVER_SHOW, NULL);
						if (res == DDERR_OUTOFCAPS && QSysInfo::windowsVersion() >= QSysInfo::WV_6_0)
						{
							/* Disable DWM to use overlay */
							DwmEnableComposition = (DwmEnableCompositionProc)GetProcAddress(GetModuleHandleA("dwmapi.dll"), "DwmEnableComposition");
							if (DwmEnableComposition)
							{
								if (DwmEnableComposition(DWM_EC_DISABLECOMPOSITION) == S_OK)
									res = DDrawTestSurface->UpdateOverlay(NULL, DDSPrimary, &destRect, DDOVER_SHOW, NULL);
								else
									DwmEnableComposition = NULL;
							}
						}
						if (res == DD_OK)
						{
							DDrawTestSurface->UpdateOverlay(NULL, DDSPrimary, NULL, DDOVER_HIDE, NULL);

							setAutoFillBackground(true);
							setPalette(QColor(ColorKEY));
							connect(&QMPlay2Core, SIGNAL(videoDockMoved()), this, SLOT(updateOverlay()));
							connect(&QMPlay2Core, SIGNAL(videoDockVisible(bool)), this, SLOT(overlayVisible(bool)));
							connect(&QMPlay2Core, SIGNAL(mainWidgetNotMinimized(bool)), this, SLOT(overlayVisible(bool)));
							connect(&visibleTim, SIGNAL(timeout()), this, SLOT(doOverlayVisible()));
							visibleTim.setSingleShot(true);

							isOK = isOverlay = true;
						}