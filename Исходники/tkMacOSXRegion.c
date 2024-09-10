void 
TkUnionRectWithRegion(
    XRectangle* rectangle,
    TkRegion src_region,
    TkRegion dest_region_return)
{
    RgnHandle srcRgn = (RgnHandle) src_region;
    RgnHandle destRgn = (RgnHandle) dest_region_return;

    if (tmpRgn == NULL) {
        tmpRgn = NewRgn();
    }
    SetRectRgn(tmpRgn, rectangle->x, rectangle->y,
	    rectangle->x + rectangle->width, rectangle->y + rectangle->height);
    UnionRgn(srcRgn, tmpRgn, destRgn);
}