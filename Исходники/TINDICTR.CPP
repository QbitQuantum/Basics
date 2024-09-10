void TIndicator::draw()
{
    uchar color, frame;
    TDrawBuffer b;
    char s[15];

    if( (state & sfDragging) == 0 )
        {
        color = getColor(1);
        frame = dragFrame;
        }
    else
        {
        color = getColor(2);
        frame = normalFrame;
        }

    b.moveChar( 0, frame, color, size.x );
    if( modified )
        b.putChar( 0, 15 );
    ostrstream os( s, 15 );

    os << ' ' << (location.y+1)
       << ':' << (location.x+1) << ' ' << ends;

    b.moveCStr( 8-int(strchr(s, ':')-s), s, color);
    writeBuf(0, 0, size.x, 1, b);
}