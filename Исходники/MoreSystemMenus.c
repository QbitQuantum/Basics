static void DeleteSubMenus(SubSysMenuHandle subSysMenus)
	// Remove any sub-menus that we added to the menu bar.
	// Basically this just walks subSysMenus (backwards, which
	// isn't strictly necessary, but reassures me that the menu
	// bar is somewhat consistent at each step), deleting each
	// menu from the menu bar and reseting its parent to reference
	// menu ID 0.
{
	ItemCount entryCount;
	ItemCount entryIndex;
	SubSysMenuEntry thisEntry;
	
	// Have to handle both NULL and non-NULL case.
	// This expression always evaluates to true,
	// but it captures the semantics of what this
	// routine must do.
	
	assert(subSysMenus != NULL || subSysMenus == NULL);
	
	entryCount = CountSubSysMenus(subSysMenus);
	for (entryIndex = 0; entryIndex < entryCount; entryIndex++) {
		thisEntry = (*subSysMenus)[entryCount - entryIndex - 1];
		DeleteMenu( (**(thisEntry.childMenu)).menuID );
		SetItemMark( thisEntry.parentMenu, thisEntry.itemInParent, 0);

		// Recalculate the parent menu size, for consistency with
		// the similar code in InsertSystemSubMenu.
		
		CalcMenuSize(thisEntry.parentMenu);
	}
}