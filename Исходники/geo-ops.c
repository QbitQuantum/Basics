double point_dt(Point *pt1, Point *pt2)
{
    return( HYPOT( pt1->x - pt2->x, pt1->y - pt2->y ) );
}