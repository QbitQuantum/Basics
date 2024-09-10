static void dw_gt_curveto(vd_trace_interface *I, double x0, double y0, double x1, double y1, double x2, double y2)
{   POINT p[3];
    get_window(); 
    if (host.tw == NULL) 
        return;
    p[0].x = SX(x0), p[0].y = SY(y0);
    p[1].x = SX(x1), p[1].y = SY(y1);
    p[2].x = SX(x2), p[2].y = SY(y2);
    PolyBezierTo(I->host->hdc, p, 3);
}