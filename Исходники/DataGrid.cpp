LRESULT CDataGrid::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	CRect client;
	GetClientRect(&client);

	if (m_rs)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);

		dc.SetBkMode(TRANSPARENT);

		HFONT hOldFont = (HFONT)dc.SelectFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

		long nfields = m_rs->Fields->Count;
		int rightX;

		// Draw column headers
		{
			dc.FillSolidRect(0, 0, client.right, 18, GetSysColor(COLOR_BTNFACE));

			int x = 18;

			{
				CRect rect(0, 0, x, 18);
				dc.Draw3dRect(&rect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
			}

			for (int nfld = 0; nfld < nfields; nfld++)
			{
				ADODB::FieldPtr fld = m_rs->Fields->GetItem(&_variant_t((long)nfld));

				_bstr_t fldName = fld->Name;

				CRect rect(x, 0, x+160, 18);
				dc.Draw3dRect(&rect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

				CRect trect = rect;
				trect.InflateRect(-1, -1);

				dc.DrawText(fldName, fldName.length(), &trect, DT_SINGLELINE | DT_VCENTER);

				x += 160;
			}

			rightX = x;
		}

		// Draw rows
		if (dc.IntersectClipRect(0, 18, client.right-16, client.bottom) > NULLREGION)
		{
			dc.SetViewportOrg(0, -scrollposY);

			int y = 18;
			int itemHeight = 60;

			m_rs->MoveFirst();

			while (!(m_rs->EndOfFile))
			{
				int x = 18;

				// Draw left margin of row
				{
					CRect rect(0, y, x, y+itemHeight);
					dc.FillSolidRect(&rect, GetSysColor(COLOR_BTNFACE));
					dc.Draw3dRect(&rect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
				}

				for (int nfld = 0; nfld < nfields; nfld++)
				{
					ADODB::FieldPtr fld = m_rs->Fields->GetItem(&_variant_t((long)nfld));

					ADODB::DataTypeEnum type = fld->Type;

					CRect rect(x, y, x+160, y+itemHeight);

					CRect trect = rect;
					trect.InflateRect(-1, -1);

					_bstr_t vStr;

					if (type == ADODB::adLongVarBinary)
					{
						long size = fld->ActualSize;

						_variant_t varr = fld->GetChunk(size);

						WCHAR* p;
						if (SUCCEEDED(SafeArrayAccessData(varr.parray, (void**)&p)))
						{
							vStr = _bstr_t(p);

							SafeArrayUnaccessData(varr.parray);
						}
					}
					else
					{
						_variant_t v;

						try
						{
							v = fld->Value;


							if (v.vt == VT_NULL)
							{
								vStr = L"<NULL>";
							}
							else
							{
								vStr = v;
							}
						}
						catch (_com_error &e)
						{
							ATLASSERT(0);
						}
					}

					ATLTRACE("%S\n", (BSTR)vStr);
					dc.DrawText(vStr, vStr.length(), &trect, DT_WORDBREAK);

					x += 160;

				// Draw vertical separator between columns
					dc.FillSolidRect(x, y, 1, itemHeight, GetSysColor(COLOR_3DLIGHT));
				}

				m_rs->MoveNext();

				y += itemHeight;

			// Draw horizontal separator between rows
				dc.FillSolidRect(18, y, rightX-18, 1, GetSysColor(COLOR_3DLIGHT));
			}
		}

		dc.SelectFont(hOldFont);
	}

	return 0;
}