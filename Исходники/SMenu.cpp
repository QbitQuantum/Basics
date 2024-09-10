void SMenuODWnd::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    CRect rcItem=lpDrawItemStruct->rcItem;
    rcItem.MoveToXY(0,0);
    SMenuItemData *pdmmi=(SMenuItemData*)lpDrawItemStruct->itemData;

    HDC dc(lpDrawItemStruct->hDC);
    CAutoRefPtr<IRenderTarget> pRT;
    GETRENDERFACTORY->CreateRenderTarget(&pRT,rcItem.Width(),rcItem.Height());

    if(pdmmi)
    {
        MENUITEMINFO mii= {sizeof(MENUITEMINFO),MIIM_FTYPE,0};
        HMENU menuPopup=pdmmi->hMenu;
        GetMenuItemInfo(menuPopup,pdmmi->nID,FALSE,&mii);

        BOOL bDisabled = lpDrawItemStruct->itemState & ODS_GRAYED;
        BOOL bSelected = lpDrawItemStruct->itemState & ODS_SELECTED;
        BOOL bChecked = lpDrawItemStruct->itemState & ODS_CHECKED;
        BOOL bRadio = mii.fType&MFT_RADIOCHECK;
        m_pItemSkin->Draw(pRT,rcItem,bSelected?1:0);    //draw background

        //draw icon
        CRect rcIcon;
        rcIcon.left=rcItem.left+m_nIconMargin;
        rcIcon.right=rcIcon.left+m_szIcon.cx;
        rcIcon.top=rcItem.top+(rcItem.Height()-m_szIcon.cy)/2;
        rcIcon.bottom=rcIcon.top+m_szIcon.cy;
        if(bChecked)
        {
            if(m_pCheckSkin)
            {
                m_pCheckSkin->Draw(pRT,rcIcon,bRadio?1:0);
            }
        }
        else if(pdmmi->itemInfo.iIcon!=-1 && m_pIconSkin)
        {
            m_pIconSkin->Draw(pRT,rcIcon,pdmmi->itemInfo.iIcon);
        }
        rcItem.left=rcIcon.right+m_nIconMargin;

        //draw text
        CRect rcTxt=rcItem;
        rcTxt.DeflateRect(m_nTextMargin,0);

        COLORREF crOld=pRT->SetTextColor(bDisabled?m_crTxtGray:(bSelected?m_crTxtSel:m_crTxtNormal));


        CAutoRefPtr<IFont> oldFont;
        pRT->SelectObject(m_hFont,(IRenderObj**)&oldFont);
        pRT->DrawText(pdmmi->itemInfo.strText,pdmmi->itemInfo.strText.GetLength(),&rcTxt,DT_SINGLELINE|DT_VCENTER|DT_LEFT);
        pRT->SelectObject(oldFont);

        pRT->SetTextColor(crOld);

        if(bSelected && m_pItemSkin->GetStates()>2)
        {
            //draw select mask
            CRect rcItem=lpDrawItemStruct->rcItem;
            rcItem.MoveToXY(0,0);
            m_pItemSkin->Draw(pRT,rcItem,2);
        }
    }
    else  //if(strcmp("sep",pXmlItem->Value())==0)
    {
        m_pItemSkin->Draw(pRT,rcItem,0);    //draw back
        if(m_pIconSkin)
        {
            rcItem.left += m_pIconSkin->GetSkinSize().cx+m_nIconMargin*2;
        }

        if(m_pSepSkin)
            m_pSepSkin->Draw(pRT,&rcItem,0);
        else
        {
            CAutoRefPtr<IPen> pen1,pen2,oldPen;
            pRT->CreatePen(PS_SOLID,RGBA(196,196,196,255),1,&pen1);
            pRT->CreatePen(PS_SOLID,RGBA(255,255,255,255),1,&pen2);
            pRT->SelectObject(pen1,(IRenderObj**)&oldPen);
            POINT pts[2]={{rcItem.left,rcItem.top},{rcItem.right,rcItem.top}};
            pRT->DrawLines(pts,2);
            pRT->SelectObject(pen2);
            pts[0].y++,pts[1].y++;
            pRT->DrawLines(pts,2);
            pRT->SelectObject(oldPen);
        }
    }
    rcItem=lpDrawItemStruct->rcItem;
    
    HDC hmemdc=pRT->GetDC(0);
    BitBlt(dc,rcItem.left,rcItem.top,rcItem.Width(),rcItem.Height(),hmemdc,0,0,SRCCOPY);
    pRT->ReleaseDC(hmemdc);
}