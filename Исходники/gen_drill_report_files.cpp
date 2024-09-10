bool GENDRILL_WRITER_BASE::genDrillMapFile( const wxString& aFullFileName,
                                            PlotFormat aFormat )
{
    // Remark:
    // Hole list must be created before calling this function, by buildHolesList(),
    // for the right holes set (PTH, NPTH, buried/blind vias ...)

    double          scale = 1.0;
    wxPoint         offset;
    PLOTTER*        plotter = NULL;
    PAGE_INFO dummy( PAGE_INFO::A4, false );

    PCB_PLOT_PARAMS plot_opts;  // starts plotting with default options

    LOCALE_IO       toggle;     // use standard C notation for float numbers

    const PAGE_INFO& page_info =  m_pageInfo ? *m_pageInfo : dummy;

    // Calculate dimensions and center of PCB
    EDA_RECT        bbbox = m_pcb->GetBoardEdgesBoundingBox();

    // Calculate the scale for the format type, scale 1 in HPGL, drawing on
    // an A4 sheet in PS, + text description of symbols
    switch( aFormat )
    {
    case PLOT_FORMAT_GERBER:
        offset  = GetOffset();
        plotter = new GERBER_PLOTTER();
        plotter->SetViewport( offset, IU_PER_MILS/10, scale, false );
        plotter->SetGerberCoordinatesFormat( 5 );   // format x.5 unit = mm
        break;

    case PLOT_FORMAT_HPGL:    // Scale for HPGL format.
    {
        HPGL_PLOTTER* hpgl_plotter = new HPGL_PLOTTER;
        plotter = hpgl_plotter;
        hpgl_plotter->SetPenNumber( plot_opts.GetHPGLPenNum() );
        hpgl_plotter->SetPenSpeed( plot_opts.GetHPGLPenSpeed() );
        plotter->SetPageSettings( page_info );
        plotter->SetViewport( offset, IU_PER_MILS/10, scale, false );
    }
        break;


    default:
        wxASSERT( false );
        // fall through
    case PLOT_FORMAT_PDF:
    case PLOT_FORMAT_POST:
    {
        PAGE_INFO   pageA4( wxT( "A4" ) );
        wxSize      pageSizeIU = pageA4.GetSizeIU();

        // Reserve a margin around the page.
        int         margin = KiROUND( 20 * IU_PER_MM );

        // Calculate a scaling factor to print the board on the sheet
        double      Xscale = double( pageSizeIU.x - ( 2 * margin ) ) / bbbox.GetWidth();

        // We should print the list of drill sizes, so reserve room for it
        // 60% height for board 40% height for list
        int     ypagesize_for_board = KiROUND( pageSizeIU.y * 0.6 );
        double  Yscale = double( ypagesize_for_board - margin ) / bbbox.GetHeight();

        scale = std::min( Xscale, Yscale );

        // Experience shows the scale should not to large, because texts
        // create problem (can be to big or too small).
        // So the scale is clipped at 3.0;
        scale = std::min( scale, 3.0 );

        offset.x    = KiROUND( double( bbbox.Centre().x ) -
                               ( pageSizeIU.x / 2.0 ) / scale );
        offset.y    = KiROUND( double( bbbox.Centre().y ) -
                               ( ypagesize_for_board / 2.0 ) / scale );

        if( aFormat == PLOT_FORMAT_PDF )
            plotter = new PDF_PLOTTER;
        else
            plotter = new PS_PLOTTER;

        plotter->SetPageSettings( pageA4 );
        plotter->SetViewport( offset, IU_PER_MILS/10, scale, false );
    }
        break;

    case PLOT_FORMAT_DXF:
    {
        DXF_PLOTTER* dxf_plotter = new DXF_PLOTTER;
        plotter = dxf_plotter;
        plotter->SetPageSettings( page_info );
        plotter->SetViewport( offset, IU_PER_MILS/10, scale, false );
    }
        break;

    case PLOT_FORMAT_SVG:
    {
        SVG_PLOTTER* svg_plotter = new SVG_PLOTTER;
        plotter = svg_plotter;
        plotter->SetPageSettings( page_info );
        plotter->SetViewport( offset, IU_PER_MILS/10, scale, false );
    }
        break;
    }

    plotter->SetCreator( wxT( "PCBNEW" ) );
    plotter->SetDefaultLineWidth( 5 * IU_PER_MILS );
    plotter->SetColorMode( false );

    if( ! plotter->OpenFile( aFullFileName ) )
    {
        delete plotter;
        return false;
    }

    plotter->StartPlot();

    // Draw items on edge layer (not all, only items useful for drill map
    BRDITEMS_PLOTTER itemplotter( plotter, m_pcb, plot_opts );
    itemplotter.SetLayerSet( Edge_Cuts );

    for( auto PtStruct : m_pcb->Drawings() )
    {
        switch( PtStruct->Type() )
        {
        case PCB_LINE_T:
            itemplotter.PlotDrawSegment( (DRAWSEGMENT*) PtStruct );
            break;

        case PCB_TEXT_T:
            itemplotter.PlotTextePcb( (TEXTE_PCB*) PtStruct );
            break;

        case PCB_DIMENSION_T:
        case PCB_TARGET_T:
        case PCB_MARKER_T:     // do not draw
        default:
            break;
        }
    }

    int         x, y;
    int         plotX, plotY, TextWidth;
    int         intervalle = 0;
    char        line[1024];
    wxString    msg;
    int         textmarginaftersymbol = KiROUND( 2 * IU_PER_MM );

    // Set Drill Symbols width
    plotter->SetDefaultLineWidth( 0.2 * IU_PER_MM / scale );
    plotter->SetCurrentLineWidth( -1 );

    // Plot board outlines and drill map
    plotDrillMarks( plotter );

    // Print a list of symbols used.
    int     charSize    = 3 * IU_PER_MM;                    // text size in IUs
    double  charScale   = 1.0 / scale;                      // real scale will be 1/scale,
                                                            // because the global plot scale is scale
    TextWidth   = KiROUND( (charSize * charScale) / 10.0 );    // Set text width (thickness)
    intervalle  = KiROUND( charSize * charScale ) + TextWidth;

    // Trace information.
    plotX   = KiROUND( bbbox.GetX() + textmarginaftersymbol * charScale );
    plotY   = bbbox.GetBottom() + intervalle;

    // Plot title  "Info"
    wxString Text = wxT( "Drill Map:" );
    plotter->Text( wxPoint( plotX, plotY ), COLOR4D::UNSPECIFIED, Text, 0,
                   wxSize( KiROUND( charSize * charScale ),
                           KiROUND( charSize * charScale ) ),
                   GR_TEXT_HJUSTIFY_LEFT, GR_TEXT_VJUSTIFY_CENTER,
                   TextWidth, false, false );

    for( unsigned ii = 0; ii < m_toolListBuffer.size(); ii++ )
    {
        DRILL_TOOL& tool = m_toolListBuffer[ii];

        if( tool.m_TotalCount == 0 )
            continue;

        plotY += intervalle;

        int plot_diam = KiROUND( tool.m_Diameter );
        x = KiROUND( plotX - textmarginaftersymbol * charScale - plot_diam / 2.0 );
        y = KiROUND( plotY + charSize * charScale );
        plotter->Marker( wxPoint( x, y ), plot_diam, ii );

        // List the diameter of each drill in mm and inches.
        sprintf( line, "%2.2fmm / %2.3f\" ",
                 diameter_in_mm( tool.m_Diameter ),
                 diameter_in_inches( tool.m_Diameter ) );

        msg = FROM_UTF8( line );

        // Now list how many holes and ovals are associated with each drill.
        if( ( tool.m_TotalCount == 1 )
            && ( tool.m_OvalCount == 0 ) )
            sprintf( line, "(1 hole)" );
        else if( tool.m_TotalCount == 1 ) // && ( toolm_OvalCount == 1 )
            sprintf( line, "(1 slot)" );
        else if( tool.m_OvalCount == 0 )
            sprintf( line, "(%d holes)", tool.m_TotalCount );
        else if( tool.m_OvalCount == 1 )
            sprintf( line, "(%d holes + 1 slot)", tool.m_TotalCount - 1 );
        else // if ( toolm_OvalCount > 1 )
            sprintf( line, "(%d holes + %d slots)",
                     tool.m_TotalCount - tool.m_OvalCount,
                     tool.m_OvalCount );

        msg += FROM_UTF8( line );

        if( tool.m_Hole_NotPlated )
            msg += wxT( " (not plated)" );

        plotter->Text( wxPoint( plotX, y ), COLOR4D::UNSPECIFIED, msg, 0,
                       wxSize( KiROUND( charSize * charScale ),
                               KiROUND( charSize * charScale ) ),
                       GR_TEXT_HJUSTIFY_LEFT, GR_TEXT_VJUSTIFY_CENTER,
                       TextWidth, false, false );

        intervalle = KiROUND( ( ( charSize * charScale ) + TextWidth ) * 1.2 );

        if( intervalle < ( plot_diam + ( 1 * IU_PER_MM / scale ) + TextWidth ) )
            intervalle = plot_diam + ( 1 * IU_PER_MM / scale ) + TextWidth;
    }

    plotter->EndPlot();
    delete plotter;

    return true;
}