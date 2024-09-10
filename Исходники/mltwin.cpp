void ecMemoryLayoutWindow::DrawRegion (wxDC& dc, int uRegion, int uUnitCount, int uPixelsPerUnit, std::list <mem_region>::iterator region)
{
#if 0
    BOOL bDrawFocusRect = FALSE;
    CRect rectAddress;
    CString strAddress;
    
    // setup the drawing objects
    
    CBrush brshUnusedSection;
    if (!brshUnusedSection.CreateHatchBrush (HS_BDIAGONAL, RGB (128, 128, 128)))
        return;
    
    CBrush brshUsedSection;
    if (!brshUsedSection.CreateSolidBrush (GetSysColor (COLOR_WINDOW)))
        return;
    
    CBrush brshInitialSectionBar;
    if (!brshInitialSectionBar.CreateSolidBrush (GetSysColor (COLOR_INACTIVECAPTION)))
        return;
    
    CBrush brshFixedSectionBar;
    if (!brshFixedSectionBar.CreateSolidBrush (GetSysColor (COLOR_ACTIVECAPTION)))
        return;
    
    CBrush brshFinalSectionBar;
    if (!brshFinalSectionBar.CreateSolidBrush (GetSysColor (COLOR_ACTIVECAPTION)))
        return;
    
    CPen penBorder;
    if (!penBorder.CreatePen (PS_SOLID, 1, GetSysColor (COLOR_WINDOWTEXT)))
        return;
    
    CPen penSelected;
    if (!penSelected.CreatePen (PS_SOLID, 2, GetSysColor (COLOR_WINDOWTEXT)))
        return;
    
    // select the border pen object
    
    CPen * pOldPen = pDC->SelectObject (&penBorder);
    
    // calculate the region rectangle
    
    REGIONRECT srRegion;
    srRegion.Rect.SetRect (HORIZ_BORDER, VERT_BORDER + REGION_SPACING * uRegion, HORIZ_BORDER + uUnitCount * uPixelsPerUnit + 1, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + 1);
    srRegion.Region = region;
    listRegionRect.AddTail (srRegion);
    
    // draw the region
    
    CPoint pointOrigin (srRegion.Rect.left, srRegion.Rect.top);
    pDC->LPtoDP (&pointOrigin);
    pointOrigin.x %= 8;
    pointOrigin.y %= 8;
    pDC->SetBrushOrg (pointOrigin);
    CBrush * pOldBrush = pDC->SelectObject (&brshUnusedSection);
    pDC->Rectangle (srRegion.Rect);
    /*
    pDC->MoveTo (srRegion.Rect.left, srRegion.Rect.bottom - 1); // draw tick
    pDC->LineTo (srRegion.Rect.left, srRegion.Rect.bottom + TICK_HEIGHT); // draw tick
    */
    if (region == m_riSelectedRegion)
    {
        bDrawFocusRect = TRUE;
        m_rectSelectedItem = srRegion.Rect;
    }
    
    // draw the region label
    
    CRect rectRegionLabel (HORIZ_BORDER, VERT_BORDER + REGION_SPACING * uRegion - EXTERNAL_TEXT_BORDER - 20, m_uViewWidth - HORIZ_BORDER /*HORIZ_BORDER + uUnitCount * uPixelsPerUnit + 1*/, VERT_BORDER + REGION_SPACING * uRegion - EXTERNAL_TEXT_BORDER);
    CString strRegionLabel;
    strRegionLabel.Format (_T("%s (%08X-%08X)%s"), CString(region->name.c_str ()), region->address, region->address + region->size - 1, ((region->type == read_only) ? _T(" read only") : _T("")));
    pDC->DrawText (strRegionLabel, -1, rectRegionLabel, DT_BOTTOM | DT_SINGLELINE);
    
    // draw the start address of the region
    /*
    rectAddress.SetRect (HORIZ_BORDER, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER, HORIZ_BORDER + ADDRESS_TEXT_SPACE * UNITS_PER_SECTION * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER + 30);
    strAddress.Format (ADDRESS_FORMAT, region->address);
    pDC->DrawText (strAddress, -1, rectAddress, DT_LEFT | DT_SINGLELINE);
    */
    // draw the end address of the region
    /*
    rectAddress.SetRect (HORIZ_BORDER + (uUnitCount - ADDRESS_TEXT_SPACE) * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER, HORIZ_BORDER + (uUnitCount + ADDRESS_TEXT_SPACE) * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER + 30);
    strAddress.Format (ADDRESS_FORMAT, region->address + region->size);
    pDC->DrawText (strAddress, -1, rectAddress, DT_CENTER | DT_SINGLELINE);
    */
    // draw the sections within the region
    
    UINT uSectionUnitCount = 0;
    CRect rectBar;
    SECTIONRECT srSection;
    for (list <mem_section_view>::iterator section_view = region->section_view_list.begin (); section_view != region->section_view_list.end (); ++section_view)
    {
        if (section_view->section != NULL) // the section is used
        {
            // draw the section
            
            pDC->SelectObject (brshUsedSection);
            srSection.Rect.SetRect (HORIZ_BORDER + uSectionUnitCount * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion, HORIZ_BORDER + (uSectionUnitCount + UNITS_PER_SECTION) * uPixelsPerUnit + 1, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + 1);
            srSection.SectionView = section_view;
            listSectionRect.AddTail (srSection);
            pDC->Rectangle (srSection.Rect);
            if (section_view == m_sviSelectedSectionView)
            {
                bDrawFocusRect = TRUE;
                m_rectSelectedItem = srSection.Rect;
            }
            
            // draw text within the section
            
            CString strSection, strSectionLine;
            
            if ((section_view->section_location != initial_location) && (section_view->section->alignment > 1))
            {
                strSectionLine.Format (_T("align %lX\n"), section_view->section->alignment);
                strSection += strSectionLine;
            }
            
            if (section_view->section->size > 0)
            {
                strSectionLine.Format (_T("size %lX\n"), section_view->section->size);
                strSection += strSectionLine;
            }
            
            if (section_view->section_location == final_location)
            {
                strSectionLine.Format (_T("relocated\n"));
                strSection += strSectionLine;
            }
            
            pDC->DrawText (strSection, -1, srSection.Rect - (LPCRECT) CRect (EXTERNAL_TEXT_BORDER, EXTERNAL_TEXT_BORDER + BAR_HEIGHT, EXTERNAL_TEXT_BORDER, EXTERNAL_TEXT_BORDER), DT_LEFT);
            
            // select caption bar colour according to type of section
            
            if (section_view->section_location == initial_location)
            {
                pDC->SetTextColor (GetSysColor (COLOR_INACTIVECAPTIONTEXT));
                pDC->SelectObject (&brshInitialSectionBar);
            }
            else
            {
                pDC->SetTextColor (GetSysColor (COLOR_CAPTIONTEXT));
                pDC->SelectObject (&brshFinalSectionBar);
            }
            
            // draw the caption bar
            
            rectBar.SetRect (HORIZ_BORDER + uSectionUnitCount * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion, HORIZ_BORDER + (uSectionUnitCount + UNITS_PER_SECTION) * uPixelsPerUnit + 1, VERT_BORDER + REGION_SPACING * uRegion + BAR_HEIGHT + 1);
            pDC->Rectangle (rectBar);
            
            // draw the section name within the caption bar
            
            CString strName(section_view->section->name.c_str ());
            CRect *pRect=NULL;
            m_arstrTooltipRects.Lookup(strName,(void *&)pRect);
            UINT format;
            if(pDC->GetTextExtent(strName).cx>rectBar.Width()-2*EXTERNAL_TEXT_BORDER){
                format=DT_LEFT;
                if(pRect){
                    pRect->CopyRect(rectBar);
                } else {
                    pRect=new CRect;
                    m_arstrTooltipRects.SetAt(strName,pRect);
                }
                // Replace final three characters of name with an elipsis
                int nLength=1+max(1,strName.GetLength()-3);
                do {
                    --nLength;
                    strName=strName.Left(nLength)+_T("...");
                } while(nLength>1 && pDC->GetTextExtent(strName).cx>rectBar.Width()-2*EXTERNAL_TEXT_BORDER);
                
                rectBar.left+=EXTERNAL_TEXT_BORDER;
                rectBar.right-=EXTERNAL_TEXT_BORDER;
            } else {
                format=DT_CENTER;
                if (pRect) {
                    m_arstrTooltipRects.RemoveKey(strName);
                }
            }
            
            pDC->DrawText (strName, -1, rectBar, format | DT_VCENTER | DT_SINGLELINE);
            pDC->SetTextColor (GetSysColor (COLOR_WINDOWTEXT));
            
            // find the mem_section item describing the current section_view item
            
            list <mem_section>::iterator MemorySection = section_view->section;
            
            // draw the section address if appropriate
            
            if ((section_view->section_location == initial_location))
            {
                if (MemorySection->initial_location->anchor == absolute)
                {
                    pDC->MoveTo (srSection.Rect.left, srSection.Rect.bottom - 1); // draw tick
                    pDC->LineTo (srSection.Rect.left, srSection.Rect.bottom + TICK_HEIGHT); // draw tick
                    rectAddress.SetRect (HORIZ_BORDER + uSectionUnitCount * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER, (int) (HORIZ_BORDER + (uSectionUnitCount + ADDRESS_TEXT_SPACE * UNITS_PER_SECTION) * uPixelsPerUnit), VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER + 30);
                    strAddress.Format (ADDRESS_FORMAT, MemorySection->initial_location->address);
                    pDC->DrawText (strAddress, -1, rectAddress, DT_LEFT | DT_SINGLELINE);
                    
                    /*
                    if (MemorySection->size > 0) // the end address can be calculated
                    {
                    rectAddress.SetRect (HORIZ_BORDER + (uSectionUnitCount + UNITS_PER_SECTION - ADDRESS_TEXT_SPACE) * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER, HORIZ_BORDER + (uSectionUnitCount + UNITS_PER_SECTION + ADDRESS_TEXT_SPACE) * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER + 30);
                    strAddress.Format (ADDRESS_FORMAT, MemorySection->initial_location->address + MemorySection->size);
                    pDC->DrawText (strAddress, -1, rectAddress, DT_CENTER | DT_SINGLELINE);
                    }
                    */
                }
            }
            
            else if ((section_view->section_location == final_location) || (section_view->section_location == fixed_location))
            {
                if (MemorySection->final_location->anchor == absolute)
                {
                    pDC->MoveTo (srSection.Rect.left, srSection.Rect.bottom - 1); // draw tick
                    pDC->LineTo (srSection.Rect.left, srSection.Rect.bottom + TICK_HEIGHT); // draw tick
                    rectAddress.SetRect (HORIZ_BORDER + uSectionUnitCount * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER, (int) (HORIZ_BORDER + (uSectionUnitCount + ADDRESS_TEXT_SPACE * UNITS_PER_SECTION) * uPixelsPerUnit), VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER + 30);
                    strAddress.Format (ADDRESS_FORMAT, MemorySection->final_location->address);
                    pDC->DrawText (strAddress, -1, rectAddress, DT_LEFT | DT_SINGLELINE);
                    
                    /*
                    if (MemorySection->size > 0) // the end address can be calculated
                    {
                    rectAddress.SetRect (HORIZ_BORDER + (uSectionUnitCount + UNITS_PER_SECTION - ADDRESS_TEXT_SPACE) * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER, HORIZ_BORDER + (uSectionUnitCount + UNITS_PER_SECTION + ADDRESS_TEXT_SPACE) * uPixelsPerUnit, VERT_BORDER + REGION_SPACING * uRegion + MAP_HEIGHT + EXTERNAL_TEXT_BORDER + 30);
                    strAddress.Format (ADDRESS_FORMAT, MemorySection->final_location->address + MemorySection->size);
                    pDC->DrawText (strAddress, -1, rectAddress, DT_CENTER | DT_SINGLELINE);
                    }
                    */
                }
            }
            
            uSectionUnitCount += UNITS_PER_SECTION;
    }
    else
    {
        uSectionUnitCount++; // unused sections occupy a single unit
    }
  }
  
  // draw the focus rectangle around the selected object (if any)
  
  if (bDrawFocusRect)
      pDC->DrawFocusRect (m_rectSelectedItem + CRect (1, 1, 1, 1));
  
  // restore previous drawing objects
  
  pDC->SelectObject (pOldBrush);
  pDC->SelectObject (pOldPen);
#endif
}