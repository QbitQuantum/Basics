BOOL CPPageExternalFilters::OnInitDialog()
{
	__super::OnInitDialog();

	DragAcceptFiles(TRUE);

	AppSettings& s = AfxGetAppSettings();

	m_pFilters.RemoveAll();

	POSITION pos = s.m_filters.GetHeadPosition();
	while (pos) {
		CAutoPtr<FilterOverride> f(DNew FilterOverride(s.m_filters.GetNext(pos)));

		CString name(_T("<unknown>"));

		if (f->type == FilterOverride::REGISTERED) {
			name = CFGFilterRegistry(f->dispname).GetName();
			if (name.IsEmpty()) {
				name = f->name + _T(" <not registered>");
			}
		} else if (f->type == FilterOverride::EXTERNAL) {
			name = f->name;
			if (f->fTemporary) {
				name += _T(" <temporary>");
			}
			if (!CPath(MakeFullPath(f->path)).FileExists()) {
				name += _T(" <not found!>");
			}
		}

		int i = m_filters.AddString(name);
		m_filters.SetCheck(i, f->fDisabled ? 0 : 1);
		m_filters.SetItemDataPtr(i, m_pFilters.AddTail(f));
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}