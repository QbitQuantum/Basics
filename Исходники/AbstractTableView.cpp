void AbstractTableView::Initialize()
{
    // Required to be called by each constructor because
    // of VTable changes
    //
    // Init all other updates once
    updateColors();
    updateFonts();
    updateShortcuts();
}