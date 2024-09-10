void CTextureTool::CreateColorCtrl (CWnd *pWnd, int nIdC)
{
CWnd *pParentWnd = GetDlgItem (nIdC);
CRect rc;
pParentWnd->GetClientRect (rc);
pWnd->Create (NULL, NULL, WS_CHILD | WS_VISIBLE, rc, pParentWnd, 0);
}