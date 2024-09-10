bool DIALOG_PLOT_SCHEMATIC::plotOneSheetSVG( EDA_DRAW_FRAME*    aFrame,
        const wxString&    aFileName,
        SCH_SCREEN*        aScreen,
        bool               aPlotBlackAndWhite,
        bool               aPlotFrameRef )
{
    SVG_PLOTTER* plotter = new SVG_PLOTTER();

    const PAGE_INFO&   pageInfo = aScreen->GetPageSettings();
    plotter->SetPageSettings( pageInfo );
    plotter->SetDefaultLineWidth( GetDefaultLineThickness() );
    plotter->SetColorMode( aPlotBlackAndWhite ? false : true );
    wxPoint plot_offset;
    double scale = 1.0;
    plotter->SetViewport( plot_offset, IU_PER_DECIMILS, scale, false );

    // Init :
    plotter->SetCreator( wxT( "Eeschema-SVG" ) );

    if( ! plotter->OpenFile( aFileName ) )
    {
        delete plotter;
        return false;
    }

    LOCALE_IO   toggle;

    plotter->StartPlot();

    if( aPlotFrameRef )
    {
        plotter->SetColor( BLACK );
        PlotWorkSheet( plotter, aFrame->GetTitleBlock(),
                       aFrame->GetPageSettings(),
                       aScreen->m_ScreenNumber, aScreen->m_NumberOfScreens,
                       aFrame->GetScreenDesc(),
                       aScreen->GetFileName() );
    }

    aScreen->Plot( plotter );

    plotter->EndPlot();
    delete plotter;

    return true;
}