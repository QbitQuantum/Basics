//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMapCheckDlg::OnGo() 
{
	CMapDoc *pDoc = CMapDoc::GetActiveMapDoc();

	// change description to match error
	int iSel = m_Errors.GetCurSel();

	if(iSel == LB_ERR)
		return;	// no sel

	MapError *pError;
	pError = (MapError*) m_Errors.GetItemDataPtr(iSel);

	VIEW2DINFO vi;
	vi.wFlags = VI_CENTER;

	// get centerpoint
	pError->pObjects[0]->GetBoundsCenter(vi.ptCenter);
	g_pToolManager->SetTool(TOOL_POINTER);
	pDoc->SelectObject(pError->pObjects[0], CMapDoc::scClear | 
		CMapDoc::scSelect | CMapDoc::scUpdateDisplay);
	pDoc->SetView2dInfo(vi);
}