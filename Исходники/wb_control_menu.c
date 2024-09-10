PWBOBJ wbCreateMenu(PWBOBJ pwboParent, PWBITEM pitem[], int nItems)
{
	int i;
	MENUITEMINFO mi;
	PWBOBJ pwbo;
	HMENU hMenu, hPopup = NULL;
	LPCTSTR pszLastPopup = NULL;

	if(!pwboParent || !pwboParent->hwnd || !IsWindow(pwboParent->hwnd))
		return NULL;

	// Start building the menu

	hMenu = CreateMenu();

	for(i = 0; i < nItems; i++) {

		if(!pitem[i]) {

			AppendMenu(hPopup, MF_SEPARATOR, 0, NULL);

		} else if(!pitem[i]->id) {

			if(pitem[i]->pszCaption && *pitem[i]->pszCaption) {		// Attach a pop-up menu to a top-level menu
				if(hPopup && pszLastPopup) {
					AppendMenu(hMenu, MF_POPUP, (UINT)hPopup, pszLastPopup);
				}
				hPopup = CreateMenu();
				pszLastPopup = pitem[i]->pszCaption;
			} else {												// Separator
				AppendMenu(hPopup, MF_SEPARATOR, 0, NULL);
			}

		} else {

			if(pitem[i]->pszCaption && *pitem[i]->pszCaption) {		// Create a submenu item
				AppendMenu(hPopup, MF_STRING, pitem[i]->id, pitem[i]->pszCaption);
				if(pitem[i]->pszImage && *pitem[i]->pszImage) {
					HBITMAP hImage = wbLoadImage(pitem[i]->pszImage, 0, 0);

					if(hImage)
						SetMenuItemBitmaps(hPopup, pitem[i]->id, MF_BYCOMMAND, hImage, hImage);
				}
			}
		}
	}

	// Create last first-level menu

	if(hPopup && pszLastPopup) {
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopup, pszLastPopup);
	}

	// Attach the menu to the window

	pwbo = wbMalloc(sizeof(WBOBJ));
	pwbo->hwnd = (HWND)hMenu;
	pwbo->id = 0;
	pwbo->uClass = Menu;
	pwbo->item = -1;
	pwbo->subitem = -1;
	pwbo->style = 0;
	pwbo->pszCallBackFn = NULL;
	pwbo->pszCallBackObj = NULL;
	pwbo->lparam = 0;
	pwbo->parent = pwboParent;

	// ********* DOESN'T WORK
	mi.dwItemData = (DWORD)pwbo;
	SetMenuItemInfo((HMENU)pwbo->hwnd, 0, TRUE, &mi);
	// ********* DOESN'T WORK

	SetMenu(pwboParent->hwnd, hMenu);
	return pwbo;
}