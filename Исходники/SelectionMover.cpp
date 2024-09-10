//nikai 2010.9.3
void SelectionMover::AlignSpaceBetween(int PaddingValue, const PaddingAlign al)
{
    // Validations
    wxASSERT_MSG(m_selection != NULL, wxT("Selection member is NULL"));

    if(m_selection->Size() <= 1) 
    {
        // Should not happen because of the disabled menu/toolbar item in this case
        LogWarning(wxT("You must select more than one window to align!"));
        return;
    }
    // The first selected window is the one to match. This is for example how Visual Studio's 
    // dialog editor works as well.
    Selection::Boxes::iterator boxIt = m_selection->GetMoveableBoxes().begin();

    const CEGUI::Window *current = boxIt->GetWindow();
            
    CEGUI::Window *pParentWin = current->getParent();
    if(NULL == pParentWin)
    {
        LogWarning(wxT("You can't operate the root window!"));
        wxMessageBox(L"You can't operate the root window!");
        return;
    }
    const long ParentX = CEGUI::CoordConverter::windowToScreenX(*pParentWin,0);
    const long ParentY = CEGUI::CoordConverter::windowToScreenY(*pParentWin,0);
    const long parentWidth = pParentWin->getPixelSize().d_width;
    const long parentHeight = pParentWin->getPixelSize().d_height;

    const CEGUI::URect rect = current->getArea();
    ++boxIt;
    
    for(; boxIt != m_selection->GetMoveableBoxes().end(); ++boxIt) {
        // Deny when it is blocked
        if (boxIt->IsLocked())
        {
            wxMessageBox(L"all the select window ¡¯s can't be locked£¡");
            return;
        }
        CEGUI::Window* curWin = boxIt->GetWindow();
        if (pParentWin != curWin->getParent())
        {
            wxMessageBox(L"all the select window ¡¯s parent must be same£¡");
            return;
        }
    }
    //»Ö¸´µü´úÆ÷Î»ÖÃ
    //boxIt = m_selection->GetMoveableBoxes().begin(); 
    //++boxIt;
    //float lWidth  = current->getPixelSize().d_width;
    //float lHeight = current->getPixelSize().d_height;
    //float RightPos = CEGUI::CoordConverter::windowToScreenX(*current,0)+lWidth;
    //float BottomPos = CEGUI::CoordConverter::windowToScreenY(*current,0)+lHeight;
    //
    //for(; boxIt != m_selection->GetMoveableBoxes().end(); ++boxIt)
    //{
    //    CEGUI::Window* curWin = boxIt->GetWindow();
    //    CEGUI::UDim xPos = curWin->getXPosition();
    //    CEGUI::UDim yPos = curWin->getYPosition();
    //    switch(al)
    //    {
    //    case HorzPadding:
    //        {
    //            float newXPixel = RightPos + PaddingValue;
    //            float xscale = (newXPixel-ParentX)/parentWidth;
    //            xPos = CEGUI::UDim(xscale,0);
    //            break;
    //        }
    //    case VertPadding:
    //        {
    //            float newYPixel = BottomPos + PaddingValue;
    //            float yscale = (newYPixel-ParentY)/parentHeight;
    //            yPos = CEGUI::UDim(yscale,0);
    //            break;
    //        }
    //    default:
    //        LogError(wxT("SelectionMover::AlignSelection - Unrecognized align option (%d)"), al);
    //        return;
    //    }
    //    curWin->setPosition(CEGUI::UVector2(xPos,yPos));
    //    lWidth  = curWin->getPixelSize().d_width;
    //    lHeight = curWin->getPixelSize().d_height;
    //    RightPos = CEGUI::CoordConverter::windowToScreenX(*curWin,0)+lWidth;
    //    BottomPos = CEGUI::CoordConverter::windowToScreenY(*curWin,0)+lHeight;
    //}
    //// Request for a repaint
    //wxGetApp().GetMainFrame()->Refresh();
    boxIt = m_selection->GetMoveableBoxes().begin(); 
    ++boxIt;
    float newPixelWidth  = current->getPixelSize().d_width;
    float newPixelHeight = current->getPixelSize().d_height;
    float RightPos = CEGUI::CoordConverter::windowToScreenX(*current,0)+newPixelWidth;
    float BottomPos = CEGUI::CoordConverter::windowToScreenY(*current,0)+newPixelHeight;

    for(; boxIt != m_selection->GetMoveableBoxes().end(); ++boxIt)
    {
        CEGUI::Window* curWin = boxIt->GetWindow();
        float fLeft = CEGUI::CoordConverter::windowToScreenX(*curWin,0);
        float fTop  = CEGUI::CoordConverter::windowToScreenY(*curWin,0);
        newPixelWidth  = curWin->getPixelSize().d_width;
        newPixelHeight = curWin->getPixelSize().d_height;
        float fRight  = fLeft  + newPixelWidth;
        float fBottom = fTop + newPixelHeight;

        CEGUI::URect newWindowArea = curWin->getArea();
        float sLeft = 0.0f,sTop = 0.0f,sRight = 0.0f, sBottom = 0.0f;
        switch(al)
        {
        case HorzPadding:
            {
                float newXPixel = RightPos + PaddingValue;
                sRight = sLeft = newXPixel - fLeft;
                break;
            }
        case VertPadding:
            {
                float newYPixel = BottomPos + PaddingValue;
                sBottom = sTop = newYPixel - fTop;
                break;
            }
        default:
            LogError(wxT("SelectionMover::AlignSelection - Unrecognized align option (%d)"), al);
            return;
        }

        MoveUsingScale(curWin,newWindowArea,sLeft,sTop,sRight,sBottom);
        curWin->setArea(newWindowArea);
        fLeft = CEGUI::CoordConverter::windowToScreenX(*curWin,0);
        fTop  = CEGUI::CoordConverter::windowToScreenY(*curWin,0);
        RightPos  = fLeft + newPixelWidth;
        BottomPos = fTop  + newPixelHeight;
    }
    // Request for a repaint
    wxGetApp().GetMainFrame()->Refresh();
}