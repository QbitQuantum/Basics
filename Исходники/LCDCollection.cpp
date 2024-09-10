void CLCDCollection::OnDraw(CLCDGfxBase &rGfx)
{
    if(!IsVisible())
    {
        return;
    }

    //iterate through your objects and draw them
    LCD_OBJECT_LIST::iterator it = m_Objects.begin();
    while(it != m_Objects.end())
    {
        CLCDBase *pObject = *it++;
        LCDUIASSERT(NULL != pObject);

        if (pObject->IsVisible())
        {
            pObject->OnPrepareDraw(rGfx);

            // create the clip region
            HRGN hRgn = CreateRectRgn(pObject->GetOrigin().x, pObject->GetOrigin().y,
                                      pObject->GetOrigin().x + pObject->GetWidth(),
                                      pObject->GetOrigin().y + pObject->GetHeight());

            // ensure that controls only draw within their specified region
            SelectClipRgn(rGfx.GetHDC(), hRgn);

            // free the region (a copy is used in the call above)
            DeleteObject(hRgn);

            // offset the control at its origin so controls use (0,0)
            POINT ptPrevViewportOrg = { 0, 0 };
            SetViewportOrgEx(rGfx.GetHDC(),
                             pObject->GetOrigin().x,
                             pObject->GetOrigin().y,
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