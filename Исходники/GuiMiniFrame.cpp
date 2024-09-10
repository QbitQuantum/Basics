CWnd* CGuiMiniFrame::GetChildWnd()
{
	
	CWnd* pBar = GetWindow( GW_CHILD );
    if( pBar == NULL ) return NULL;
	pBar = pBar->GetWindow( GW_CHILD );
    if( pBar == NULL ) return NULL;
	return pBar;
}