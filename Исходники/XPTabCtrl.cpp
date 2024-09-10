//----------------------------------------------------------------------------------------------------------
void CXPTabCtrl::OnPaint() 
{
    if(!IsExtendedTabTheamedXP())            // if it is not XP or it is not Themes, behave as default
    { Default(); return; }    
    CPaintDC dc(this);                        // device context for painting

    CRect rcClip; rcClip.SetRectEmpty();
    dc.GetClipBox(rcClip);

    // 1st paint the tab body
    CRect rcPage,rcItem,rcClient;
    GetClientRect(&rcPage);
    rcClient=rcPage;
    AdjustRect(FALSE,rcPage);

    switch(m_eTabOrientation)
    {    case e_tabTop:      rcClient.top   =rcPage.top   -2; break;
    case e_tabBottom: rcClient.bottom=rcPage.bottom+3; break;
    case e_tabLeft:      rcClient.left  =rcPage.left  -1; break;
    case e_tabRight:  rcClient.right =rcPage.right +3; break;
    default: ASSERT(FALSE); return;
    }
    UINT uiVertBottm;
    uiVertBottm =(m_eTabOrientation&1)? 8:0;        //  8=bottom
    uiVertBottm|=(m_eTabOrientation&2)?16:0;        // 16=vertical
    UINT uiFlags=1|uiVertBottm;                        //  1=body    
    DrawThemesXpTabItem(&dc, -1, rcClient,uiFlags);    // TABP_PANE=9,0,'TAB'

    int nTab=GetItemCount();                        // paint the tabs first and then the borders
    if(!nTab) return;                                // no tab pages added

    // 2nd paint the inactive tabs
    CRect ;
    TCHITTESTINFO hti;    hti.flags=0;
    ::GetCursorPos(&hti.pt); ScreenToClient(&hti.pt);
    int ixHot=HitTest(&hti);
    int ixSel=GetCurSel();

    for(int ixTab=0; ixTab<nTab; ixTab++)
    {    if(ixTab==ixSel)
    continue;
    VERIFY(GetItemRect(ixTab, &rcItem));
    if(m_eTabOrientation==e_tabLeft) rcItem.right++;
    uiFlags=uiVertBottm|(ixTab==ixHot?4:0);        // 4= hot
    DrawThemesXpTabItem(&dc,ixTab,rcItem,uiFlags);
    }
    // 3rd paint the active selected tab
    VERIFY(GetItemRect(ixSel, &rcItem));            // now selected tab
    rcItem.InflateRect(2,2);
    if(m_eTabOrientation==e_tabTop) rcItem.bottom--;
    uiFlags=uiVertBottm|2;                            // 2= selected
    DrawThemesXpTabItem(&dc, ixSel, rcItem,uiFlags);
}