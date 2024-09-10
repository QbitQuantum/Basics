/* #FN#
   Populates the tree view control with file list */
void
/* #AS#
   Nothing */
CShellTree::
PopulateTree()
{
	LPSHELLFOLDER lpsf = NULL;
	LPITEMIDLIST  lpi  = NULL;
	HRESULT hr;

	/* Get a pointer to the desktop folder */
	hr = SHGetDesktopFolder( &lpsf );

	if( SUCCEEDED(hr) )
	{
		/* Initialize the tree view to be empty */
		DeleteAllItems();

		/* Fill in the tree view from the root */
		FillTreeView( lpsf, NULL, TVI_ROOT );
		/* Release the folder pointer */
		lpsf->Release();
	}
	TV_SORTCB tvscb;
	tvscb.hParent     = TVI_ROOT;
	tvscb.lParam      = 0;
	tvscb.lpfnCompare = TreeViewCompareProc;

	/* Sort the items in the tree view */
	SortChildrenCB( &tvscb /*, FALSE*/ );

	HTREEITEM hItem = GetRootItem();
	Expand( hItem, TVE_EXPAND );
	Select( GetRootItem(), TVGN_CARET );

} /* #OF# CShellTree::PopulateTree */