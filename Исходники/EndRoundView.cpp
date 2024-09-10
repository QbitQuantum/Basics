// doDraw
//---------------------------------------------------------------------------
void EndRoundView::doDraw(Surface &viewArea, Surface &clientArea)
{
    unsigned int flagHeight = ResourceManager::getFlag(0)->getHeight();
    clientArea.BltRoundRect(RectWinner, 14, Palette::green256.getColorArray());
    clientArea.RoundRect(RectWinner,14, Color::gray);
    
    clientArea.BltRoundRect(RectStates, 14, Palette::darkGray256.getColorArray());
    clientArea.RoundRect(RectStates, 14, Color::gray);
    
    drawPlayerStats(clientArea, flagHeight);

    View::doDraw(viewArea, clientArea);
} // end doDraw