void DIALOG_PLOT_SCHEMATIC::createPDFFile( bool aPlotAll, bool aPlotFrameRef )
{
    SCH_SCREEN*     screen = m_parent->GetScreen();
    SCH_SHEET_PATH* sheetpath;
    SCH_SHEET_PATH  oldsheetpath = m_parent->GetCurrentSheet();     // sheetpath is saved here
    wxPoint         plot_offset;

    /* When printing all pages, the printed page is not the current page.  In
     * complex hierarchies, we must update component references and others
     * parameters in the given printed SCH_SCREEN, accordint to the sheet path
     * because in complex hierarchies a SCH_SCREEN (a drawing ) is shared
     * between many sheets and component references depend on the actual sheet
     * path used
     */
    SCH_SHEET_LIST SheetList( NULL );

    sheetpath = SheetList.GetFirst();

    // Allocate the plotter and set the job level parameter
    PDF_PLOTTER* plotter = new PDF_PLOTTER();
    plotter->SetDefaultLineWidth( GetDefaultLineThickness() );
    plotter->SetColorMode( getModeColor() );
    plotter->SetCreator( wxT( "Eeschema-PDF" ) );

    wxString msg;
    wxString plotFileName;

    // First page handling is different
    bool first_page = true;
    do
    {
        // Step over the schematic hierarchy
        if( aPlotAll )
        {
            SCH_SHEET_PATH list;

            if( list.BuildSheetPathInfoFromSheetPathValue( sheetpath->Path() ) )
            {
                m_parent->SetCurrentSheet( list );
                m_parent->GetCurrentSheet().UpdateAllScreenReferences();
                m_parent->SetSheetNumberAndCount();
                screen = m_parent->GetCurrentSheet().LastScreen();
            }
            else // Should not happen
                wxASSERT( 0 );

            sheetpath = SheetList.GetNext();
        }

        if( first_page )
        {
            plotFileName = m_parent->GetUniqueFilenameForCurrentSheet() + wxT( "." )
                           + PDF_PLOTTER::GetDefaultFileExtension();

            if( ! plotter->OpenFile( plotFileName ) )
            {
                msg.Printf( _( "** Unable to create %s **\n" ), GetChars( plotFileName ) );
                m_MessagesBox->AppendText( msg );
                delete plotter;
                return;
            }

            // Open the plotter and do the first page
            SetLocaleTo_C_standard();
            setupPlotPagePDF( plotter, screen );
            plotter->StartPlot();
            first_page = false;
        }
        else
        {
            /* For the following pages you need to close the (finished) page,
             *  reconfigure, and then start a new one */
            plotter->ClosePage();
            setupPlotPagePDF( plotter, screen );
            plotter->StartPage();
        }

        plotOneSheetPDF( plotter, screen, aPlotFrameRef );
    } while( aPlotAll && sheetpath );

    // Everything done, close the plot and restore the environment
    plotter->EndPlot();
    delete plotter;
    SetLocaleTo_Default();

    // Restore the previous sheet
    m_parent->SetCurrentSheet( oldsheetpath );
    m_parent->GetCurrentSheet().UpdateAllScreenReferences();
    m_parent->SetSheetNumberAndCount();

    msg.Printf( _( "Plot: %s OK\n" ), GetChars( plotFileName ) );
    m_MessagesBox->AppendText( msg );
}