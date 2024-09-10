bool GSCaptureDlg::OnCommand(HWND hWnd, UINT id, UINT code)
{
	if(id == IDC_BROWSE && code == BN_CLICKED)
	{
		char buff[MAX_PATH] = {0};

		OPENFILENAME ofn;

		memset(&ofn, 0, sizeof(ofn));

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = m_hWnd;
		ofn.lpstrFile = buff;
		ofn.nMaxFile = countof(buff);
		ofn.lpstrFilter = "Avi files (*.avi)\0*.avi\0";
		ofn.Flags = OFN_EXPLORER | OFN_ENABLESIZING | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;

		strcpy(ofn.lpstrFile, m_filename.c_str());

		if(GetSaveFileName(&ofn))
		{
			m_filename = ofn.lpstrFile;

			SetText(IDC_FILENAME, m_filename.c_str());
		}

		return true;
	}
	else if(id == IDC_CONFIGURE && code == BN_CLICKED)
	{
		Codec c;

		if(GetSelCodec(c) == 1)
		{
			if(CComQIPtr<ISpecifyPropertyPages> pSPP = c.filter)
			{
				CAUUID caGUID;

				memset(&caGUID, 0, sizeof(caGUID));

				if(SUCCEEDED(pSPP->GetPages(&caGUID)))
				{
					IUnknown* lpUnk = NULL;
					pSPP.QueryInterface(&lpUnk);
					OleCreatePropertyFrame(m_hWnd, 0, 0, c.FriendlyName.c_str(), 1, (IUnknown**)&lpUnk, caGUID.cElems, caGUID.pElems, 0, 0, NULL);
					lpUnk->Release();

					if(caGUID.pElems) CoTaskMemFree(caGUID.pElems);
				}
			}
			else if(CComQIPtr<IAMVfwCompressDialogs> pAMVfWCD = c.filter)
			{
				if(pAMVfWCD->ShowDialog(VfwCompressDialog_QueryConfig, NULL) == S_OK)
				{
					pAMVfWCD->ShowDialog(VfwCompressDialog_Config, m_hWnd);
				}
			}
		}

		return true;
	}
	else if(id == IDOK)
	{
		m_width = GetTextAsInt(IDC_WIDTH);
		m_height = GetTextAsInt(IDC_HEIGHT);
		m_filename = GetText(IDC_FILENAME);

		Codec c;

		int ris = GetSelCodec(c);
		if(ris == 0)
		{
			return false;
		}

		m_enc = c.filter;

		theApp.SetConfig("CaptureWidth", m_width);
		theApp.SetConfig("CaptureHeight", m_height);
		theApp.SetConfig("CaptureFileName", m_filename.c_str());

		if (ris != 2)
		{
			wstring s = wstring(c.DisplayName.m_str);
			theApp.SetConfig("CaptureVideoCodecDisplayName", string(s.begin(), s.end()).c_str());
		}
		else
		{
			theApp.SetConfig("CaptureVideoCodecDisplayName", "");
		}
	}

	return __super::OnCommand(hWnd, id, code);
}