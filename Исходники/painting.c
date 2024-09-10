BOOL nulldrv_PolyBezierTo( PHYSDEV dev, const POINT *points, DWORD count )
{
    DC *dc = get_nulldrv_dc( dev );
    BOOL ret = FALSE;
    POINT *pts = HeapAlloc( GetProcessHeap(), 0, sizeof(POINT) * (count + 1) );

    if (pts)
    {
        pts[0] = dc->cur_pos;
        memcpy( pts + 1, points, sizeof(POINT) * count );
        ret = PolyBezier( dev->hdc, pts, count + 1 );
        HeapFree( GetProcessHeap(), 0, pts );
    }
    return ret;
}