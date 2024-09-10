void InitGroupMenus(void)
{
	HICON hicon = LoadIconFromExternalFile("clisticons.dll",2,TRUE,TRUE,"NewGroup","Contact list","New Group",-IDI_NEWGROUP2,0);
	NewGroupIconidx = ImageList_AddIcon(hCListImages,hicon );

	CreateServiceFunction("CLISTMENUSGroup/ExecService",GroupMenuExecService);
	CreateServiceFunction("CLISTMENUSGroup/FreeOwnerDataGroupMenu",FreeOwnerDataGroupMenu);
	CreateServiceFunction("CLISTMENUSGroup/GroupMenuonAddService",GroupMenuonAddService);
	CreateServiceFunction("CLISTMENUSGroup/HideGroupsHelper",HideGroupsHelper);
	CreateServiceFunction("CLISTMENUSGroup/UseGroupsHelper",UseGroupsHelper);
	CreateServiceFunction("CLISTMENUSGroup/HideOfflineRootHelper",HideOfflineRootHelper);

	CreateServiceFunction("CList/AddGroupMenuItem",AddGroupMenuItem);
	CreateServiceFunction(MS_CLIST_REMOVEGROUPMENUITEM,RemoveGroupMenuItem);
	CreateServiceFunction(MS_CLIST_MENUBUILDGROUP,BuildGroupMenu);
	hPreBuildGroupMenuEvent = CreateHookableEvent(ME_CLIST_PREBUILDGROUPMENU);
	HookEvent(ME_CLIST_PREBUILDGROUPMENU,OnBuildGroupMenu);

	InitSubGroupMenus();

	// Group menu
	hGroupMenuObject = MO_CreateMenuObject("GroupMenu", LPGEN("Group menu"), 0, "CLISTMENUSGroup/ExecService");
	MO_SetMenuObjectParam(hGroupMenuObject, OPT_USERDEFINEDITEMS, TRUE);
	MO_SetMenuObjectParam(hGroupMenuObject, OPT_MENUOBJECT_SET_FREE_SERVICE, "CLISTMENUSGroup/FreeOwnerDataGroupMenu");
	MO_SetMenuObjectParam(hGroupMenuObject, OPT_MENUOBJECT_SET_ONADD_SERVICE, "CLISTMENUSGroup/GroupMenuonAddService");
	{
		//add  exit command to menu
		GroupMenuParam gmp;

		CLISTMENUITEM mi = { sizeof(mi) };
		mi.position = 1900000;
		mi.pszService = "CloseAction";
		mi.pszName = LPGEN("E&xit");
		AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 500;
		mi.pszService = MS_CLIST_SHOWHIDE;
		mi.pszName = LPGEN("&Hide/Show");
		hHideShowMainMenuItem = (HANDLE)AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 200000;
		mi.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FINDUSER));
		mi.pszService = "FindAdd/FindAddCommand";
		mi.pszName = LPGEN("&Find/Add Contacts...");
		AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 300000;
		mi.pszService = "";
		mi.pszName = LPGEN("&Main menu");
		hGroupMainMenuItemProxy = (HANDLE)AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 300100;
		mi.pszService = "";
		mi.pszName = LPGEN("&Status");
		hGroupStatusMenuItemProxy = (HANDLE)AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 400000;
		mi.hIcon = LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_OPTIONS));
		mi.pszService = "Options/OptionsCommand";
		mi.pszName = LPGEN("&Options...");

		AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 500000;
		mi.hIcon = LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_CLIENTMIRANDA));
		mi.pszService = "Help/AboutCommand";
		mi.pszName = LPGEN("&About");

		//AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 100000;
		mi.hIcon = ImageList_GetIcon(hCListImages,NewGroupIconidx,0);
		mi.pszService = MS_CLIST_GROUPCREATE;
		mi.pszName = LPGEN("&New Group");
		hNewGroupMenuItem = (HGENMENU)AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 100001;
		mi.hIcon = NULL;
		mi.pszService = MS_CLIST_SETHIDEOFFLINE;
		mi.pszName = LPGEN("&Hide Offline Users");
		gmp.lParam = 0;gmp.wParam = -1;
		hHideOfflineUsersMenuItem = (HGENMENU)AddGroupMenuItem((WPARAM)&gmp,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 100002;
		mi.hIcon = NULL;
		mi.pszService = "CLISTMENUSGroup/HideOfflineRootHelper";
		mi.pszName = LPGEN("Hide &Offline Users out here");
		hHideOfflineUsersOutHereMenuItem = (HGENMENU)AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 100003;
		mi.hIcon = NULL;
		mi.pszService = "CLISTMENUSGroup/HideGroupsHelper";
		mi.pszName = LPGEN("Hide &Empty Groups");
		hHideEmptyGroupsMenuItem = (HGENMENU)AddGroupMenuItem(0,(LPARAM)&mi);

		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.position = 100004;
		mi.hIcon = NULL;
		mi.pszService = "CLISTMENUSGroup/UseGroupsHelper";
		mi.pszName = LPGEN("Disable &Groups");
		hDisableGroupsMenuItem = (HGENMENU)AddGroupMenuItem(0,(LPARAM)&mi);

		HookEvent(ME_SKIN2_ICONSCHANGED,OnIconLibIconChanged);
	}
}