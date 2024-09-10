/**
* Toggles between including the file into the material list and not.
*/
void MEMainFrame::OnViewIncludeFile() {
	CMenu *mmenu = GetMenu();
	UINT state = mmenu->GetMenuState( ID_VIEW_INCLUDEFILENAME, MF_BYCOMMAND );
	ASSERT( state != 0xFFFFFFFF );
	if( state & MF_CHECKED ) {
		mmenu->CheckMenuItem( ID_VIEW_INCLUDEFILENAME, MF_UNCHECKED | MF_BYCOMMAND );
		m_materialTreeView->InitializeMaterialList( false );
	} else {
		mmenu->CheckMenuItem( ID_VIEW_INCLUDEFILENAME, MF_CHECKED | MF_BYCOMMAND );
		m_materialTreeView->InitializeMaterialList( true );
	}
}