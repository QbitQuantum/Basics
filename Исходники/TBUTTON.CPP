void TButton::drawState(Boolean down)
{
    ushort cButton, cShadow;
    char   ch;
    int    i;
    TDrawBuffer b;

    if( (state & sfDisabled) != 0 )
        cButton = getColor(0x0404);
    else
        {
        cButton = getColor(0x0501);
        if( (state & sfActive) != 0 )
            if( (state & sfSelected) != 0 )
                cButton = getColor(0x0703);
            else if( amDefault )
                cButton = getColor(0x0602);
        }
    cShadow = getColor(8);
    int s = size.x-1;
    int T = size.y / 2 - 1;

    for( int y = 0; y <= size.y-2; y++ )
        {
        b.moveChar( 0, ' ', cButton, size.x );
        b.putAttribute( 0, cShadow );
        if( down )
            {
            b.putAttribute( 1, cShadow );
            ch =  ' ';
            i = 2;
            }
        else
            {
            b.putAttribute( s, cShadow );
            if( showMarkers == True )
                ch = ' ';
            else
                {
                if( y == 0 )
                    b.putChar( s, shadows[0] );
                else
                    b.putChar( s, shadows[1] );
                ch = shadows[2];
                }
            i =  1;
            }

        if( y == T && title != 0 )
            drawTitle( b, s, i, cButton, down );

        if( showMarkers && !down )
            {
            b.putChar( 1, markers[0] );
            b.putChar( s-1, markers[1] );
            }
        writeLine( 0, y, size.x, 1, b );
        }
    b.moveChar( 0, ' ', cShadow, 2 );
    b.moveChar( 2, ch, cShadow, s-1 );
    writeLine( 0, size.y-1, size.x, 1, b );
}