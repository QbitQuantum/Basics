Rect TableWidget::ColumnRect( int column ) const
{
    int last_row = GetNumRows() -1;
    
    Rect R = CellRect( column, 0) | CellRect( column, last_row);
    Rect r = ClientRect( column, 0) | ClientRect( column, last_row);

    return Rect( r.GetX1(), R.GetY1(), r.GetW(), R.GetH() );
}