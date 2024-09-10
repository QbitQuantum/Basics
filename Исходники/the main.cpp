LRESULT CALLBACK WndProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	HDC hDC;
	
	/*		 Структура PAINTSTRUCT содержит информации для приложения. 
			  Эта информация может быть использована для окраски
			  клиентской области окна, которым владеет приложение.
				
				HDC  hdc; 
			    BOOL fErase;		Определяет, должен ли фон быть стерт. Значение этого параметра должно быть не равно нулю, если приложение должно стирать фон.
			    RECT rcPaint;		Задает стурктуру RECT, которая определяет верхний левый и нижний правый углы прямоугольника, в котором требуется прорисовка.
				BOOL fRestore; 
				BOOL fIncUpdate; 
				BYTE rgbReserved[32]; 
*/

	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	static COLORREF textColor;
	RECT rcClient;
	int cxClient=0, cyClient=0;
	static int xInc, yInc;	
	//Внутри этой структуры координаты углов.
	//Верхний левый угол определяется двумя координатами left и top. 
	//Нижний правый соответственно определяется вдумя оставшимися координатами right и bottom.
	RECT rect;					
	int dX, dY;
	int ws, hs, wd, hd, wd_s, hd_s;
	int mouseX=0, mouseY=0;
	static BOOL isFileLoaded;
	static BOOL isFileLoaded_help;
	
	unsigned int DRAW_N=2;

	// Переменные для стандартного диалога "Open"
	static OPENFILENAME ofn;
	static char szFile[MAX_PATH];
	// Переменные для стандартного диалога "Color"
	static CHOOSECOLOR cc;          // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 

	// Переменные для стандартного диалога "Font"
	static CHOOSEFONT chf;
	static HFONT hFont;
	static LOGFONT lf;
	
	
		
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

	switch (uMsg)
	{
	case WM_CREATE: 
		
		page=1;
		success=0;
		name_change=0;
			// Инициализация структуры ofn

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = TEXT("Text Files(*.txt)\0*.txt\0");			//открывает только .txt

			// Инициализация структуры cc
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hWnd;
		cc.lpCustColors = (LPDWORD) acrCustClr;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;

		// Инициализация структуры chf
		chf.lStructSize = sizeof(CHOOSEFONT);
		chf.hwndOwner = hWnd;
		chf.lpLogFont = &lf;
		chf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
		chf.nFontType = SIMULATED_FONTTYPE;
		
	
		hDC= GetDC (hWnd);
		GetTextMetrics(hDC, &tm);
		doc.Initialize(&tm); 
		ReleaseDC(hWnd, hDC);
			
		isFileLoaded = menu.LoadFromFile (MENU);
		
		if (!isFileLoaded)
			{
				MessageBox (hWnd, "File " MENU " don't loaded ", "Error", MB_OK);
				break;
			}
		
		isFileLoaded_help = help.LoadFromFile (HELP);
		
		if (!isFileLoaded_help)
			{
				MessageBox (hWnd, "File " HELP " don't loaded ", "Error", MB_OK);
				break;
			}
		//  gдогнать размеры окна программы под размер растра bmp

		//  Для получения области клиента 
		GetClientRect (hWnd, &rect);
		dX = menu.GetWidth () - rect.right;
		dY = menu.GetHeight() - rect.bottom;
	//  Для получение прямоугольника приложения 
		GetWindowRect (hWnd, &rect);
	// Модифициpует высоту и шиpину Rect. Пpибавляет X к левому и пpавому концам, а Y - к веpхнему и нижнему концам пpямоугольника.
		InflateRect (&rect, dX/2, dY/2);
	// Посылает окну сообщение wm_Size. Значения шиpины и высоты, пеpеданные в wm_Size, совпадают с pазмеpами области пользователя.
		MoveWindow (hWnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, TRUE);
	// Освобождает общий или оконный (не влияющий на класс или локальность) контекст устpойства, делая его доступным для дpугих пpикладных задач.
		ReleaseDC (hWnd, hDC);
		
		
		break;
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

	case WM_SIZE:
		hDC = GetDC(hWnd);
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		if (cxClient > 0)
			doc.ScrollSettings(hWnd, cxClient, cyClient);

		ReleaseDC(hWnd, hDC);
		break;
//----------------------------------------------------------------------------------------------------------------
		//для прокрутки
//----------------------------------------------------------------------------------------------------------------
	case WM_VSCROLL:
		switch(LOWORD(wParam)) {
		case SB_LINEUP:
			yInc = -1;
			break;

		case SB_LINEDOWN:
			yInc = 1;
			break;

		case SB_PAGEUP:
			yInc = -(int)doc.vsi.nPage;
			break;

		case SB_PAGEDOWN:
			yInc = (int)doc.vsi.nPage;
			break;

		case SB_THUMBTRACK:
			yInc = HIWORD(wParam) - doc.vsi.nPos;
			break;

		default:
			yInc = 0;
		}

		doc.UpdateVscroll(hWnd, yInc);
		break;

	case WM_HSCROLL:
		switch(LOWORD(wParam)) {
		case SB_LINELEFT:
			xInc = -1;
			break;

		case SB_LINERIGHT:
			xInc = 1;
			break;

		case SB_PAGELEFT:
			xInc = -0.8 * (int)doc.hsi.nPage;
			break;

		case SB_PAGERIGHT:
			xInc = 0.8 * (int)doc.hsi.nPage;
			break;

		case SB_THUMBTRACK:
			xInc = HIWORD(wParam) - doc.hsi.nPos;
			break;

		default:
			xInc = 0;
		}

		doc.UpdateHscroll(hWnd, xInc);
		break;

	
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
	case WM_COMMAND:
		{

		
		switch (LOWORD(wParam))
		{
	//--------------------------------------------------------------------
		case IDM_OPEN:	
			
			page=1;
			strcpy(szFile, "");
			success = GetOpenFileName(&ofn);
			if (success)
				{
					MessageBox(hWnd, ofn.lpstrFile, 
						"OK. File was loaded.", MB_OK);
					name = ofn.lpstrFile;
					name+='\n';
					name=path_reform(name);
					--att;
					name_change=1;
				}
			else
				MessageBox(hWnd, ESC_OF,
				"ERROR! Failure or file wasn't founded ",
				MB_ICONWARNING);
			InvalidateRect (hWnd, NULL, 1);
			SendMessage (hWnd,WM_PAINT, wParam, lParam);
			break;
	//-----------------------------------------------------------------
		case ID_HELP_ABOUT:
			page=3;
			InvalidateRect (hWnd, NULL, 1);
			SendMessage (hWnd,WM_PAINT, wParam, lParam);
			break;
	//-----------------------------------------------------------------
		case IDM_EXIT:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
	//-----------------------------------------------------------------

		case ID_RUN_RUSSIAN:
			if (!success) {MessageBox(hWnd, ESC_OF,
						"ERROR! Firstly, choose the file. ",
						MB_ICONWARNING);break;}
			language=1;
			analysis_of_file (hWnd);
			out_statistic ();
			if (att<0) {MessageBox(hWnd, ESC_OF,
						"No attempts. ",
						MB_ICONWARNING);
						SendMessage(hWnd, WM_DESTROY, 0, 0); 
						break;}
			if (name_change==1){
								tempr[att] = new char[statistic_file_name.size()];
								strcpy( tempr[att], statistic_file_name.c_str() );}
			if (!doc.Open(tempr[att])) return 0;
			page=2;
			InvalidateRect (hWnd, NULL, 1);
			SendMessage (hWnd,WM_PAINT, wParam, lParam);
			name_change=0;
			break;
	//--------------------------------------------------------------			
		case ID_RUN_ENGLISH:
			if (!success) {MessageBox(hWnd, ESC_OF,
						"ERROR! Firstly, choose the file. ",
						MB_ICONWARNING); break;}
			language=2;
			analysis_of_file (hWnd);
			out_statistic ();
			if (att<0) {MessageBox(hWnd, ESC_OF,
						"No attempts. ",
						MB_ICONWARNING);
						SendMessage(hWnd, WM_DESTROY, 0, 0);
						break;}
			if (name_change==1){
							tempr[att] = new char[statistic_file_name.size()];
							strcpy( tempr[att], statistic_file_name.c_str() );}
			if (!doc.Open(tempr[att])) return 0;
			page=2;
			InvalidateRect (hWnd, NULL, 1);
			SendMessage (hWnd,WM_PAINT, wParam, lParam);
			name_change=0;
			break;	
	//-------------------------------------------------------------	
		case ID_RUN_RUS:
			if (!success) {MessageBox(hWnd, ESC_OF,
						"No attempts. ",
						MB_ICONWARNING);
						SendMessage(hWnd, WM_DESTROY, 0, 0); 
						break;}
			language=3;
			analysis_of_file (hWnd);
			out_statistic ();
			if (att<0) {SendMessage(hWnd, WM_DESTROY, 0, 0); break;}
			if (name_change==1){
							tempr[att] = new char[statistic_file_name.size()];
							strcpy( tempr[att], statistic_file_name.c_str() );}
			if (!doc.Open(tempr[att])) return 0;
			page=2;
			InvalidateRect (hWnd, NULL, 1);
			SendMessage (hWnd,WM_PAINT, wParam, lParam);
			name_change=0;
			break;
	//------------------------------------------------------------	
		case IDM_BKGR_COLOR:
 			if (ChooseColor(&cc))
				SetClassLong(hWnd, GCL_HBRBACKGROUND,
				(LONG)CreateSolidBrush(cc.rgbResult));
			break;
	//------------------------------------------------------------	
		case IDM_TEXT_COLOR:
 			if (ChooseColor(&cc))  textColor = cc.rgbResult;
			break;
    //------------------------------------------------------------
		case IDM_CHOOSE_FONT:
			if(ChooseFont(&chf))  hFont = CreateFontIndirect(chf.lpLogFont);	
			break;
    //------------------------------------------------------------
		

		default : 
			InvalidateRect(hWnd, NULL, TRUE);		
		break;
		}
		}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
	case WM_PAINT:
		hDC = BeginPaint (hWnd, &ps);
		wd = ws = menu.GetWidth ();
		hd = hs = menu.GetHeight ();
					
		switch (page)
		{
			case 1:
				menu.Draw (hDC, 0, 0, wd, hd, 0, 0, ws, hs, SRCCOPY);
				statistic_file_name="out.txt";
				break;
		
			case 2:
				menu.Draw (hDC, 0, 0, wd, hd, 0, 0, ws, hs, SRCCOPY);
				SetBkMode(hDC, TRANSPARENT);
				SetTextColor(hDC, textColor);
				if (hFont) DeleteObject(SelectObject(hDC, hFont));
				GetClientRect(hWnd, &rect);
				doc.PutText(hWnd, hDC);
				statistic_file_name="out.txt";
				break;

			case 3:
				help.Draw (hDC, 0, 0, wd, hd, 0, 0, ws, hs, SRCCOPY);
				statistic_file_name="out.txt";
				break;

				
			default: 
				menu.Draw (hDC, 0, 0, wd, hd, 0, 0, ws, hs, SRCCOPY);
				SetBkMode(hDC, TRANSPARENT);
				GetClientRect(hWnd, &rect);
				break;

		}

		EndPaint (hWnd, &ps);
		break;

//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

	case WM_DESTROY:
		dictionary.clear();
		PostQuitMessage (0);
		break;

	default:
		return DefWindowProc (hWnd, uMsg, wParam, lParam);
	}

return 0;
}