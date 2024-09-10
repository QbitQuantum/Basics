long FAR PASCAL _export WndProc (HWND hWnd, UINT message, UINT wParam, LONG lParam)
{

	FP x1,x2,y1,y2;
	PCURVE pCurve;
	ULong Comb;

	Comb = 0;

	switch (message)
	{

	case WM_CREATE:
		return 0;

	case WM_ACTIVATE:
		return 0;

	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;

//      case WM_COMMAND:
//	     	switch (wParam)
//			{
//         }
//         break;

	case WM_KEYDOWN:

		if (_Editor.SetFuncCode (wParam))
			_Editor.PrintFunctionName ();

		switch (wParam)
		{

		case VK_ESCAPE:
			DestroyWindow (hWnd);
			break;

		case 'S':
			WriteCurves (_CurveRsc.pCurves, "model\\cdat.cpp");
			break;

		case 'N':

			pCurve = _Editor.GetActiveCurve ();

			if (pCurve != NULL)
			{
				pCurve = NextCurve (_CurveRsc.pCurves, (Bool)FALSE);

				_Editor.SetCurrCurvePtr (pCurve);

				_Editor.ClearWindow ();

				pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
				_Editor.pCurrView->InitView(x1,x2,y1,y2);
			}


			break;

		case 'B':

			pCurve = _Editor.GetActiveCurve ();

			if (pCurve != NULL)
			{

				pCurve = NextCurve (_CurveRsc.pCurves, (Bool)TRUE);

				_Editor.ClearWindow ();

				_Editor.SetCurrCurvePtr (pCurve);

				pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
				_Editor.pCurrView->InitView(x1,x2,y1,y2);
			}


			break;

		case 'K':

			for (;;)
			{

				_Editor.ActiveCurve++;

				if (_Editor.ActiveCurve == 4)
					_Editor.ActiveCurve = 1;

				if (_Editor.GetActiveCurve () != NULL)
					break;
			}

			_Editor.ClearWindow ();

			break;

		case 'O':


			if (_Editor.ActiveCurve == 2)
				_Editor.pCurrCurve1 = NULL;

			if (_Editor.ActiveCurve == 3)
				_Editor.pCurrCurve2 = NULL;

			_Editor.ActiveCurve = 1;

			_Editor.ClearWindow ();

			pCurve = _Editor.GetActiveCurve ();
			pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
			_Editor.pCurrView->InitView(x1,x2,y1,y2);

			break;

		case 'H':

			if (_Editor.pCurrCurve1 == NULL)
			{
				_Editor.pCurrCurve1 = NextCurve (_CurveRsc.pCurves, (Bool)FALSE);
				_Editor.ActiveCurve = 2;
			}

			else if (_Editor.pCurrCurve2 == NULL)
			{
				_Editor.pCurrCurve2 = NextCurve (_CurveRsc.pCurves, (Bool)FALSE);
				_Editor.ActiveCurve = 3;
			}
			else
				break;

			_Editor.ClearWindow ();

			pCurve = _Editor.GetActiveCurve ();
			pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
			_Editor.pCurrView->InitView(x1,x2,y1,y2);

			break;

		case 'R':

			_Editor.ClearWindow ();

			pCurve = _Editor.GetActiveCurve ();
			if (pCurve != NULL)
			{
				pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
				_Editor.pCurrView->InitView(x1,x2,y1,y2);
			}

			break;

		case 'C':

			// Duplicate Cl Curve
			_Editor.GetActiveCurve ()-> DuplicateCl (0);

			break;

		case 'T':
			_Editor.ClearWindow ();
			break;

		case VK_NUMPAD4:
			Comb |= 0x11;	// 1st +
			break;

		case VK_NUMPAD5:
			Comb |= 0x12;	// 1st -
			break;

		case VK_NUMPAD1:
			Comb |= 0x24;	// 2nd +
			break;

		case VK_NUMPAD2:
			Comb |= 0x28;	// 2nd -
			break;

		case VK_NUMPAD7:
			Comb |= 0x35;	// 1st & 2nd +
			break;

		case VK_NUMPAD8:
			Comb |= 0x3a;	// 1st & 2nd -
			break;

		case VK_NUMPAD9:
			Comb |= 0x39;	// 1st + 2nd -
			break;

		case VK_NUMPAD6:
			Comb |= 0x36;	// 1st - 2nd +
			break;

  		}

		if (Comb)
		{
			// draw combination curve
			if (_Editor.pCurrView != NULL)
				_Editor.pCurrView->CombinationCurve (Comb);
		}

//		if (Comb) 
//			_Editor.ClearWindow ();

  		return 0;

	case WM_LBUTTONDOWN:
		_Editor.Function () (WM_LBUTTONDOWN);
		return 0;

	case WM_RBUTTONDOWN:
		_Editor.Function () (WM_RBUTTONDOWN);
         return 0;

	case WM_LBUTTONUP:
		_Editor.Function () (WM_LBUTTONUP);
		return 0;

	case WM_RBUTTONUP:
		_Editor.Function () (WM_RBUTTONUP);
		return 0;

	case WM_MOUSEMOVE:
		_Editor.MousePos.x = LOWORD(lParam);
		_Editor.MousePos.y = HIWORD(lParam);

		PrintMousePos (_Editor.pCurrView);

		_Editor.Function () (WM_MOUSEMOVE);
        return 0;

	case WM_PAINT:

		_Editor.PrintFunctionName ();

		PrintMousePos (_Editor.pCurrView);

		// curve names
		HDC hdc = GetDC (_Editor.pCurrView->hWnd);

		if (_Editor.pCurrCurve != NULL)
		{
			TextOut (hdc, 5, 5, _Editor.pCurrCurve->AircraftName, strlen(_Editor.pCurrCurve->AircraftName));
			TextOut (hdc, 5, 20, _Editor.pCurrCurve->CurveName, strlen(_Editor.pCurrCurve->CurveName));

			if (_Editor.ActiveCurve == 1)
				TextOut (hdc, 5, 35, "Active", 6);
			else
				TextOut (hdc, 5, 35, "Inert", 5);
		}
		else
			TextOut (hdc, 5, 5, "Empty", 5);

		if (_Editor.pCurrCurve1 != NULL)
		{
			TextOut (hdc, 5, 105, _Editor.pCurrCurve1->AircraftName, strlen(_Editor.pCurrCurve1->AircraftName));
			TextOut (hdc, 5, 120, _Editor.pCurrCurve1->CurveName, strlen(_Editor.pCurrCurve1->CurveName));

			if (_Editor.ActiveCurve == 2)
				TextOut (hdc, 5, 135, "Active", 6);
			else
				TextOut (hdc, 5, 135, "Inert", 5);
		}
		else
			TextOut (hdc, 5, 105, "Empty", 5);


		if (_Editor.pCurrCurve2 != NULL)
		{
			TextOut (hdc, 5, 205, _Editor.pCurrCurve2->AircraftName, strlen(_Editor.pCurrCurve2->AircraftName));
			TextOut (hdc, 5, 220, _Editor.pCurrCurve2->CurveName, strlen(_Editor.pCurrCurve2->CurveName));

			if (_Editor.ActiveCurve == 3)
				TextOut (hdc, 5, 235, "Active", 6);
			else
				TextOut (hdc, 5, 235, "Inert", 5);
		}
		else
			TextOut (hdc, 5, 205, "Empty", 5);

		ReleaseDC (_Editor.pCurrView->hWnd, &hdc);

		_Editor.GetActiveCurve()->DrawGrads (_Editor.pCurrView);

		if (_Editor.pCurrCurve != NULL)
			_Editor.pCurrCurve->DrawCurve (_Editor.pCurrView);

		if (_Editor.pCurrCurve1 != NULL)
			_Editor.pCurrCurve1->DrawCurve (_Editor.pCurrView);

		if (_Editor.pCurrCurve2 != NULL)
			_Editor.pCurrCurve2->DrawCurve (_Editor.pCurrView);

		// Validate the entire client area to stop looping WM_PAINT
		// BeginPaint normally does this
		RECT rect;
		GetClientRect (_Editor.hWnd, &rect);
		HRGN hRgn = CreateRectRgn (rect.left, rect.top, rect.right, rect.bottom);
		ValidateRgn (_Editor.hWnd, hRgn);

		_Editor.pCurrView->cRect = rect;

		return 0;
	}

	return DefWindowProc (hWnd, message, wParam, lParam) ;
}