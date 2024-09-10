BOOL KSceneSettingPageRegionSplit::OnItemSelectChange( KSceneSceneTreeCtrl& tree, HTREEITEM hItemInserted, HTREEITEM hItemLastSelect )
{
	KSceneSettingPageRegionSplit* pDialog = this;
	_ASSERTE(pDialog->IsValidInMemory());

	pDialog->SynFromInnerToInterface();

	if(BST_CHECKED == pDialog->IsDlgButtonChecked(IDC_CK_SHOW2))
		pDialog->EnableShowMask(TRUE);
	return TRUE;
}