BOOL FunctionListPanel::setTreeViewImageList(int root_id, int node_id, int leaf_id)
{
	HBITMAP hbmp;
	COLORREF maskColour = RGB(192, 192, 192);
	const int nbBitmaps = 3;

	// Creation of image list
	if ((_hTreeViewImaLst = ImageList_Create(CX_BITMAP, CY_BITMAP, ILC_COLOR32 | ILC_MASK, nbBitmaps, 0)) == NULL) 
		return FALSE;

	// Add the bmp in the list
	hbmp = LoadBitmap(_hInst, MAKEINTRESOURCE(root_id));
	if (hbmp == NULL)
		return FALSE;
	ImageList_AddMasked(_hTreeViewImaLst, hbmp, maskColour);
	DeleteObject(hbmp);

	hbmp = LoadBitmap(_hInst, MAKEINTRESOURCE(node_id));
	if (hbmp == NULL)
		return FALSE;
	ImageList_AddMasked(_hTreeViewImaLst, hbmp, maskColour);
	DeleteObject(hbmp);

	hbmp = LoadBitmap(_hInst, MAKEINTRESOURCE(leaf_id));
	if (hbmp == NULL)
		return FALSE;
	ImageList_AddMasked(_hTreeViewImaLst, hbmp, maskColour);
	DeleteObject(hbmp);

	if (ImageList_GetImageCount(_hTreeViewImaLst) < nbBitmaps)
		return FALSE;

	// Set image list to the tree view
	TreeView_SetImageList(_treeView.getHSelf(), _hTreeViewImaLst, TVSIL_NORMAL);
	TreeView_SetImageList(_treeViewSearchResult.getHSelf(), _hTreeViewImaLst, TVSIL_NORMAL);

	return TRUE;
}