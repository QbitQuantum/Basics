void CPPageInternalFiltersListBox::OnRButtonDown(UINT nFlags, CPoint point)
{
	CCheckListBox::OnRButtonDown(nFlags, point);

	CMenu m;
	m.CreatePopupMenu();

	enum {
		ENABLE_ALL = 1,
		DISABLE_ALL,
		ENABLE_FFMPEG,
		DISABLE_FFMPEG,
		ENABLE_DXVA,
		DISABLE_DXVA,
	};

	int totalFilters = 0, totalChecked = 0;
	for (int i = 0; i < FILTER_TYPE_NB; i++) {
		totalFilters += m_nbFiltersPerType[i];
		totalChecked += m_nbChecked[i];
	}

	UINT state = (totalChecked != totalFilters) ? MF_ENABLED : MF_GRAYED;
	m.AppendMenu(MF_STRING | state, ENABLE_ALL, ResStr(IDS_ENABLE_ALL_FILTERS));
	state = (totalChecked != 0) ? MF_ENABLED : MF_GRAYED;
	m.AppendMenu(MF_STRING | state, DISABLE_ALL, ResStr(IDS_DISABLE_ALL_FILTERS));

	if (m_n == 1) {
		m.AppendMenu(MF_SEPARATOR);
		state = (m_nbChecked[FFMPEG_DECODER] != m_nbFiltersPerType[FFMPEG_DECODER]) ? MF_ENABLED : MF_GRAYED;
		m.AppendMenu(MF_STRING | state, ENABLE_FFMPEG, ResStr(IDS_ENABLE_FFMPEG_FILTERS));
		state = (m_nbChecked[FFMPEG_DECODER] != 0) ? MF_ENABLED : MF_GRAYED;
		m.AppendMenu(MF_STRING | state, DISABLE_FFMPEG, ResStr(IDS_DISABLE_FFMPEG_FILTERS));

		m.AppendMenu(MF_SEPARATOR);
		state = (m_nbChecked[DXVA_DECODER] != m_nbFiltersPerType[DXVA_DECODER]) ? MF_ENABLED : MF_GRAYED;
		m.AppendMenu(MF_STRING | state, ENABLE_DXVA, ResStr(IDS_ENABLE_DXVA_FILTERS));
		state = (m_nbChecked[DXVA_DECODER] != 0) ? MF_ENABLED : MF_GRAYED;
		m.AppendMenu(MF_STRING | state, DISABLE_DXVA, ResStr(IDS_DISABLE_DXVA_FILTERS));
	}

	CPoint p = point;
	::MapWindowPoints(m_hWnd, HWND_DESKTOP, &p, 1);

	UINT id = m.TrackPopupMenu(TPM_LEFTBUTTON|TPM_RETURNCMD, p.x, p.y, this);

	if (id == 0) {
		return;
	}

	int index = 0;
	for (int i = 0; i < countof(s_filters); i++) {
		switch (s_filters[i].type) {
			case SOURCE_FILTER:
				if (m_n == 1) {
					continue;
				}
				break;
			case DECODER:
			case DXVA_DECODER:
			case FFMPEG_DECODER:
				if (m_n == 0) {
					continue;
				}
				break;
			default:
				continue;
		}

		switch (id) {
			case ENABLE_ALL:
				SetCheck(index, TRUE);
				break;
			case DISABLE_ALL:
				SetCheck(index, FALSE);
				break;
			case ENABLE_FFMPEG:
				if (s_filters[i].type == FFMPEG_DECODER) {
					SetCheck(index, TRUE);
				}
				break;
			case DISABLE_FFMPEG:
				if (s_filters[i].type == FFMPEG_DECODER) {
					SetCheck(index, FALSE);
				}
				break;
			case ENABLE_DXVA:
				if (s_filters[i].type == DXVA_DECODER) {
					SetCheck(index, TRUE);
				}
				break;
			case DISABLE_DXVA:
				if (s_filters[i].type == DXVA_DECODER) {
					SetCheck(index, FALSE);
				}
				break;
		}
		index++;
	}

	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CLBN_CHKCHANGE), (LPARAM)m_hWnd);
}