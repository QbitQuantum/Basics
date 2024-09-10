void
frtick(Frame *f, Point pt, int ticked)
{
    Rectangle r;

    if(f->ticked==ticked || f->tick==0 || !ptinrect(pt, f->r))
        return;
    pt.x--;	/* looks best just left of where requested */
    r = Rect(pt.x, pt.y, pt.x+FRTICKW, pt.y+f->font->height);
    /* can go into left border but not right */
    if(r.max.x > f->r.max.x)
        r.max.x = f->r.max.x;
    if(ticked) {
        draw(f->tickback, f->tickback->r, f->b, nil, pt);
        draw(f->b, r, f->tick, nil, ZP);
    } else
        draw(f->b, r, f->tickback, nil, ZP);
    f->ticked = ticked;
}