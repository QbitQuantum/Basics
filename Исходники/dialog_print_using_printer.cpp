/*
 * This is the real print function: print the active screen
 */
void SCH_PRINTOUT::DrawPage( SCH_SCREEN* aScreen )
{
    int      oldZoom;
    wxPoint  tmp_startvisu;
    wxSize   pageSizeIU;             // Page size in internal units
    wxPoint  old_org;
    EDA_RECT oldClipBox;
    wxRect   fitRect;
    wxDC*    dc = GetDC();
    EDA_DRAW_PANEL* panel = m_parent->GetCanvas();

    wxBusyCursor dummy;

    // Save current scale factor, offsets, and clip box.
    tmp_startvisu = aScreen->m_StartVisu;
    oldZoom = aScreen->GetZoom();
    old_org = aScreen->m_DrawOrg;

    oldClipBox = *panel->GetClipBox();

    // Change clip box to print the whole page.
    #define MAX_VALUE (INT_MAX/2)   // MAX_VALUE is the max we can use in an integer
                                    // and that allows calculations without overflow
    panel->SetClipBox( EDA_RECT( wxPoint( 0, 0 ), wxSize( MAX_VALUE, MAX_VALUE ) ) );

    // Change scale factor and offset to print the whole page.
    bool printReference = m_parent->GetPrintSheetReference();

    pageSizeIU = aScreen->GetPageSettings().GetSizeIU();
    FitThisSizeToPaper( pageSizeIU );
    fitRect = GetLogicalPaperRect();

    wxLogDebug( wxT( "Fit rectangle: x = %d, y = %d, w = %d, h = %d" ),
                fitRect.x, fitRect.y, fitRect.width, fitRect.height );

    // When is the actual paper size does not match the schematic page
    // size, the drawing is not perfectly centered on X or Y axis.
    // Give a draw offset centers the schematic page on the paper draw area
    // Because the sizes are fitted, only an Y or X offset is needed
    // and both are 0 when sizes are identical.
    // Y or Y offset is not null when the X/Y size ratio differs between
    // the actual paper size and the schematic page
    int xoffset = ( fitRect.width - pageSizeIU.x ) / 2;

    // For an obscure reason, OffsetLogicalOrigin creates issues,
    // under some circumstances, when yoffset is not always null
    // and changes from a page to an other page
    // This is only a workaround, not a fix
    // see https://bugs.launchpad.net/kicad/+bug/1464773
    // xoffset does not create issues.
#if 0   // FIX ME
    int yoffset = ( fitRect.height - pageSizeIU.y ) / 2;
#else
    // the Y centering will be not perfect, but this is less annoying
    // than a blank page or a buggy centering
    int yoffset = 0;
#endif
    OffsetLogicalOrigin( xoffset, yoffset );

    GRResetPenAndBrush( dc );

    if( m_parent->GetPrintMonochrome() )
        GRForceBlackPen( true );

    aScreen->m_IsPrinting = true;

    EDA_COLOR_T bg_color = m_parent->GetDrawBgColor();

    aScreen->Draw( panel, dc, (GR_DRAWMODE) 0 );

    if( printReference )
        m_parent->DrawWorkSheet( dc, aScreen, GetDefaultLineThickness(),
                IU_PER_MILS, aScreen->GetFileName() );

    m_parent->SetDrawBgColor( bg_color );
    aScreen->m_IsPrinting = false;
    panel->SetClipBox( oldClipBox );

    GRForceBlackPen( false );

    aScreen->m_StartVisu = tmp_startvisu;
    aScreen->m_DrawOrg   = old_org;
    aScreen->SetZoom( oldZoom );
}