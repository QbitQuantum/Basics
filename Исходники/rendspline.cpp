void RendSplineParamsMapDlgProc::Initialize(HWND hWnd, TimeValue t)
{
	if (hWnd == NULL) return;
	else
	{
		ISpinnerControl *iSpin = GetISpinner(GetDlgItem(hWnd, IDC_ASPECTSPIN));
		iSpin->LinkToEdit(GetDlgItem(hWnd, IDC_ASPECT), EDITTYPE_FLOAT);
		iSpin->SetLimits(0.0f,99999999.0f);
		iSpin->SetAutoScale(TRUE);
		ReleaseISpinner(iSpin);

		if (RendSpline::hLockButton == NULL) {
			HBITMAP hBitmap, hMask;
			RendSpline::hLockButton = ImageList_Create(16, 15, TRUE, 2, 0);
			hBitmap = LoadBitmap(RendSplineDesc.HInstance(), MAKEINTRESOURCE(IDB_LOCK));
			hMask   = LoadBitmap(RendSplineDesc.HInstance(), MAKEINTRESOURCE(IDB_LOCKMASK));
			ImageList_Add(RendSpline::hLockButton,hBitmap,hMask);
			DeleteObject(hBitmap);
			DeleteObject(hMask);
		}

		ICustButton *lockAspect = GetICustButton(GetDlgItem(hWnd,IDC_ASPECTLOCK));
		lockAspect->SetImage(RendSpline::hLockButton,0,0,1,1,16,15);
		lockAspect->SetType(CBT_CHECK);
		ReleaseICustButton(lockAspect);

		CheckRadioButton(hWnd, IDC_VIEWPORT, IDC_RENDERER, IDC_RENDERER);

        BOOL usePhysUVs = mod->GetUsePhysicalScaleUVs();
        CheckDlgButton(hWnd, IDC_REAL_WORLD_MAP_SIZE, usePhysUVs);
	}

}