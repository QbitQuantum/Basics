bool wxVScrolledWindow::ScrollToLine(size_t line)
{
    if ( !m_lineMax )
    {
        // we're empty, code below doesn't make sense in this case
        return false;
    }

    // determine the real first line to scroll to: we shouldn't scroll beyond
    // the end
    size_t lineFirstLast = FindFirstFromBottom(m_lineMax - 1, true);
    if ( line > lineFirstLast )
        line = lineFirstLast;

    // anything to do?
    if ( line == m_lineFirst )
    {
        // no
        return false;
    }


    // remember the currently shown lines for the refresh code below
    size_t lineFirstOld = GetVisibleBegin(),
           lineLastOld = GetVisibleEnd();

    m_lineFirst = line;


    // the size of scrollbar thumb could have changed
    UpdateScrollbar();


    // finally refresh the display -- but only redraw as few lines as possible
    // to avoid flicker
    if ( GetChildren().empty() &&
         (GetVisibleBegin() >= lineLastOld || GetVisibleEnd() <= lineFirstOld ) )
    {
        // the simplest case: we don't have any old lines left, just redraw
        // everything
        Refresh();
    }
    else // overlap between the lines we showed before and should show now
    {
        // Avoid scrolling visible parts of the screen on Mac
#ifdef __WXMAC__
        if (!IsShownOnScreen())
            Refresh();
        else
#endif
        ScrollWindow(0, GetLinesHeight(GetVisibleBegin(), lineFirstOld));
    }

    return true;
}