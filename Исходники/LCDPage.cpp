void CLCDPage::OnDraw(CLCDGfxBase &rGfx)
{
    if(!IsVisible())
    {
        return;
    }

    //Draw the background first
    if(m_bUseBitmapBackground)
    {
        m_Background.OnDraw(rGfx);
    }
    else if(m_bUseColorBackground)
    {
        HBRUSH hBackBrush = CreateSolidBrush(m_BackgroundColor);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(rGfx.GetHDC(), hBackBrush);
        Rectangle(rGfx.GetHDC(), 0, 0, GetWidth(), GetHeight());
        SelectObject(rGfx.GetHDC(), hOldBrush);
        DeleteObject(hBackBrush);
    }


    //iterate through your objects and draw them
    LCD_OBJECT_LIST::iterator it = m_Objects.begin();
    while(it != m_Objects.end())
    {
        CLCDBase *pObject = *it++;
        LCDUIASSERT(NULL != pObject);

        if (pObject->IsVisible())
        {
            // create the clip region
            // Note that pages can now be added to pages (GetOrigin of the page is now factored in)
            HRGN hRgn = CreateRectRgn(GetOrigin().x + pObject->GetOrigin().x, GetOrigin().y + pObject->GetOrigin().y,
                GetOrigin().x + pObject->GetOrigin().x + pObject->GetWidth(),
                GetOrigin().y + pObject->GetOrigin().y + pObject->GetHeight());

            // ensure that controls only draw within their specified region
            SelectClipRgn(rGfx.GetHDC(), hRgn);

            // free the region (a copy is used in the call above)
            DeleteObject(hRgn);

            // offset the control at its origin so controls use (0,0)
            POINT ptPrevViewportOrg = { 0, 0 };
            SetViewportOrgEx(rGfx.GetHDC(),
                GetOrigin().x + pObject->GetOrigin().x,
                GetOrigin().y + pObject->GetOrigin().y,
                &ptPrevViewportOrg);

            // allow controls to supply additional translation
            // this allows controls to move freely within the confined viewport
            OffsetViewportOrgEx(rGfx.GetHDC(),
                pObject->GetLogicalOrigin().x,
                pObject->GetLogicalOrigin().y,
                NULL);

            pObject->OnDraw(rGfx);

            // set the clipping region to nothing
            SelectClipRgn(rGfx.GetHDC(), NULL);

            // restore the viewport origin
            SetViewportOrgEx(rGfx.GetHDC(),
                ptPrevViewportOrg.x,
                ptPrevViewportOrg.y,
                NULL);

            // restore the viewport origin offset
            OffsetViewportOrgEx(rGfx.GetHDC(), 0, 0, NULL);
        }
    }
}