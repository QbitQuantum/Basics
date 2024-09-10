void ListedTextItems::PaintArea( const Painter &painter, const Rect &area, int stateID)
{
    if ( _skins.Select(stateID) )
    {
        int cur_w = _skins.GetWidth();
        int cur_h = _skins.GetHeight();
        _skins.SetSize( Dim2i( area.GetW(), area.GetH()));
        _skins.Paint( painter, area.GetPos());
        _skins.SetSize( Dim2i( cur_w, cur_h));
    }
}