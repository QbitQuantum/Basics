void DialogAbout::TabSkins::Initialize()
{
	// Add columns to the list view
	HWND item = GetControl(Id_ItemsListView);
	ListView_SetExtendedListViewStyleEx(item, 0, LVS_EX_LABELTIP | LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);

	LVGROUP lvg;
	lvg.cbSize = sizeof(LVGROUP);
	lvg.mask = LVGF_HEADER | LVGF_GROUPID | LVGF_STATE;
	lvg.state = (IsWindowsVistaOrGreater()) ? LVGS_COLLAPSIBLE : LVGS_NORMAL;
	lvg.iGroupId = 0;
	lvg.pszHeader = GetString(ID_STR_MEASURES);
	ListView_InsertGroup(item, 0, &lvg);
	lvg.iGroupId = 1;
	lvg.pszHeader = GetString(ID_STR_VARIABLES);
	ListView_InsertGroup(item, 1, &lvg);

	ListView_EnableGroupView(item, TRUE);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iSubItem = 0;
	lvc.cx = 120;
	lvc.pszText = GetString(ID_STR_NAME);
	ListView_InsertColumn(item, 0, &lvc);
	lvc.iSubItem = 1;
	lvc.cx = 90;
	lvc.pszText = GetString(ID_STR_RANGE);
	ListView_InsertColumn(item, 1, &lvc);
	lvc.iSubItem = 2;

	// Start 3rd column at max width
	RECT rect;
	lvc.cx = GetWindowRect(item, &rect) ? (rect.right - rect.left - 230) : 130;
	lvc.pszText = GetString(ID_STR_VALUE);
	ListView_InsertColumn(item, 2, &lvc);

	UpdateSkinList();

	m_Initialized = true;
}