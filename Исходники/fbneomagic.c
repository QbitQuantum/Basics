static int HWAccelBlit (GAL_Surface *src, GAL_Rect *srcrect,
                       GAL_Surface *dst, GAL_Rect *dstrect)
{
    RECT rc_src = {srcrect->x, srcrect->y, srcrect->x + srcrect->w, srcrect->y + srcrect->h};
    RECT rc_dst = {dstrect->x, dstrect->y, dstrect->x + dstrect->w, dstrect->y + dstrect->h};
    RECT rc_inter, rc_sub [4];
    
    if (rc_src.top < rc_dst.top && IntersectRect (&rc_inter, &rc_src, &rc_dst)) {
        int i, sub_count, inter_h;
        Sint32 off_x = dstrect->x - srcrect->x;
        Sint32 off_y = dstrect->y - srcrect->y;
        GAL_Rect tmp_src, tmp_dst;

        inter_h = rc_inter.bottom - rc_inter.top;
        for (i = 0; i < inter_h; i++) {
            rc_inter.top = rc_inter.bottom - 1;
            make_rects (&tmp_src, &tmp_dst, &rc_inter, off_x, off_y);
            HWAccelBlit_helper (src, &tmp_src, dst, &tmp_dst);
            rc_inter.bottom --;
        }

        sub_count = SubtractRect (rc_sub, &rc_src, &rc_dst);
        for (i = 0; i < sub_count; i++) {
            make_rects (&tmp_src, &tmp_dst, rc_sub + i, off_x, off_y);
            HWAccelBlit_helper (src, &tmp_src, dst, &tmp_dst);
        }
    }
    else if (rc_src.top == rc_dst.top && rc_src.left < rc_dst.left) {
        int i;
        GAL_Rect tmp_src, tmp_dst;
        Sint32 off_x = dstrect->x - srcrect->x;
        RECT rc = rc_src;

        for (i = 0; i < rc_src.right - rc_src.left; i++) {
            rc.left = rc.right - 1;
            make_rects (&tmp_src, &tmp_dst, &rc, off_x, 0);
            HWAccelBlit_helper (src, &tmp_src, dst, &tmp_dst);
            rc.right --;
        }
    }
    else
        HWAccelBlit_helper (src, srcrect, dst, dstrect);

	return(0);
}