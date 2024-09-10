CRect CRegisterTabs::GetPageRect()
{
    CWindow parentWin = GetParent();
    CRect pageRect;
    GetWindowRect(&pageRect);
    parentWin.ScreenToClient(&pageRect);
    AdjustRect(FALSE, &pageRect);
    return pageRect;
}