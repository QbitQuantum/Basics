void CBadTrustDialog::OnInitDialog()
    {
    //
    // Get the background brush for our edit controls
    //
    m_hbrBackground = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

    // Load the icon
    LPSTR idi;
    switch (m_rrn.hrValid)
        {
    case HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND):
    case TRUST_E_NOSIGNATURE:
        idi = IDI_EXCLAMATION;
        break;
    default:
        idi = IDI_HAND;
        break;
        }
    HICON hicon = LoadIcon(NULL, idi);
    ::SendDlgItemMessage(m_hWnd, IDC_BADTRUSTICON, STM_SETICON, (WPARAM)hicon, (LPARAM)0);

    // Set the window title
		{
		TCHAR sz[128];
        WideCharToMultiByte(CP_ACP, 0, m_rrn.wszDialogTitle, -1, (LPSTR)sz, 128, NULL, NULL);
		::SetWindowText(GetWindow(), sz);
		}

    // Set the banter text
    int cchBanter2;
        {
        const int cchMax = INTERNET_MAX_URL_LENGTH+64;
        TCHAR sz[cchMax];

        // Set the top level banter
        ::LoadString(hinst, IDS_BADTRUSTBANTER1, &sz[0], cchMax);
        ::SetWindowText(WindowOf(IDC_BADTRUSTBANTER1), &sz[0]);

        // Set the program name
            {
            //
            // The 'program' name we see can in fact often be a full URL. URLs
            // can be very long, up to 1024 or so.
            //
            if (m_rrn.wszProgramName)
                {
                WideCharToMultiByte(CP_ACP, 0, m_rrn.wszProgramName, -1, &sz[0], cchMax, NULL, NULL);
                }
            else
                ::LoadString(hinst, IDS_UNKNOWNPROGRAM, &sz[0], cchMax);

            TCHAR szF[cchMax];
            ::FormatMessage(hinst, &szF[0], cchMax, IDS_BADTRUSTBANTER2, &sz[0]);

            ::SetWindowText(WindowOf(IDC_BADTRUSTBANTER2), &szF[0]);
            cchBanter2 = lstrlen(&szF[0]);

            //
            // This control is read-only. Note that the text on the control
            // can be copied using the context menu in the control.
            //
            SendMessage(WindowOf(IDC_BADTRUSTBANTER2), EM_SETREADONLY, (WPARAM)TRUE, 0);
            }

        // Set the trailing banter
        UINT ids;
        switch (m_rrn.hrValid)
            {
        case HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND):
        case TRUST_E_NOSIGNATURE:
            ids = IDS_BADTRUSTBANTER31;
            break;
        case CERT_E_EXPIRED:
        case CERT_E_VALIDIYPERIODNESTING:
            ids = IDS_BADTRUSTBANTER32;
            break;
        case NTE_BAD_SIGNATURE:
            ids = IDS_BADTRUSTBANTER33;
            break;
        default:
            ids = IDS_BADTRUSTBANTER34;
            break;
            }
        ::LoadString(hinst, ids, &sz[0], cchMax);
        ::SetWindowText(WindowOf(IDC_BADTRUSTBANTER3), &sz[0]);

        }

    // Position the controls so that all are visible
        {
        UINT spacing = GetSystemMetrics(SM_CYFIXEDFRAME) * 2;
        RECT rc1, rc2, rc3;
        int h;
        POINT pt;

        //
        // Where on the screen is the client area of the dialog?
        //
        pt.x = 0;
        pt.y = 0;
        ClientToScreen(GetWindow(), &pt);

        //
        // Find first text box location
        //
        GetWindowRect(WindowOf(IDC_BADTRUSTBANTER1), &rc1);

        //
        // Adjust second text box size
        //
        SizeControlToFitText(WindowOf(IDC_BADTRUSTBANTER2));
        //
        // Adjust second text box location
        //
        GetWindowRect(WindowOf(IDC_BADTRUSTBANTER2), &rc2);
        rc2.top    = rc1.bottom + spacing;
        ::SetWindowPos(WindowOf(IDC_BADTRUSTBANTER2), NULL,
            rc2.left - pt.x, rc2.top - pt.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
        GetWindowRect(WindowOf(IDC_BADTRUSTBANTER2), &rc2);

        //
        // Adjust third text box location
        //
        GetWindowRect(WindowOf(IDC_BADTRUSTBANTER3), &rc3);
        h = Height(rc3);
        rc3.top         = rc2.bottom + spacing;
        rc3.bottom      = rc3.top + h;
        ::SetWindowPos(WindowOf(IDC_BADTRUSTBANTER3), NULL,
            rc3.left - pt.x, rc3.top - pt.y, Width(rc3), Height(rc3), SWP_NOZORDER);

        //
        // Adjust the button locations
        //
        RECT rcOk, rcCancel, rcDetails;
        GetWindowRect(WindowOf(IDOK),        &rcOk);
        GetWindowRect(WindowOf(IDCANCEL),    &rcCancel);
        GetWindowRect(WindowOf(IDC_DETAILS), &rcDetails);
        rcOk.top        = rc3.bottom + spacing;
        rcCancel.top    = rcOk.top;
        rcDetails.top   = rcOk.top;
        ::SetWindowPos(WindowOf(IDOK),        NULL, rcOk.left-pt.x, rcOk.top-pt.y,0,0, SWP_NOZORDER|SWP_NOSIZE);
        ::SetWindowPos(WindowOf(IDCANCEL),    NULL, rcCancel.left-pt.x, rcCancel.top-pt.y,0,0, SWP_NOZORDER|SWP_NOSIZE);
        ::SetWindowPos(WindowOf(IDC_DETAILS), NULL, rcDetails.left-pt.x, rcDetails.top-pt.y,0,0, SWP_NOZORDER|SWP_NOSIZE);
        GetWindowRect(WindowOf(IDOK),        &rcOk);
        GetWindowRect(WindowOf(IDCANCEL),    &rcCancel);
        GetWindowRect(WindowOf(IDC_DETAILS), &rcDetails);

        //
        // Adjust the overall dialog box size
        //
        RECT rcMe;
	    ::GetWindowRect(GetWindow(), &rcMe);            // screen coords	
        rcMe.bottom = rcOk.bottom + spacing + GetSystemMetrics(SM_CYFIXEDFRAME);
        ::SetWindowPos(GetWindow(), NULL, 0,0,Width(rcMe),Height(rcMe), SWP_NOZORDER | SWP_NOMOVE);

        //
        // Center ourselves in the parent window
        //
        HWND hwndParent = ::GetParent(GetWindow());
	    if (hwndParent == NULL)
		    hwndParent = ::GetDesktopWindow();
	    RECT rcParent;
	    ::GetWindowRect(GetWindow(), &rcMe);            // screen coords	
        ::GetWindowRect(hwndParent,  &rcParent);        // screen coords

        POINT ptParent = Center(rcParent);
        POINT ptMe     = Center(rcMe);
        pt.x = ptParent.x - ptMe.x;
        pt.y = ptParent.y - ptMe.y;

	    ::SetWindowPos
            (
            GetWindow(),
            NULL,
            pt.x,
            pt.y,
            0,
            0,
            SWP_NOZORDER | SWP_NOSIZE
            );
        }

    //
    // Make sure we're on the screen
    //
    EnsureOnScreen(GetWindow());

    //
    // Bring ourselves to the attention of the user
    //
    SetForegroundWindow(GetWindow());
    }