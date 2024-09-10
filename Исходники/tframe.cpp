void TFrame::draw()
{
    ushort cFrame, cTitle;
    short  f, i, l, width;
    TDrawBuffer b;

    if( (state & sfActive) == 0 )
        {
        cFrame = 0x0101;
        cTitle = 0x0002;
        f = 0;
        }
    else
        if( (state & sfDragging) != 0 )
            {
            cFrame = 0x0505;
            cTitle = 0x0005;
            f = 0;
            }
        else
            {
            cFrame = 0x0503;
            cTitle = 0x0004;
            f = 9;
            }

    cFrame = getColor(cFrame);
    cTitle = getColor(cTitle);

    width = size.x;
    l = width - 10;

    if( ( ((TWindow *)owner)->flags & (wfClose | wfZoom) ) != 0 )
        l -= 6;
    frameLine( b, 0, f, uchar(cFrame) );
    if( ((TWindow *)owner)->number != wnNoNumber &&
        ((TWindow *)owner)->number < 10
      )
        {
        l -= 4;
        if( ( ((TWindow *)owner)->flags & wfZoom ) != 0 )
            i = 7;
        else
            i = 3;
        b.putChar( width-i, ((TWindow *)owner)->number + '0' );
        }

    if( owner != 0 )
        {
        const char *title = ((TWindow *)owner)->getTitle(l);
        if( title != 0 )
            {
            l = min( cstrlen(title), width - 10 );
            l = max( l, 0 );
            i = (width - l) >> 1;
            b.putChar( i-1, ' ' );
            b.moveBuf( i, title, cTitle, l );
            b.putChar( i+l, ' ' );
            }
        }