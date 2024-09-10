void CAlfSrvDisplaySubSession::SetSessionFocused(TBool aFocused)
    {
    if ( iDisplay )
        {
        if (aFocused)
            {
            // Set clipping rect for display visible area to e.g. avoid unnecesssary 
            // drawing under Avkon status/control pane areas. TV out does not show
            // those so no clipping in that case.
            if (UseVisualAreaClipping())
                {
                TRect clipped = Session().AlfAppUi()->Container()->Rect();
                if (clipped.Intersects(iRect))
                    {
                    clipped.Intersection(iRect);        
                    }
                iDisplay->SetVisibleAreaClippingRect(clipped);        
                iDisplay->SetDirty();
                }

            // If background items are used
            if (iBackgroundItems.Count() != 0)
                {
                TRAP_IGNORE(iDisplay->SetBackgroundItemsL(iBackgroundItems))                        
                }
            else
                {
                TRAP_IGNORE(iDisplay->SetClearBackgroundL(
                        CHuiDisplay::TClearMode(iDisplayClearBackground)))                                        
                }    

            if ( KAlfSrvClientQualitySupport )
                {
                iDisplay->SetQuality(THuiQuality(iDisplayRenderingQuality));
                }
            iDisplay->SetUseDepth(iDisplayUseDepthTest);
            
            UpdateAutomaticFading(); // update non-fading to app ui container
            }
        else
            {
            // Disable clipping rect 
            if (UseVisualAreaClipping())
                {
                iDisplay->SetVisibleAreaClippingRect(TRect(0,0,0,0));        
                iDisplay->SetDirty();
                }                
            }    
        
        if (IsTvOut())
            {
            if (aFocused)
                {
                TRAP_IGNORE(
                    {
                    iDisplay->RestoreL();
                    Session().AlfAppUi()->AppendTvDisplayOnSharedWindowL(*iDisplay);
                    })
                }
            else
                {
                Session().AlfAppUi()->RemoveTvDisplayOnSharedWindow(*iDisplay);
                iDisplay->Release();    
                }                
            }