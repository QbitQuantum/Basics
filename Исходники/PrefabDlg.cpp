BOOL CPrefabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMenu menu;
	menu.LoadMenu(IDR_MENU2);
	SetMenu(&menu);
	menu.Detach();

	if (g_editorMode == eMODE_PREFAB)
	{
		GetMenu()->EnableMenuItem(ID_PACKAGE_NEW, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_PACKAGE_RENAMESELECTED, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_PACKAGE_DELETESELECTED, MF_ENABLED);

		GetMenu()->EnableMenuItem(ID_PREFAB_NEW, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_PREFAB_OPENSELECTED, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_PREFAB_RENAMESELECTED, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_PREFAB_DELETESELECTED, MF_ENABLED);
		m_btnInsertPrefab.SetWindowTextA("Open Prefab");
	}
	else
	{
		GetMenu()->EnableMenuItem(ID_PACKAGE_NEW, MF_DISABLED | MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_PACKAGE_RENAMESELECTED, MF_DISABLED | MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_PACKAGE_DELETESELECTED, MF_DISABLED | MF_GRAYED);

		GetMenu()->EnableMenuItem(ID_PREFAB_NEW, MF_DISABLED | MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_PREFAB_OPENSELECTED, MF_DISABLED | MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_PREFAB_RENAMESELECTED, MF_DISABLED | MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_PREFAB_DELETESELECTED, MF_DISABLED | MF_GRAYED);

		m_btnInsertPrefab.SetWindowTextA("Insert Prefab");

	}
	m_slideLod.SetRange(0, 2);
	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;
	m_packageListImage.Create(36, 36, ILC_COLOR24, 1, 1);

	cBmp.LoadBitmap(IDB_BITMAP_DEFAULT_PACKAGE);
	m_packageListImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	RECT tempRect;
	m_listPrefabPackages.GetClientRect(&tempRect);
	m_listPrefabPackages.SetImageList(&m_packageListImage, LVSIL_SMALL);
	m_listPrefabPackages.InsertColumn(0, "Packages", LVCFMT_CENTER | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 80 / 100);
	m_listPrefabPackages.ShowWindow(SW_SHOW);
	m_listPrefabPackages.UpdateWindow();

	m_prefabListImage.Create(80, 80, ILC_COLOR24, 1, 1);

	cBmp.LoadBitmap(IDB_BITMAP_DEFAULT_VPF);
	m_prefabListImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	m_listPrefabs.SetImageList(&m_prefabListImage, LVSIL_NORMAL);

	m_listPrefabs.GetClientRect(&tempRect);
	m_listPrefabs.InsertColumn(0, "Prefabs", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 80 / 100);
	m_listPrefabs.ShowWindow(SW_SHOW);
	m_listPrefabs.UpdateWindow();

	//insert items
	for (CUInt i = 0; i < g_prefabPackagesAndNames.size(); i++)
	{
		CChar str[MAX_NAME_SIZE];
		Cpy(str, g_prefabPackagesAndNames[i].front().c_str());
		if (!Cmp(str, "Vanda_Basics"))
			InsertItemToPackageList(str);
	}
	RECT rect;
	m_listPrefabProperties.GetClientRect(&rect);
	m_listPrefabProperties.InsertColumn(0, "Parameters", LVCFMT_LEFT, rect.right - rect.left, 1);
	m_listPrefabProperties.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);
	InserItemToPropertiesList("Vertices");
	InserItemToPropertiesList("Textures");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}