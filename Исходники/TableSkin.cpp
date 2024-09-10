void TableSkin::TableDice( const Rect &bound, int x1, int x2, int x3, int y1, int y2, int y3, bool no_interrior)
{
    AssocVector<int ,Rect> assoc_rects;

    Pos p0;// = bound.GetPos();

    int x[5] = { 0, x1, x2, x3, bound.GetW() };
    int y[5] = { 0, y1, y2, y3, bound.GetH() };

    assoc_rects.Insert( TOP+HEAD, CheckedRect( x[0], y[0], x[1]-x[0], y[1]-y[0]) +p0);
    assoc_rects.Insert( TOP+BODY, CheckedRect( x[1], y[0], x[2]-x[1], y[1]-y[0]) +p0);
    assoc_rects.Insert( TOP+TAIL, CheckedRect( x[3], y[0], x[4]-x[3], y[1]-y[0]) +p0);

    assoc_rects.Insert( MIDDLE+HEAD, CheckedRect( x[0], y[1], x[1]-x[0], y[2]-y[1]) +p0);

    if ( !no_interrior )
    assoc_rects.Insert( MIDDLE+BODY, CheckedRect( x[1], y[1], x[2]-x[1], y[2]-y[1]) +p0);

    assoc_rects.Insert( MIDDLE+TAIL, CheckedRect( x[3], y[1], x[4]-x[3], y[2]-y[1]) +p0);

    assoc_rects.Insert( BOTTOM+HEAD, CheckedRect(x[0], y[3], x[1]-x[0], y[4]-y[3]) +p0);
    assoc_rects.Insert( BOTTOM+BODY, CheckedRect(x[1], y[3], x[2]-x[1], y[4]-y[3]) +p0);
    assoc_rects.Insert( BOTTOM+TAIL, CheckedRect(x[3], y[3], x[4]-x[3], y[4]-y[3]) +p0);

    assoc_rects.Insert( HEAD+HDIV , CheckedRect( x[0], y[2], x[1]-x[0], y[3]-y[2]) +p0);
    assoc_rects.Insert( BODY+HDIV , CheckedRect( x[1], y[2], x[2]-x[1], y[3]-y[2]) +p0);
    assoc_rects.Insert( TAIL+HDIV , CheckedRect( x[3], y[2], x[4]-x[3], y[3]-y[2]) +p0);

    assoc_rects.Insert( HEAD+VDIV , CheckedRect( x[2], y[0], x[3]-x[2], y[1]-y[0]) +p0);
    assoc_rects.Insert( BODY+VDIV , CheckedRect( x[2], y[1], x[3]-x[2], y[2]-y[1]) +p0);
    assoc_rects.Insert( TAIL+VDIV , CheckedRect( x[2], y[3], x[3]-x[2], y[4]-y[3]) +p0);

    assoc_rects.Insert( CROSSING  , CheckedRect( x[2], y[2], x[3]-x[2], y[3]-y[2]) +p0);

    ImageDicer::Dice(assoc_rects);
    SetSize( Dim2i(bound.GetW(), bound.GetH()) );
}