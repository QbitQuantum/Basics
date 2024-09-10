void TLabel::draw()
{
    ushort color;
    TDrawBuffer b;
    uchar scOff;

    if( light )
        {
        color = getColor(0x0402);
        scOff = 0;
        }
    else
        {
        color = getColor(0x0301);
        scOff = 4;
        }

    b.moveChar( 0, ' ', color, size.x );
    if( text != 0 )
        b.moveCStr( 1, text, color );
    if( showMarkers )
        b.putChar( 0, specialChars[scOff] );
    writeLine( 0, 0, size.x, 1, b );
}