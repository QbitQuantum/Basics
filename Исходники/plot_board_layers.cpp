/** Open a new plotfile using the options (and especially the format)
 * specified in the options and prepare the page for plotting.
 * Return the plotter object if OK, NULL if the file is not created
 * (or has a problem)
 */
PLOTTER* StartPlotBoard( BOARD *aBoard, PCB_PLOT_PARAMS *aPlotOpts,
                         const wxString& aFullFileName,
                         const wxString& aSheetDesc )
{
    // Create the plotter driver and set the few plotter specific
    // options
    PLOTTER*    plotter = NULL;

    switch( aPlotOpts->GetFormat() )
    {
    case PLOT_FORMAT_DXF:
        plotter = new DXF_PLOTTER();
        break;

    case PLOT_FORMAT_POST:
        PS_PLOTTER* PS_plotter;
        PS_plotter = new PS_PLOTTER();
        PS_plotter->SetScaleAdjust( aPlotOpts->GetFineScaleAdjustX(),
                                    aPlotOpts->GetFineScaleAdjustY() );
        plotter = PS_plotter;
        break;

    case PLOT_FORMAT_PDF:
        plotter = new PDF_PLOTTER();
        break;

    case PLOT_FORMAT_HPGL:
        HPGL_PLOTTER* HPGL_plotter;
        HPGL_plotter = new HPGL_PLOTTER();

        /* HPGL options are a little more convoluted to compute, so
           they're split in an other function */
        ConfigureHPGLPenSizes( HPGL_plotter, aPlotOpts );
        plotter = HPGL_plotter;
        break;

    case PLOT_FORMAT_GERBER:
        plotter = new GERBER_PLOTTER();
        break;

    case PLOT_FORMAT_SVG:
        plotter = new SVG_PLOTTER();
        break;

    default:
        wxASSERT( false );
        return NULL;
    }

    // Compute the viewport and set the other options

    // page layout is not mirrored, so temporary change mirror option
    // just to plot the page layout
    PCB_PLOT_PARAMS plotOpts = *aPlotOpts;

    if( plotOpts.GetPlotFrameRef() && plotOpts.GetMirror() )
        plotOpts.SetMirror( false );

    initializePlotter( plotter, aBoard, &plotOpts );

    if( plotter->OpenFile( aFullFileName ) )
    {
        plotter->StartPlot();

        // Plot the frame reference if requested
        if( aPlotOpts->GetPlotFrameRef() )
        {
            PlotWorkSheet( plotter, aBoard->GetTitleBlock(),
                           aBoard->GetPageSettings(),
                           1, 1, // Only one page
                           aSheetDesc, aBoard->GetFileName() );

            if( aPlotOpts->GetMirror() )
            initializePlotter( plotter, aBoard, aPlotOpts );
        }

        /* When plotting a negative board: draw a black rectangle
         * (background for plot board in white) and switch the current
         * color to WHITE; note the color inversion is actually done
         * in the driver (if supported) */
        if( aPlotOpts->GetNegative() )
        {
            EDA_RECT bbox = aBoard->ComputeBoundingBox();
            FillNegativeKnockout( plotter, bbox );
        }

        return plotter;
    }

    delete plotter;
    return NULL;
}