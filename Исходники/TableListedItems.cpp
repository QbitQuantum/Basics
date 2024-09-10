void TableListedItems::PaintClients( const WidgetPainter &painter )
{
    Pos p;
    Dim2i d( GetWidth(), 0);

    Rect client_area = GetParent()->GetClientRect(this)-GetPosition();
    Rect visibile = TableWidget::GetCrossing( client_area );
    
    p.y = RowRect( visibile.GetY1() ).GetY();
    for ( int i=visibile.GetY1(); i<visibile.GetY2(); ++i )
    {
        d.y = GetRowHeight(i);

        int last_col = GetNumColumns() -1;
        Rect fa = RowRect( i );

        if ( _skins.Select( GetState(i) ) )
        {
            _skins.SetSize( Dim2i(fa.GetW(),fa.GetH()) );
        }
        _skins.Paint( painter, fa.GetPos(), fa );

        p.y += d.y;
    }
}