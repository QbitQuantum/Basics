void BOARD_PRINTOUT_CONTROLLER::DrawPage()
{
    wxPoint       offset;
    double        userscale;
    EDA_RECT      boardBoundingBox;
    EDA_RECT      drawRect;
    wxDC*         dc = GetDC();
    BASE_SCREEN*  screen = m_Parent->GetScreen();
    bool          printMirror = m_PrintParams.m_PrintMirror;
    wxSize        pageSizeIU = m_Parent->GetPageSizeIU();

    wxBusyCursor  dummy;

    boardBoundingBox = ((GERBVIEW_FRAME*) m_Parent)->GetGerberLayoutBoundingBox();
    wxString titleblockFilename;    // TODO see if we uses the gerber file name

    // Use the page size as the drawing area when the board is shown or the user scale
    // is less than 1.
    if( m_PrintParams.PrintBorderAndTitleBlock() )
        boardBoundingBox = EDA_RECT( wxPoint( 0, 0 ), pageSizeIU );

    // Compute the PCB size in internal units
    userscale = m_PrintParams.m_PrintScale;

    if( m_PrintParams.m_PrintScale == 0 )   //  fit in page option
    {
        if(boardBoundingBox.GetWidth() && boardBoundingBox.GetHeight())
        {
            int margin = Millimeter2iu( 10.0 ); // add a margin around the drawings
            double scaleX = (double)(pageSizeIU.x - (2 * margin)) /
                            boardBoundingBox.GetWidth();
            double scaleY = (double)(pageSizeIU.y - (2 * margin)) /
                            boardBoundingBox.GetHeight();
            userscale = (scaleX < scaleY) ? scaleX : scaleY;
        }
        else
            userscale = 1.0;
    }

    wxSize scaledPageSize = pageSizeIU;
    drawRect.SetSize( scaledPageSize );
    scaledPageSize.x = wxRound( scaledPageSize.x / userscale );
    scaledPageSize.y = wxRound( scaledPageSize.y / userscale );


    if( m_PrintParams.m_PageSetupData )
    {
        // Always scale to the size of the paper.
        FitThisSizeToPageMargins( scaledPageSize, *m_PrintParams.m_PageSetupData );
    }

    // Compute Accurate scale 1
    if( m_PrintParams.m_PrintScale == 1.0 )
    {
        // We want a 1:1 scale, regardless the page setup
        // like page size, margin ...
        MapScreenSizeToPaper(); // set best scale and offset (scale is not used)
        int w, h;
        GetPPIPrinter( &w, &h );
        double accurate_Xscale = (double) w / (IU_PER_MILS*1000);
        double accurate_Yscale = (double) h / (IU_PER_MILS*1000);

        if( IsPreview() )  // Scale must take in account the DC size in Preview
        {
            // Get the size of the DC in pixels
            wxSize       PlotAreaSize;
            dc->GetSize( &PlotAreaSize.x, &PlotAreaSize.y );
            GetPageSizePixels( &w, &h );
            accurate_Xscale *= (double)PlotAreaSize.x / w;
            accurate_Yscale *= (double)PlotAreaSize.y / h;
        }
        // Fine scale adjust
        accurate_Xscale *= m_PrintParams.m_XScaleAdjust;
        accurate_Yscale *= m_PrintParams.m_YScaleAdjust;

        // Set print scale for 1:1 exact scale
        dc->SetUserScale( accurate_Xscale, accurate_Yscale );
    }

    // Get the final size of the DC in pixels
    wxSize       PlotAreaSizeInPixels;
    dc->GetSize( &PlotAreaSizeInPixels.x, &PlotAreaSizeInPixels.y );

    double scalex, scaley;
    dc->GetUserScale( &scalex, &scaley );

    // In some cases the plot origin is the centre of the board outline rather than the center
    // of the selected paper size.
    if( m_PrintParams.CenterOnBoardOutline() )
    {
        // Here we are only drawing the board and it's contents.
        drawRect = boardBoundingBox;
        offset.x += wxRound( (double) -scaledPageSize.x / 2.0 );
        offset.y += wxRound( (double) -scaledPageSize.y / 2.0 );

        wxPoint center = boardBoundingBox.Centre();

        if( printMirror )
        {
            // Calculate the mirrored center of the board.
            center.x = m_Parent->GetPageSizeIU().x - boardBoundingBox.Centre().x;
        }

        offset += center;
    }

    GRResetPenAndBrush( dc );

    EDA_DRAW_PANEL* panel = m_Parent->GetCanvas();
    EDA_RECT        tmp   = *panel->GetClipBox();

    // Set clip box to the max size
    #define MAX_VALUE (INT_MAX/2)   // MAX_VALUE is the max we can use in an integer
                                    // and that allows calculations without overflow
    panel->SetClipBox( EDA_RECT( wxPoint( 0, 0 ), wxSize( MAX_VALUE, MAX_VALUE ) ) );

    screen->m_IsPrinting = true;
    EDA_COLOR_T bg_color = m_Parent->GetDrawBgColor();

    // Print frame reference, if requested, before printing draw layers
    if( m_PrintParams.m_Print_Black_and_White )
        GRForceBlackPen( true );

    if( m_PrintParams.PrintBorderAndTitleBlock() )
        m_Parent->DrawWorkSheet( dc, screen, m_PrintParams.m_PenDefaultSize,
                                 IU_PER_MILS, titleblockFilename );

    if( printMirror )
    {
        // To plot mirror, we reverse the x axis, and modify the plot x origin
        dc->SetAxisOrientation( false, false );

        /* Change plot offset in order to have the draw area at the same location.
         * The plot origin X is just moved from 0 to PlotAreaSizeInPixels.x.
         * just set offset x at PlotAreaSizeInPixels.x.
         */
        int x_dc_offset = PlotAreaSizeInPixels.x;
        x_dc_offset = KiROUND( x_dc_offset  * userscale );
        dc->SetDeviceOrigin( x_dc_offset, 0 );

        panel->SetClipBox( EDA_RECT( wxPoint( -MAX_VALUE / 2, -MAX_VALUE / 2 ),
                                     panel->GetClipBox()->GetSize() ) );
    }

    // screen->m_DrawOrg = offset;
    dc->SetLogicalOrigin( offset.x, offset.y );
    m_Parent->SetDrawBgColor( WHITE );

    // Never force black pen to print draw layers
    // because negative objects need a white pen, not a black pen
    // B&W mode is handled in print page function
    GRForceBlackPen( false );

    m_Parent->PrintPage( dc, m_PrintParams.m_PrintMaskLayer, printMirror, &m_PrintParams );

    m_Parent->SetDrawBgColor( bg_color );
    screen->m_IsPrinting = false;
    panel->SetClipBox( tmp );
}