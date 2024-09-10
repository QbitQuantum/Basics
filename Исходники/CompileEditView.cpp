BOOL CCompileEditView::CreateSaveMenu()
{
	if(g_pSaveMenu.m_hMenu != NULL)
		g_pSaveMenu.DestroyMenu();
	
	if( !g_pSaveMenu.LoadMenu(IDR_SAVEMENU) )
		return FALSE;

	CTreeCtrlFormula* pTree = NULL;

	if( pTree == NULL )
		return FALSE;
	
	CMenu& popup = *g_pSaveMenu.GetSubMenu(0);
	if( popup.m_hMenu == NULL )
		return FALSE;

	popup.RemoveMenu(0,MF_BYPOSITION);
	pTree->AddTreeGroupToMenu(SAVEMENU_BEGIN,popup);

	return TRUE;
}