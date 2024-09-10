void CCheckBTGroup::GetPanelRect( CRect &rect )
{
    CWnd *Parent = m_ChkGrpInfo.Parent;
    Parent->GetDlgItem(m_ChkGrpInfo.AreaCtrlID)->GetWindowRect(&rect);
    Parent->ScreenToClient(&rect);
    rect.left = rect.left + 5;
    rect.top  = rect.top + 10;
    rect.right= rect.right - 2;
    rect.bottom = rect.bottom - 5;
}