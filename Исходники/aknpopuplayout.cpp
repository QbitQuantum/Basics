EXPORT_C
void AknPopupLayouts::HandleSizeChanged( TAknPopupWindowLayoutDef &aDef,
                                         TAknPopupLayouts aLayout_1,
                                         TAknPopupLayoutsNode *aNode)
    {
    CAknPopupHeadingPane *aHeading = (CAknPopupHeadingPane*)FindControl(aNode, EHeadingNode);
    CEikListBox *aListBox = (CEikListBox*)FindControl(aNode, EListNode);
    CCoeControl *aWindowOwningControl = FindControl(aNode, EWindowOwningNode);
    CAknMessageQueryControl *aMsgQueryCtrl = (CAknMessageQueryControl*)FindControl(aNode, EMessageBoxNode);
    
    TInt aLayout = aLayout_1;
    TInt numofitems = aListBox->Model()->NumberOfItems();

    aListBox->View()->ItemDrawer()->SetSkinEnabledL(ETrue);
    
    TInt maxListHeight = GetMaxListHeight();

    // position popup window's bottom correctly
    TRect clientRect;
    AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EPopupParent, clientRect);
    // set windowrect to minimum size - this will be adjusted later    
    TAknLayoutRect windowRect;
    windowRect.LayoutRect( clientRect, AknLayoutScalable_Avkon::popup_menu_window(8));
    aDef.iWindowRect = windowRect.Rect();
    TRAP_IGNORE( aListBox->View()->ItemDrawer()->SetSkinEnabledL(ETrue) );
    
    // Popup window when the size does not change based on
    // the number of items.
    TBool fixedWindowSize = EFalse;
    if ( (aLayout & EAknPopupLayoutsDynamic) || numofitems == 0 ||
         (aLayout & EAknPopupLayoutsFind) )
        {
        aLayout &= ~EAknPopupLayoutsDynamic;
        fixedWindowSize = ETrue;
        }
        
    // heading =============================================================
    TInt spaceForHeading = 0;
    if (aHeading)
        {
        aHeading->SetLayout( CAknPopupHeadingPane::EListHeadingPane ); 
        TAknLayoutRect tempHeadingRect;
        tempHeadingRect.LayoutRect(clientRect,
            AknLayoutScalable_Avkon::heading_pane(0));
        spaceForHeading = tempHeadingRect.Rect().Height();
        maxListHeight -= spaceForHeading;
        }
    aDef.iPopupMenuWindowOffset=TPoint(0,spaceForHeading);
        
    
    // findbox =============================================================
    TBool windowSizeFind = EFalse;
    TInt spaceForFind = 0;
    if (aLayout & EAknPopupLayoutsFind)
        {
        aLayout &= ~EAknPopupLayoutsFind;
        windowSizeFind = ETrue;
        // calculate space needed for find
        TAknLayoutRect tempFindRect;
        tempFindRect.LayoutRect(clientRect,AknLayoutScalable_Avkon::find_popup_pane_cp2(0));
        spaceForFind = tempFindRect.Rect().Height();
        maxListHeight -= spaceForFind;
        }
    
    // messagebox ==========================================================
    TRect messageRect;
    TInt messageNumOfLines = 0;
    TBool messageBox = EFalse;
    if (aMsgQueryCtrl && aMsgQueryCtrl->Lines() > 0)
        {
        messageBox = ETrue;
        messageNumOfLines = aMsgQueryCtrl->Lines();
        TInt varietyIndex = 0;
        switch(messageNumOfLines)
            {
            case (0):
            case (1): varietyIndex = 0;
            break;          
            case (2): varietyIndex = 1;
            break;
            default : varietyIndex = 2;
            }           
        TAknWindowLineLayout lay = AknLayoutScalable_Apps::loc_type_pane(varietyIndex).LayoutLine();
        TAknLayoutRect layout;
        layout.LayoutRect( TRect(0,0,0,0), lay );           
        messageRect =  layout.Rect();           
        maxListHeight -= messageRect.Height();
        }
    
    TInt minItems = 1;
    
    TRect scrollBarRect(0,0,0,0);
    
    TAknWindowLineLayout listLayout;
    TAknLayoutScalableParameterLimits listLimits;
    
    switch(aLayout)
        {
        case EPopupSNotePopupWindow:
        case EMenuUnknownColumnWindow:
        case EMenuUnknownFormattedCellWindow:
        case EMenuWindow:
            {
            minItems = aHeading ? 5 : 6;
            listLayout = AknLayoutScalable_Avkon::list_single_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_single_pane_cp2_ParamLimits();
            break;
            }
        case EMenuGraphicWindow:
            {
            minItems = 5;
            listLayout = AknLayoutScalable_Avkon::list_single_graphic_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_single_graphic_pane_cp2_ParamLimits();
            break;
            }
        case EMenuGraphicHeadingWindow:
            {
            minItems = 5;
            listLayout = AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2_ParamLimits();
            break;
            }
        case EMenuDoubleWindow:
            {
            minItems = 3;
            listLayout = AknLayoutScalable_Avkon::list_double_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_double_pane_cp2_ParamLimits();
            break;
            }
        case EMenuDoubleLargeGraphicWindow:
            {
            minItems = 3;
            listLayout = AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2_ParamLimits();
            break;
            }
        }
        
    if (!fixedWindowSize)
        {
        minItems = 1;
        }

    TInt maxLayoutItems = listLimits.LastRow() + 1; // last row is a zero based index, we need num items which is 1 based
        
    //aDef.iVertLineExt1.LayoutRect(TRect(1,1,1,1), 0, 0,0, ELayoutEmpty, ELayoutEmpty, 0,0);
    //aDef.iVertLineExt2.LayoutRect(TRect(1,1,1,1), 0, 0,0, ELayoutEmpty, ELayoutEmpty, 0,0);
        
    TAknLayoutRect listItemRect;
    listItemRect.LayoutRect( aDef.iWindowRect, listLayout);
    TInt listItemHeight = listItemRect.Rect().Height();
    TInt maxItems = maxListHeight / listItemHeight;
    // minItems == 1 only if the popuplist is dynamically changeable
    if ( (numofitems > 1) && (minItems == 1) )
        {
        minItems = numofitems;
        }
    if (minItems > maxItems)
        {
        minItems = maxItems;
        }
    // maxItems might be greater than max items from layout -> use layout's maximum
    if (minItems > maxLayoutItems)
        {
        minItems = maxLayoutItems;
        }

    TRect window_rect = AknPopupLayouts::MenuRect(aDef);

    TAknLayoutRect temp, layout;
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect ); 
    TAknWindowLineLayout lineLayout = AknLayoutScalable_Avkon::listscroll_menu_pane(0).LayoutLine();
 
    // Layout data of listscroll_menu_pane are changed for CR 417-35260.
    // The change is just for QHD landscape model.
    // The CR makes listscroll_menu_pane's ir or il bigger than normal,
    // so that width of list item is smaller than needs. Then, first cell 
    // of list item can not be drawn on proper position.
    // Adjustment of layout is a solution for this problem. This is not a perfect idea, but
    // creating a new layout for popuplist is too complex to do that. Adjustment is a must.
    if(Layout_Meta_Data::IsLandscapeOrientation())       
        {
        TInt offset  = AknListBoxLayouts::AdjustPopupLayoutData( screenRect );
        if (!AknLayoutUtils::LayoutMirrored())
            {
            lineLayout.ir -= offset;
            }
        else
            {
            lineLayout.il -= offset;
            }
        }
    temp.LayoutRect( window_rect, lineLayout);        

    layout.LayoutRect( temp.Rect(), AknLayoutScalable_Avkon::list_menu_pane(0));
    TRect tempListRect = layout.Rect(); // this is list's rect for the whole window
    
    // subtract heading, findbox and messagebox from tempListRect
    tempListRect.iBr.iY -= spaceForFind;
    tempListRect.iTl.iY += spaceForHeading;
    tempListRect.iTl.iY += messageRect.Height();
    
    // We really don't want parent relative list layout here because findbox will be overwritten.
    // Just calculate list height and use that.
    TRect nullRect(0,0,0,0);
    listLayout.iH = (TInt16)(minItems * listItemHeight);
    listLayout.ib = ELayoutEmpty;

    aDef.iListRect.LayoutRect(tempListRect,
        listLayout);

    // we have to scale iWindowRect to list rect - layout is not (yet) correct
    TInt usedHeight = aDef.iListRect.Rect().Height()
        + spaceForFind
        + spaceForHeading
        + messageRect.Height();
        
    // popupwindow's inside area
    TInt varietyIndex = Layout_Meta_Data::IsLandscapeOrientation();
    
    TAknLayoutRect insideArea;
    insideArea.LayoutRect(
        window_rect,
        AknLayoutScalable_Avkon::bg_popup_window_pane_g1(varietyIndex) );

    if (layout.Rect().Height() < usedHeight)
        {
        aDef.iWindowRect.iTl.iY -= (usedHeight - layout.Rect().Height());
        }
    
    AknLayoutUtils::TAknCbaLocation cbaLocation = AknLayoutUtils::CbaLocation();    
        
    // In landscape we have to center (on y-axis) popup window (but not with bottom CBA)
    if (varietyIndex == 1 && cbaLocation != AknLayoutUtils::EAknCbaLocationBottom)
        {
        TRect mainPane;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
        TInt diff = (mainPane.Height()-aDef.iWindowRect.Height()) / 2;
        aDef.iWindowRect.iTl.iY -= diff;
        aDef.iWindowRect.iBr.iY -= diff;
                        
        // with right CBA, move window to the right side of the screen
        if (cbaLocation == AknLayoutUtils::EAknCbaLocationRight)
            {
            TInt offset = mainPane.Width()-aDef.iWindowRect.iBr.iX;
            aDef.iWindowRect.iTl.iX += offset;
            aDef.iWindowRect.iBr.iX += offset;
            }        
        
        //should this be uncommented??
        // If we have left CBA, we move window to left side of screen (on x-axis).       
        /*else if (cbaLocation == AknLayoutUtils::EAknCbaLocationLeft)
            {
            TInt xOffset = aDef.iWindowRect.iTl.iX;
            if ( xOffset > 0 )
                {
                aDef.iWindowRect.iTl.iX = 0;
                aDef.iWindowRect.iBr.iX -= xOffset;
                }
            }*/
        }                                                                              
      
    TRect screen;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
        
    TAknLayoutRect cbaRect;
    cbaRect.LayoutRect( screen, 
        AknLayoutScalable_Avkon::popup_sk_window( 0  ).LayoutLine() );
            
    if ( AknLayoutUtils::PenEnabled() )
        {
        TSize size( aDef.iWindowRect.Size() );
        // add softkey height
        size.iHeight += cbaRect.Rect().Height();
        
        // Reduce listbox's and popup's height if total height is more than
        // screen height.
        if ( size.iHeight > screen.Height() )
            {
            listLayout.iH -= ( size.iHeight - screen.Height() );
            aDef.iListRect.LayoutRect( tempListRect, listLayout );
            
            size.iHeight = screen.Height();
            }

        aDef.iWindowRect.SetRect( AknPopupUtils::Position( size, ETrue ), size );
        }

    // now we finally know the window rect: first setup heading
    if (aHeading)
        {
        aDef.iHeadingRect.LayoutRect(AknPopupLayouts::MenuRect(aDef),
            AknLayoutScalable_Avkon::heading_pane(0));
        }
    
    MenuPopupWindowGraphics(aDef);
    aWindowOwningControl->SetRect(WindowRect(aDef));
    HandleSizeAndPositionOfComponents(aDef, aListBox, aHeading);

    layout.LayoutRect(MenuRect(aDef), lineLayout);
    TRect scrollBarClientRect(layout.Rect());
        
    if ( AknLayoutUtils::PenEnabled() )
        {
        // remove softkey height that was added earlier so that
        // scroll bar doesn't get behind the softkey 
        scrollBarClientRect.iBr.iY -= cbaRect.Rect().Height();
        }

    if (aHeading)
        {
        scrollBarClientRect.iTl.iY += spaceForHeading;                
        }
        
    if (windowSizeFind)
        {
        scrollBarClientRect.iBr.iY -= spaceForFind;
        }
        
    if (messageBox)
        {
        scrollBarClientRect.iTl.iY += messageRect.Height();
        }
    varietyIndex = 0;
    AknLayoutUtils::LayoutVerticalScrollBar(
        aListBox->ScrollBarFrame(),
        scrollBarClientRect, 
        AknLayoutScalable_Avkon::scroll_pane_cp25(varietyIndex).LayoutLine() ) ;
        
    if (messageBox)
        {
        TAknLayoutRect msgQuery;
      
        TInt varietyIndex = 0;
        switch(messageNumOfLines)
            {
            case (0):
            case (1): varietyIndex = 0;
            break;          
            case (2): varietyIndex = 1;
            break;
            default : varietyIndex = 2;
            }
        msgQuery.LayoutRect( AknPopupLayouts::MenuRect(aDef),
           AknLayoutScalable_Apps::loc_type_pane(varietyIndex).LayoutLine() );
        aMsgQueryCtrl->SetRect(msgQuery.Rect());
        }

    window_rect = WindowRect(aDef);
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( aListBox );
    TBool defaultContext = EFalse;
    if (!cc)
        {
        cc = aListBox->View()->ItemDrawer()->SkinBackgroundControlContext();
        defaultContext = ETrue;
        }
    if (cc)
        {
        CAknsBasicBackgroundControlContext *bcc = (CAknsBasicBackgroundControlContext*)cc;
        TAknLayoutRect popupBgRect;
        popupBgRect.LayoutRect(window_rect,
                               SkinLayout::Popup_windows_skin_placing__background_slice__Line_1(window_rect));
        bcc->SetBitmap(KAknsIIDQsnFrPopupCenter);
        if (defaultContext) bcc->SetRect(popupBgRect.Rect());
        bcc->SetParentPos(aWindowOwningControl->PositionRelativeToScreen());
        if (defaultContext)
            bcc->SetParentPos(TPoint(0,0));
        }
// handled in CFormattedCellListBoxDataExtension, since listbox does not always cover whole
// window rect (listquery/popup list), especially when items are added after construction        
/*
    // note, that cleanup is done in ~CFormattedCellListBoxData()
    // or ( shudder ) in ~CColumnListBoxData()
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if( feedback )
        {       
        feedback->SetFeedbackArea( aListBox, 0, aListBox->Rect(), 
                    ETouchFeedbackBasic, ETouchEventStylusDown );                                   
        }
*/
}