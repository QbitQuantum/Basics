void VScrollBar::draw(Surface& s) const
{
    s.fillRect(scrollArea, Color::darkGray);
    if ( ! movableBar.isEmpty() )
    {
        s.fillRect(movableBar, overScrollable ? Color::gray128 : Color::gray96);
    }
    
    upButton->draw(s);
    downButton->draw(s);
}