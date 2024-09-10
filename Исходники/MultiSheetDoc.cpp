void CMultiSheetDoc::SelectSheetView( int i )
{
	POSITION pos = GetFirstViewPosition();
    while (pos != NULL)
    {
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf( RUNTIME_CLASS( CTinyCadView )))
		{
			static_cast<CTinyCadView*>(pView)->SelectSheet( i );
			pView->RedrawWindow();
		}
    }
}