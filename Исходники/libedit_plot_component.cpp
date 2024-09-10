void LIB_EDIT_FRAME::SVG_PlotComponent( const wxString& aFullFileName )
{
    const bool plotBW = false;
    const PAGE_INFO& pageInfo = GetScreen()->GetPageSettings();

    SVG_PLOTTER* plotter = new SVG_PLOTTER();
    plotter->SetPageSettings( pageInfo );
    plotter->SetDefaultLineWidth( GetDefaultLineThickness() );
    plotter->SetColorMode( plotBW );

    wxPoint plot_offset;
    const double scale = 1.0;

    // Currently, plot units are in decimil
    plotter->SetViewport( plot_offset, IU_PER_MILS/10, scale, false );

    // Init :
    plotter->SetCreator( wxT( "Eeschema-SVG" ) );

    if( ! plotter->OpenFile( aFullFileName ) )
    {
        delete plotter;
        return;
    }

    LOCALE_IO   toggle;

    plotter->StartPlot();

    LIB_PART*      part = GetCurPart();

    if( part )
    {
        TRANSFORM   temp;     // Uses default transform
        wxPoint     plotPos;

        plotPos.x = pageInfo.GetWidthIU() /2;
        plotPos.y = pageInfo.GetHeightIU()/2;

        part->Plot( plotter, GetUnit(), GetConvert(), plotPos, temp );

        // Plot lib fields, not plotted by m_component->Plot():
        part->PlotLibFields( plotter, GetUnit(), GetConvert(), plotPos, temp );
    }

    plotter->EndPlot();
    delete plotter;
}