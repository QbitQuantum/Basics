int _tmain(int argc, _TCHAR* argv[])
{
	//----------------
	hLog = fopen("log.txt", "w");
	LPCTSTR path = L".\\options.ini";

	TCHAR stecilPicturePathResult[4096];
	TCHAR maskedPicturePathResult[4096];
	TCHAR serverPortResult[255];
	TCHAR serverIPResult[255];
	TCHAR listenUDPPortResult[255];
	TCHAR listenUDPIPResult[255];
	TCHAR colorResult[255];
	TCHAR shiftXResult[255];
	TCHAR shiftYResult[255];
	TCHAR isEyeWindowShowResult[255];
	TCHAR isEyePositionWindowShowResult[255];
	TCHAR isCalibrateResult[255];

	char buffer[4096];

	GetPrivateProfileString(_T("Base"), _T("stecilPicturePath"), _T(""), stecilPicturePathResult, sizeof(buffer), path);
	GetPrivateProfileString(_T("Base"), _T("maskedPicturePath"), _T(""), maskedPicturePathResult, sizeof(buffer), path);
	GetPrivateProfileString(_T("Base"), _T("serverPort"), _T(""), serverPortResult, 255, path);
	GetPrivateProfileString(_T("Base"), _T("serverIP"), _T(""), serverIPResult, 255, path);
	GetPrivateProfileString(_T("Base"), _T("listenUDPPort"), _T(""), listenUDPPortResult, 255, path);
	GetPrivateProfileString(_T("Base"), _T("listenUDPIP"), _T(""), listenUDPIPResult, 255, path);
	GetPrivateProfileString(_T("Base"), _T("color"), _T(""), colorResult, 255, path);
	GetPrivateProfileString(_T("Base"), _T("shiftX"), _T(""), shiftXResult, 255, path);
	GetPrivateProfileString(_T("Base"), _T("shiftY"), _T(""), shiftYResult, 255, path);
	GetPrivateProfileString(_T("Base"), _T("isEyeWindowShow"), _T(""), isEyeWindowShowResult, 255, path);
	GetPrivateProfileString(_T("Base"), _T("isEyePositionWindowShow"), _T(""), isEyePositionWindowShowResult, 255, path);
	GetPrivateProfileString(_T("Base"), _T("isCalibrate"), _T(""), isCalibrateResult, 255, path);

	int shiftXint = _ttoi(shiftXResult);
	int shiftYint = _ttoi(shiftYResult);
	int serverPortint = _ttoi(serverPortResult);
	int listenUDPPortint = _ttoi(listenUDPPortResult);
	desiredColor = wcstoul(colorResult, NULL, 0x10);

	char serverIPChar[255];
	wcstombs(serverIPChar, serverIPResult, wcslen(serverIPResult) + 1);

	char listenUDPIPChar[255];
	wcstombs(listenUDPIPChar, listenUDPIPResult, wcslen(listenUDPIPResult) + 1);

	bool isEyeWindowShowBool = false;
	bool isEyePositionWindowShow = false;
	bool isCalibrate = false;

	if(_tcscmp(isEyeWindowShowResult, L"true") == 0){
		isEyeWindowShowBool = true;
	} 
	if(_tcscmp(isEyePositionWindowShowResult, L"true") == 0){
		isEyePositionWindowShow = true;
	}
	if(_tcscmp(isCalibrateResult, L"true") == 0){
		isCalibrate = true;
	}
	
	//getchar();
    //return 0;

	// screenMasker.exe 757575 checker4px.pgm stencil.pgm 23 45 Y"
	// parse arguments
	//E:\OrlovPA\screenMasker\screenmasker\screenMasker_bin\screenMasker_bin\screenMasker.exe 757575 bg.pgm stencil.pgm 0
	//LPWSTR *argc;
	//LPWSTR bgPath;
	//wchar_t newBgPath[] = L"E:\\OrlovPA\\screenMasker\\screenmasker\\screenMasker_bin\\screenMasker_bin\\bg.pgm";
	//wchar_t newBgPath[] = maskedPicturePathResult;
	//LPWSTR stencilPath;
	//wchar_t newStencilPath[] = L"E:\\OrlovPA\\screenMasker\\screenmasker\\screenMasker_bin\\screenMasker_bin\\stencil.pgm";

	//int localstencilX, localstencilY, localCoursor;

	//wchar_t myColor = '757575';
	//const wchar_t * myColorAdress = &myColor;
	
	
	//desiredColor = wcstoul(L"1a3399", NULL, 0x10);

	//desiredColor = 757575;

	isCoursor = 1;

	// read background and stencil to buffers
	UINT8 *bytes;
	int width;
	int height;

	//bytes = readPGM(bgPath, &width, &height);
	bytes = readPGM(maskedPicturePathResult, &width, &height);
	//bytes = readPGM(newBgPath, &width, &height);

	if(bytes == NULL)
	{
		return 1;
	}

	bgBmpBytes = bytes;
	bgBmpWidth = width;
	bgBmpHeight = height;

	//bytes = readPGM(newStencilPath, &width, &height);
	bytes = readPGM(stecilPicturePathResult, &width, &height);
	
	if(bytes == NULL){
		return 1;
	}

	stencilBmpBytes = bytes;
	stencilBmpWidth = width;
	stencilBmpHeight = height;
	//----------------

	POINT pt = {};
	HMONITOR hMon;
	MONITORINFO monitorInfo = {};
	GetCursorPos(&pt); 
	hMon = MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);

	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(hMon, &monitorInfo);

	mX = monitorInfo.rcMonitor.left;
	mY = monitorInfo.rcMonitor.top;
	mW = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	mH = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

	WNDCLASSEX wc;
	MSG msg;
	// Init wc
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = NULL;
	wc.hIconSm = NULL;
	wc.lpszClassName = toString("animation_class");
	wc.lpszMenuName = NULL;

	// Register wc
	if ( !RegisterClassEx(&wc) ) {
		MessageBox( NULL, toString("Failed to register window class."), toString("Error"), MB_OK );
		return 0;
	}
	// Make window
	hwnd = CreateWindowEx(
		//WS_EX_APPWINDOW,
		WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT,
		toString("animation_class"),
		toString("Animation"),
		WS_POPUP | WS_SYSMENU,
		mX, mY, mW, mH,
		NULL, NULL, GetModuleHandle(0), NULL );

	assert(hwnd);


	/*
	RECT rcClient, rcWindow;
	POINT ptDiff;
	// Get window and client sizes
	GetClientRect( hwnd, &rcClient );
	GetWindowRect( hwnd, &rcWindow );
	// Find offset between window size and client size
	ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
	ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
	// Resize client
	MoveWindow( hwnd, rcWindow.left, rcWindow.top, width + ptDiff.x, height + ptDiff.y, false);
	

	//UpdateLayeredWindow(hwnd, NULL, &ptDst, &siz, hdcOutBmp, &ptZero, 0, &blendFunc, ULW_ALPHA);

	//SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0x0, LWA_COLORKEY);
	*/

	ShowWindow( hwnd, SW_SHOWDEFAULT );
	UpdateWindow( hwnd );

	initGpuResources(	bgBmpBytes, 
		stencilBmpBytes, 
		bgBmpWidth, 
		bgBmpHeight, 
		stencilBmpHeight, 
		stencilBmpWidth, 
		mW, 
		mH	);


	//****************************
	AccuracyStruct accuracyData; 
	SystemInfoStruct systemInfoData; 
	CalibrationStruct calibrationData;
	int ret_calibrate = 0, ret_validate = 0, ret_connect = 0; 
	char c = ' ';
	char repeat = ' ';

	std::cout << "Output from iViewXAPI Demo"<< std::endl;

	// define logger 
	iV_SetLogger(1, "ScreenMasker.txt");
	std::cout << "ScreenMasker on iViewX API" << std::endl;

	// connect to iViewX 
	ret_connect = iV_Connect(serverIPChar, serverPortint, listenUDPIPChar, listenUDPPortint);
	

	switch(ret_connect)
	{
		case RET_SUCCESS:
			std::cout <<  "Connection was established successfully" << std::endl;

			// read out meta data from iViewX 
			std::cout << "GetSystemInfo: " << iV_GetSystemInfo(&systemInfoData) << std::endl;
			std::cout << "SystemInfo ETSystem: " << systemInfoData.iV_ETDevice << std::endl;
			std::cout << "SystemInfo iV_Version: " << systemInfoData.iV_MajorVersion << "." << systemInfoData.iV_MinorVersion << "." << systemInfoData.iV_Buildnumber << std::endl;
			std::cout << "SystemInfo API_Version: " << systemInfoData.API_MajorVersion << "." << systemInfoData.API_MinorVersion << "." << systemInfoData.API_Buildnumber << std::endl;
			std::cout << "SystemInfo samplerate: " << systemInfoData.samplerate << std::endl;

			break;
		case ERR_COULD_NOT_CONNECT:
			std::cout <<  "Connection could not be established" << std::endl;
			break;
		case ERR_WRONG_PARAMETER:
			std::cout <<  "Wrong Parameter used" << std::endl;
			break;
		default:
			std::cout <<  "Any other error appeared" << std::endl;
			return 0;
	}

	if(ret_connect == RET_SUCCESS)
	{
		calibrationData.method = 5;
		calibrationData.speed = 0;
		calibrationData.displayDevice = 0;
		calibrationData.targetShape = 20;
		calibrationData.foregroundBrightness = 250;
		calibrationData.backgroundBrightness = 100;
		calibrationData.autoAccept = 1;
		calibrationData.targetSize = 10;
		calibrationData.visualization = 1;
		strcpy(calibrationData.targetFilename, "");

		iV_SetupCalibration(&calibrationData);

		// start calibration
		//std::cout <<  "Do you want to calibrate? (y)es | (n)o" << std::endl;
		//c = getchar();

		if(isCalibrate){
			ret_calibrate = iV_Calibrate();

			switch(ret_calibrate){
				case RET_SUCCESS:
					std::cout <<  "Calibration done successfully" << std::endl;
					
					// start validation
					ret_validate = iV_Validate();

					break;
				case ERR_NOT_CONNECTED:
					std::cout <<  "iViewX is not reachable" << std::endl;
					break;
				case ERR_WRONG_PARAMETER:
					std::cout <<  "Wrong Parameter used" << std::endl;
					break;
				case ERR_WRONG_DEVICE:
					std::cout <<  "Not possible to calibrate connected Eye Tracking System" << std::endl;
					break;
				default:
					std::cout <<  "An unknown error appeared" << std::endl;
					break;
			}

		}

		// show accuracy only if validation was successful
		if(ret_validate == RET_SUCCESS){
			std::cout << "iV_GetAccuracy: " << iV_GetAccuracy(&accuracyData, 0) << std::endl;
			std::cout << "AccuracyData DevX: " << accuracyData.deviationLX << " DevY: " << accuracyData.deviationLY << std::endl;
			//getchar();

		}

		if(isEyeWindowShowBool){
			iV_ShowEyeImageMonitor();
		}
		
		if(isEyePositionWindowShow){
			iV_ShowTrackingMonitor();
			iV_ShowSceneVideoMonitor();
		}

		// start data output via callback function
		// define a callback function for receiving samples 
		iV_SetSampleCallback(SampleCallbackFunction);
		iV_SetTrackingMonitorCallback(TrackingMonitorCallbackFunction);

		while ( GetMessage(&msg, 0, 0, NULL) > 0 ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		/*
		getchar();

		iV_SetSampleCallback(NULL);
		iV_SetTrackingMonitorCallback(NULL);

		std::cout << "iV_Disconnect: " << iV_Disconnect() << std::endl;

		getchar();
		*/
	}

	freeGpuResources();
	fclose(hLog);

	return 0;
}