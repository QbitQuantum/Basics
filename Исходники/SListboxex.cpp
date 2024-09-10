void SListBoxEx::RedrawItem(int iItem)
{
    if(!IsVisible(TRUE)) return;
    CRect rcClient;
    GetClientRect(&rcClient);
    CRect rcItem=GetItemRect(iItem);
    CRect rcInter;
    rcInter.IntersectRect(&rcClient,&rcItem);
    if(rcInter.IsRectEmpty()) return;

    IRenderTarget * pRT=GetRenderTarget(&rcItem,OLEDC_PAINTBKGND);

    SSendMessage(WM_ERASEBKGND,(WPARAM)pRT);
    DrawItem(pRT,rcItem,iItem);

    ReleaseRenderTarget(pRT);
}