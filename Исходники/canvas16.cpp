void MWcanvas16::fill(const Color* c)
{
    if (c->rep()->stipple)
    {
        // ---- stipple some color into the area ----
        stencilFill(c->rep()->stipple, c);
    }
    else
    {
        PathRenderInfo* p = &MWcanvas16::path_;
        int n = (int) (p->cur_point_ - p->point_);
        if (n <= 2)
        {
            return;
        }

        flush();
        color(c);
        HPEN hpen = (HPEN)SelectObject(drawable_, CreatePen(PS_SOLID, 0, lg_color_->rep()->msColor()));

        POINT* pt = p->point_;
        if (xrect(pt, n))
        {
            // ---- draw a rectangle ----
            int x = Math::min(pt[0].x, pt[2].x);
            int y = Math::min(pt[0].y, pt[2].y);
            int x1 = Math::max(pt[0].x, pt[2].x);
            int y1 = Math::max(pt[0].y, pt[2].y);
            Rectangle(drawable_, x, y, x1, y1);
        }
        else
        {
            Polygon(drawable_, pt, n);
        }
        DeleteObject(SelectObject(drawable_, hpen));
    }

#ifdef DEBUG
    // ---- canvas debug ----
    MWassert( LPtoDP(drawable_, pt, n) );
    printf("fill ");
    for (int i = 0; i < n; i++)
    {
        BOOL vis = PtVisible(drawable_,  pt[i].x, pt[i].y);
        if (vis)
            printf("[%d,%d] ", pt[i].x, pt[i].y);
        else
            printf("(%d,%d> ", pt[i].x, pt[i].y);
    }
    printf("\n");
#endif
}