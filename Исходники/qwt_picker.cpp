static inline QRegion qwtMaskRegion( const QLine &l, int penWidth )
{
    const int pw = qMax( penWidth, 1 );
    const int pw2 = penWidth / 2;

    QRegion region;

    if ( l.x1() == l.x2() )
    {
        region += QRect( l.x1() - pw2, l.y1(),
            pw, l.y2() ).normalized();
    }
    else if ( l.y1() == l.y2() )
    {
        region += QRect( l.x1(), l.y1() - pw2,
            l.x2(), pw ).normalized();
    }

    return region;
}