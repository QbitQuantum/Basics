//
//  FUNCTION: WndProc(HWND, unsigniert, WORD, LONG)
//
// PUPOSE:  handling of messages from main window  
//
//  WM_COMMAND	- Processes message coming from the menu and the controls (e.g. button)
//  WM_PAINT	- Re/Drawing of main window
//  WM_DESTROY	- Ends application
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// handling commands from menu and controls (e.g. buttons)
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;

		case IDC_CHECK_BOX_BASE:
			if (videofolderPath.compare("") == 0 && showVideoConfigWarning){
				MessageBox(hWnd, "You haven't configure the video directory, which may lead to an error when trying to play video.", "WARNNING", MB_OK);
				showVideoConfigWarning = false;
			}

			DestroyImage(MATCH_TYPE);
			HandleMovement(0);
			//need to first disable, then enable, otherwise same button will be disabled by mistake
			EnableMatchImageInteractions(false);
			EnableVideoInteractions(true);
			EnableNavigator(true);
			EnableBaseImageInteractions(true);

			break;

		case IDC_CHECK_BOX_MATCH:
			HandleMovement(0);
			//need to first disable, then enable, otherwise same button will be disabled by mistake
			EnableBaseImageInteractions(false);
			EnableMatchImageInteractions(true);
			EnableNavigator(true);
			break;

		case IDC_BUTTON_LEFT:
			HandleMovement(-1);
			break;

		case IDC_BUTTON_RIGHT:
			HandleMovement(+1);
			break;

		case IDC_BUTTON_SAVE:
		{
			if (BST_CHECKED == SendMessage(check_box_handles[0], BM_GETCHECK, 0, 0)){
				int trackID = Get_Number(trackId_handle);
				int type = UNKNOW;
				if (BST_CHECKED == SendMessage(check_box_handles[2], BM_GETCHECK, 0, 0)){
					type = PARK;
				}
				else if (BST_CHECKED == SendMessage(check_box_handles[3], BM_GETCHECK, 0, 0)){
					type = LEAVE;
				}

				int spotNum = Get_Number(spot_handle);
				if (spotNum < 0 || type == UNKNOW){
					MessageBox(hWnd, "Either SpotNum or Park/Leave type is not set yet, please check and save again!", "WARNING", MB_OK);
				}
				else{
					if (saveSpotConfig(type, trackID, spotNum)){
						Set_Text(spot_handle, "");
						PostMessage(type == PARK ? check_box_handles[2] : check_box_handles[3], BM_SETCHECK, BST_UNCHECKED, 0);
					}
				}
			}
			else if (BST_CHECKED == SendMessage(check_box_handles[1], BM_GETCHECK, 0, 0)){
				if (BST_CHECKED == SendMessage(merge_checkbox_handle, BM_GETCHECK, 0, 0)){
					if (saveMerge(curBaseImageInfo->trackNum, curMatchImageInfo->trackNum)){
						PostMessage(merge_checkbox_handle, BM_SETCHECK, BST_UNCHECKED, 0);
					}
				}
				else{
					MessageBox(hWnd, "The merge radio button is not set yet, please check and save again!", "WARNING", MB_OK);
				}
			}
			else{
				MessageBox(hWnd, "This should never be shown!", "ERROR", MB_OK);
			}
		}
			break;

		case IDC_BUTTON_DO_IT:
		{
			char buf[15];
			int x = GetWindowText(button_handle, buf, 15);
			if (strcmp(buf, "PLAY") == 0){
				char videoName[MAX_PATH];
				x = GetWindowText(videoName_handle, videoName, MAX_PATH);
				string fullVideoPath = videofolderPath + "\\" + string(videoName);
				if (vio->Get_Video_from_File((char*)fullVideoPath.c_str())){
					Set_Text(button_handle, "STOP");

					int start = max(Get_Number(from_handle), 0);
					int end = max(Get_Number(to_handle), 0);
					start = start > end ? 0 : start;
					vio->Play_Video(start, end);

					Set_Text(button_handle, "PLAY");
				}
				else{
					MessageBox(hWnd, "Failed to open the video file, please verify your video dir setup!", "SORRY", MB_OK);
				}
			}
			else
			{
				vio->Stop_Video();
				Set_Text(button_handle, "PLAY");
			}
		}
		break;

		case IDM_IMAGEOP_LOADIMAGEFOLDER:
		{
			if (fd->OpenDirectory()){
				imagefolderPath = fd->Get_ImgFolder_Name();
				std::vector<string> imageNameList;
				fd->GetFilesInDirectory(imageNameList, imagefolderPath, ".jpg");
				Set_Text(img_pathinfo_handle, (char*)imagefolderPath.c_str());
				imginfoset = new ImageInfoSet(imageNameList);
				EnableBaseImage(true);
			}
		}
		break;

		case IDM_IMAGEOP_SELECTVIDEOFOLDER:
		{
			if (fd->OpenDirectory()){
				videofolderPath = fd->Get_ImgFolder_Name();
				//fd->GetFilesInDirectory(imageNameList, imagefolderPath, ".jpg");
				Set_Text(video_pathinfo_handle, (char*)videofolderPath.c_str());
			}
		}
		break;

		case IDM_IMAGEOP_SELECTOUTPUTFILE:
		{
			if (fd->OpenFile()){
				closeOutputFile();
				outputPath = fd->Get_Name();
				outputStream.open(outputPath, ios::out | ios::app);

				time_t now = time(0); 
				char buf[100];
				ctime_s(buf, 100, &now);
				appendTxtToOutput("OpenFile : " + outputPath + " @ " + string(buf));
			}
			else{
				MessageBox(hWnd, "Failed to open the output file!", "SORRY", MB_OK);
			}
			
		}
		break;

		case IDM_EXIT:
			vio->Stop_Video();
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;

	case WM_CREATE:
	{
		fd = new FileDialog(hWnd);
		vio = new Video_OP();

		// Static control as caption for path info textfield
		img_path_caption_handle = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "ImageDir:", WS_CHILD | WS_VISIBLE,
			10, 10, 70, 30, hWnd, (HMENU)IDC_STATIC_IMAGE_PATH, GetModuleHandle(NULL), NULL);
		//SetBkColor(img_path_caption_handle, GetSysColor(COLOR_WINDOW));

		// Textfield for image pathinfo
		img_pathinfo_handle = CreateWindowEx(WS_EX_STATICEDGE, "STATIC", "", WS_CHILD | WS_VISIBLE,
			85, 10, 440, 30, hWnd, (HMENU)IDC_EDIT_IMAGE_PATH, GetModuleHandle(NULL), NULL);

		video_path_caption_handle = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "VideoDir:", WS_CHILD | WS_VISIBLE,
			10, 50, 70, 30, hWnd, (HMENU)IDC_STATIC_VIDEO_PATH, GetModuleHandle(NULL), NULL);
		// Textfield for video pathinfo
		video_pathinfo_handle = CreateWindowEx(WS_EX_STATICEDGE, "STATIC", "", WS_CHILD | WS_VISIBLE,
			85, 50, 440, 30, hWnd, (HMENU)IDC_EDIT_VIDEO_PATH, GetModuleHandle(NULL), NULL);

		//videoName
		CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "CurVideo:", WS_CHILD | WS_VISIBLE,
			10, 90, 70, 30, hWnd, (HMENU)IDC_STATIC_VIDENAME, GetModuleHandle(NULL), NULL);
		videoName_handle = CreateWindowEx(WS_EX_STATICEDGE, "STATIC", "", WS_CHILD | WS_VISIBLE,
			85, 90, 300, 30, hWnd, (HMENU)IDC_EDIT_VIDEONAME, GetModuleHandle(NULL), NULL);

		//trackId
		CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "CurTrack:", WS_CHILD | WS_VISIBLE,
			400, 90, 70, 30, hWnd, (HMENU)IDC_STATIC_TRACK, GetModuleHandle(NULL), NULL);
		trackId_handle = CreateWindowEx(WS_EX_STATICEDGE, "STATIC", "", WS_CHILD | WS_VISIBLE,
			475, 90, 50, 30, hWnd, (HMENU)IDC_EDIT_TRACK, GetModuleHandle(NULL), NULL);

		int horzSeparatorPos = 130;
		CreateWindowEx(WS_EX_CLIENTEDGE, "Static", "", SS_ETCHEDHORZ | WS_CHILD | WS_VISIBLE, 5, horzSeparatorPos, 535, 10, hWnd, NULL, GetModuleHandle(NULL), NULL);

		// Static control saying FROM
		CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Video Info Section", WS_CHILD | WS_VISIBLE,
			10, horzSeparatorPos + 10, 145, 30, hWnd, NULL, GetModuleHandle(NULL), NULL);

		from_caption_handle = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Frame start:", WS_CHILD | WS_VISIBLE,
			10, horzSeparatorPos + 50, 90, 30, hWnd, (HMENU)IDC_STATIC_START, GetModuleHandle(NULL), NULL);
		// Textfield to fill in frame where video shall start from
		from_handle = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE,
			105, horzSeparatorPos + 50, 50, 30, hWnd, (HMENU)IDC_EDIT_START, GetModuleHandle(NULL), NULL);

		// Static control saying TO
		to_caption_handle = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Frame end:", WS_CHILD | WS_VISIBLE,
			10, horzSeparatorPos + 90, 90, 30, hWnd, (HMENU)IDC_STATIC_STOP, GetModuleHandle(NULL), NULL);
		// Textfield for telling program where to stop 
		to_handle = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE,
			105, horzSeparatorPos + 90, 50, 30, hWnd, (HMENU)IDC_EDIT_STOP, GetModuleHandle(NULL), NULL);

		// Button to start processes which were selected in the menu
		button_handle = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "PLAY", WS_CHILD | WS_VISIBLE,
			40, horzSeparatorPos + 130, 80, 40, hWnd, (HMENU)IDC_BUTTON_DO_IT, GetModuleHandle(NULL), NULL);

		int vertSeparatorPos = 170;
		CreateWindowEx(WS_EX_CLIENTEDGE, "Static", "", SS_ETCHEDVERT | WS_CHILD | WS_VISIBLE, vertSeparatorPos, horzSeparatorPos + 1, 100, 181, hWnd, NULL, GetModuleHandle(NULL), NULL);

		// commoncontrol DLL needs to be loaded (needed for trackbar) 
		//Attention: also requires <commctrl.h> and comctl32.lib
		INITCOMMONCONTROLSEX icc;
		icc.dwICC = ICC_BAR_CLASSES;
		icc.dwSize = sizeof(icc);
		bool z = InitCommonControlsEx(&icc);

		//frame diff and distance filters
		framediff_caption_handle = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Framediff Thres:", WS_CHILD | WS_VISIBLE,
			vertSeparatorPos + 10, horzSeparatorPos + 10, 110, 30, hWnd, (HMENU)IDC_STATIC_FRAME_DIFF, GetModuleHandle(NULL), NULL);
		framediff_handle = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", std::to_string(DEFAULT_FRAMEDIFF_THRES).c_str(), WS_CHILD | WS_VISIBLE,
			vertSeparatorPos + 125, horzSeparatorPos + 10, 50, 30, hWnd, (HMENU)IDC_EDIT_FRAME_DIFF, GetModuleHandle(NULL), NULL);

		int thirdcolPos = vertSeparatorPos + 180;

		distance_caption_handle = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Distance Thres:", WS_CHILD | WS_VISIBLE,
			thirdcolPos + 10, horzSeparatorPos + 10, 110, 30, hWnd, (HMENU)IDC_STATIC_DISTANCE_THRES, GetModuleHandle(NULL), NULL);
		distance_handle = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", std::to_string(DEFAULT_DISTANCE_THRES).c_str(), WS_CHILD | WS_VISIBLE,
			thirdcolPos + 125, horzSeparatorPos + 10, 50, 30, hWnd, (HMENU)IDC_EDIT_DISTANCE_THRES, GetModuleHandle(NULL), NULL);

		//base/match image selector
		check_box_handles[0] = CreateWindowEx(WS_EX_STATICEDGE, "BUTTON", "Base Image", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
			vertSeparatorPos + 10, horzSeparatorPos + 50, 165, 30, hWnd, (HMENU)IDC_CHECK_BOX_BASE, GetModuleHandle(NULL), NULL);
		check_box_handles[1] = CreateWindowEx(WS_EX_STATICEDGE, "BUTTON", "Match Image", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			vertSeparatorPos + 10, horzSeparatorPos + 90, 165, 30, hWnd, (HMENU)IDC_CHECK_BOX_MATCH, GetModuleHandle(NULL), NULL);

		//merge checkbox
		merge_checkbox_handle = CreateWindowEx(WS_EX_STATICEDGE, "BUTTON", "Merge Match to Base", WS_CHILD | BS_AUTOCHECKBOX,
			thirdcolPos + 10, horzSeparatorPos + 50, 165, 30, hWnd, (HMENU)IDC_CHECK_BOX_MERGE, GetModuleHandle(NULL), NULL);

		//base/match image selector
		check_box_handles[2] = CreateWindowEx(WS_EX_STATICEDGE, "BUTTON", "Park", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
			thirdcolPos + 10, horzSeparatorPos + 50, 80, 30, hWnd, (HMENU)IDC_CHECK_BOX_PARK, GetModuleHandle(NULL), NULL);
		check_box_handles[3] = CreateWindowEx(WS_EX_STATICEDGE, "BUTTON", "Leave", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			thirdcolPos + 95, horzSeparatorPos + 50, 80, 30, hWnd, (HMENU)IDC_CHECK_BOX_LEAVE, GetModuleHandle(NULL), NULL);

		//change spot
		CreateWindowEx(WS_EX_TRANSPARENT, "Static", "New Spot:", WS_CHILD | WS_VISIBLE,
			thirdcolPos + 10, horzSeparatorPos + 90, 110, 30, hWnd, (HMENU)IDC_STATIC_SPOT, GetModuleHandle(NULL), NULL);
		spot_handle = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE,
			thirdcolPos + 125, horzSeparatorPos + 90, 50, 30, hWnd, (HMENU)IDC_EDIT_SPOT, GetModuleHandle(NULL), NULL);

		//navigator
		leftnavi_button_handle = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "<---", WS_CHILD | WS_VISIBLE,
			vertSeparatorPos + 100 - 80, horzSeparatorPos + 130, 80, 40, hWnd, (HMENU)IDC_BUTTON_LEFT, GetModuleHandle(NULL), NULL);
		rightnavi_button_handle = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "--->", WS_CHILD | WS_VISIBLE,
			vertSeparatorPos + 185 - 80, horzSeparatorPos + 130, 80, 40, hWnd, (HMENU)IDC_BUTTON_RIGHT, GetModuleHandle(NULL), NULL);
		//save review result
		save_button_handle = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "SAVE", WS_CHILD | WS_VISIBLE,
			vertSeparatorPos + 275, horzSeparatorPos + 130, 80, 40, hWnd, (HMENU)IDC_BUTTON_SAVE, GetModuleHandle(NULL), NULL);

		horzSeparatorPos += 175;
		CreateWindowEx(WS_EX_CLIENTEDGE, "Static", "", SS_ETCHEDHORZ | WS_CHILD | WS_VISIBLE, 5, horzSeparatorPos, 535, 10, hWnd, NULL, GetModuleHandle(NULL), NULL);
		
		CreateWindowEx(WS_EX_TRANSPARENT, "Static", "Latest Logs:", WS_CHILD | WS_VISIBLE,
			10, horzSeparatorPos + 10, 515, 30, hWnd, (HMENU)IDC_STATIC_RESULT, GetModuleHandle(NULL), NULL);
		result_handle = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", " Waiting for configurting the output file!", WS_CHILD | WS_VISIBLE,
			10, horzSeparatorPos + 40, 515, 110, hWnd, (HMENU)IDC_EDIT_RESULT, GetModuleHandle(NULL), NULL);

		EnableAllInteractions(false);

		// Gets Menu Handle
		menu_handle = GetMenu(hWnd);
		CheckMenuItem(menu_handle, IDM_PLAY_MOV, MF_CHECKED);
		
	}
	break;
	// press left mouse button somewhere in the main window to uncheck all radiobuttons (optionbuttons)
	case WM_LBUTTONDOWN:
	{
		if (BST_CHECKED == SendMessage(check_box_handles[0], BM_GETCHECK, 0, 0)){
			if (showClearTutorial){
				int ret = MessageBox(hWnd, "Enable the function to clear park/leave radio when clicking the background or a non-active component?", "You just clicked the background or a non-active component", MB_YESNO);
				showClearTutorial = false;
				enableClear = (ret == IDYES);
			}
		}
		
		if (enableClear){
			SendMessage(check_box_handles[2], BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(check_box_handles[3], BM_SETCHECK, BST_UNCHECKED, 0);
		}
	}
	break;

	case WM_KEYDOWN:
	{
		int x = 0;
		switch (wParam)
		{
		case VK_LEFT:
			HandleMovement(-1);
			break;

		case VK_RIGHT:
			HandleMovement(+1);
			break;
		}
	}
	break;

	case WM_DESTROY:
		vio->Stop_Video();
		DestroyImage(BASE_TYPE);
		DestroyImage(MATCH_TYPE);
		closeOutputFile();

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}