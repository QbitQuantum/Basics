/**
 * name:	Icon
 * class:	CPsTreeItem
 * desc:	load the icon, add to icolib if required and add to imagelist of treeview
 * params:	hIml			- treeview's imagelist to add the icon to
 *			odp				- pointer to OPTIONSDIALOGPAGE providing the information about the icon to load
 *			hDefaultIcon	- default icon to use
 * return: nothing
 **/
int CPsTreeItem::Icon(HIMAGELIST hIml, OPTIONSDIALOGPAGE *odp, BYTE bInitIconsOnly)
{
	// check parameter
	if (!_pszName || !odp)
		return 1;

	// load the icon if no icolib is installed or creating the required settingname failed
	LPCSTR pszIconName = IconKey();

	// use icolib to handle icons
	HICON hIcon = IcoLib_GetIcon(pszIconName);
	if (!hIcon) {
		bool bNeedFree = false;

		SKINICONDESC sid = { 0 };
		sid.flags = SIDF_ALL_TCHAR;
		sid.pszName = (LPSTR)pszIconName;
		sid.description.t = _ptszLabel;
		sid.section.t = LPGENT(SECT_TREE);

		// the item to insert brings along an icon?
		if (odp->flags & ODPF_ICON) {
			// is it uinfoex item?
			if (odp->hInstance == ghInst) {

				// the pszGroup holds the iconfile for items added by uinfoex
				sid.defaultFile.t = odp->ptszGroup;

				// icon library exists?
				if (sid.defaultFile.t)
					sid.iDefaultIndex = (INT_PTR)odp->hIcon;
				// no valid icon library
				else {
					bNeedFree = true;
					sid.hDefaultIcon = ImageList_GetIcon(hIml, 0, ILD_NORMAL);
					sid.iDefaultIndex = -1;
				}
			}
			// default icon is delivered by the page to add
			else {
				if (odp->hIcon)
					sid.hDefaultIcon = odp->hIcon;
				else
					sid.hDefaultIcon = ImageList_GetIcon(hIml, 0, ILD_NORMAL), bNeedFree = true;
				sid.iDefaultIndex = -1;
			}
		}
		// no icon to add, use default
		else {
			sid.iDefaultIndex = -1;
			sid.hDefaultIcon = ProtoIcon();
			if (!sid.hDefaultIcon)
				sid.hDefaultIcon = ImageList_GetIcon(hIml, 0, ILD_NORMAL), bNeedFree = true;
		}
		// add file to icolib
		IcoLib_AddIcon(&sid);

		if (!bInitIconsOnly)
			hIcon = IcoLib_GetIcon(pszIconName);
		if (bNeedFree)
			DestroyIcon(sid.hDefaultIcon);
	}
	
	if (!bInitIconsOnly && hIml) {
		// set custom icon to image list
		if (hIcon) return ((_iImage = ImageList_AddIcon(hIml, hIcon)) == -1);
		_iImage = 0;
	}
	else
		_iImage = -1;
	return 0;
}