//==============================================================================
//==============================================================================
geBoolean GMain_Startup(DRV_DriverHook *Hook)
{
 
	int32			VidMode;

	//SetEnvironmentVariable("SST_GAMMA", "1.0");

	switch(Hook->Mode)
	{
		case 0:
		{
			ClientWindow.Width = 512;
			ClientWindow.Height = 384;
			VidMode = GR_RESOLUTION_512x384;
			break;
		}
		case 1:
		{
			ClientWindow.Width = 640;
			ClientWindow.Height = 480;
			VidMode = GR_RESOLUTION_640x480;
			break;
		}
		case 2:
		{
			ClientWindow.Width = 800;
			ClientWindow.Height = 600;
			VidMode = GR_RESOLUTION_800x600;
			break;
		}
		case 3:
		{
			ClientWindow.Width = 1024;
			ClientWindow.Height = 768;
			VidMode = GR_RESOLUTION_1024x768;
			break;
		}
		default:
		{
			SetLastDrvError(DRV_ERROR_NULL_WINDOW, "GLIDE_DrvInit:  Invalid display mode.");
			return FALSE;
		}
	}

	ClientWindow.hWnd = Hook->hWnd;

	// Go full-screen so we won't lose the mouse
	{
		RECT	DeskTop;

		// Save the old window size
		GetWindowRect(ClientWindow.hWnd, &OldWindow);

		// Get the size of the desktop
		GetWindowRect(GetDesktopWindow(), &DeskTop);

		// Resize the window to the size of the desktop
		MoveWindow(ClientWindow.hWnd, DeskTop.left-4, DeskTop.top-40, DeskTop.right+20, DeskTop.bottom+20, TRUE);

		// Center the mouse
		SetCursorPos(ClientWindow.Width / 2, ClientWindow.Height / 2);
	}

	// initialize the Glide library 
	grGlideInit();

	// Get the info about this board
	if (!GMain_GetBoardInfo(&g_BoardInfo))
		return FALSE;

	if (g_BoardInfo.NumTMU <= 0)
	{
		SetLastDrvError(DRV_ERROR_INIT_ERROR, "GLIDE_DrvInit:  Not enough texture mapping units.");
		return GE_FALSE;
	}

	// select the current graphics system 
	grSstSelect(0);

	// initialize and open the graphics system 
	if (!grSstWinOpen( (U32)ClientWindow.hWnd,
              VidMode,
              GR_REFRESH_60Hz,
              GR_COLORFORMAT_ABGR,
              GR_ORIGIN_UPPER_LEFT,
              2, 1 ))
	{
		SetLastDrvError(DRV_ERROR_INIT_ERROR, "GLIDE_DrvInit:  grSstWinOpen failed.");
		return GE_FALSE;
	}

	// We know that GLIDE will be in 5-6-5 mode...
	ClientWindow.R_shift = 5+6;
	ClientWindow.G_shift = 5;
	ClientWindow.B_shift = 0;

	ClientWindow.R_mask = 0xf800;
	ClientWindow.G_mask = 0x07e0;
	ClientWindow.B_mask = 0x001f;

	ClientWindow.R_width = 5;
	ClientWindow.G_width = 6;
	ClientWindow.B_width = 5;

	SetLastDrvError(DRV_ERROR_NONE, "GMain_Startup:  No error.");

	if (!GTHandle_Startup())
	{
		SetLastDrvError(DRV_ERROR_GENERIC, "GMain_Startup:  GTHandle_Startup failed...\n");
		return GE_FALSE;
	}
	
	if (!GMain_InitGlideRegisters())
	{
		SetLastDrvError(DRV_ERROR_GENERIC, "GMain_Startup:  GMain_InitGlideRegisters failed...\n");
		return GE_FALSE;
	}

	// Init the 3d display
	//grSstControl(GR_CONTROL_ACTIVATE);
	grGammaCorrectionValue(1.0f);

	return GE_TRUE;
}