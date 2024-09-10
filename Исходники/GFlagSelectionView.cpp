void GFlagSelectionView::doDraw(Surface &viewArea, Surface &clientArea)
{
    clientArea.BltRoundRect(rect, 14, Palette::darkGray256.getColorArray());
    clientArea.RoundRect(rect,14, Color::gray);

    ResourceManager::getFlag(PlayerInterface::getLocalPlayerIndex())->blt(clientArea, loc_player_flag.x, loc_player_flag.y);

    View::doDraw(viewArea, clientArea);
} // end doDraw