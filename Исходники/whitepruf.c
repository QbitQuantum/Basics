static void arrow(float x1, float y1, float x2, float y2)
{
    float dx, dy, r, backx, backy, perpx, perpy, tipx, tipy;
    dx = x2 - x1;
    dy = y2 - y1;
    r = hypotf(dx,dy);
    if ( r < .5)  r = .5;

    backx = -.15 * dx / r;
    backy = -.15 * dy / r;
    perpx =  .05 * dy / r;
    perpy = -.05 * dx / r;
    vp_umove( x1, y1 );         
    vp_udraw( x2, y2 );

    tipx = x2 + backx + perpx;
    tipy = y2 + backy + perpy;
    vp_umove( x2, y2 );         
    vp_udraw( tipx, tipy);

    tipx = x2 + backx - perpx;
    tipy = y2 + backy - perpy;
    vp_umove( x2, y2 );         
    vp_udraw( tipx, tipy);
}