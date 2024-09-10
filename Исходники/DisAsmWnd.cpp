void CDisAsmWnd::RefreshLayout()
{
	RECT rc = GetClientRect();
	m_disAsm->SetSize(rc.right, rc.bottom);
}