void Widget::Align( int inner_alignment)
{
    Rect client_area = GetParent()->GetClientRect( this);
    Rect bound = GetBoundingRect() + GetPosition();
    bound.Align( client_area, Rect::Alignment( inner_alignment));
    SetBoundingRect( bound);
}