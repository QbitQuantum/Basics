// Used in Win95/98/NT.  Win2000 uses the TransparentBlt function.
//  -  Win98 also has this function but it seems to leak GDI resources
//     whenever I use it
static void myTransparentBlt(CDC *dst, int x, int y, int w, int h,
                             CDC *src, int srcx, int srcy, CBitmap *mskBmp)
{
    if (NULL == transparentblt) {
        CDC mskDC;
        CBitmap *oldBmp;

        mskDC.CreateCompatibleDC(dst);

        oldBmp = mskDC.SelectObject(mskBmp);

        // Mask out places where the bitmap will be placed
        // SRCAND of dst and mskBmp
        dst->BitBlt(x, y, w, h, &mskDC, srcx, srcy, SRCAND);

        // OR the bitmap to the destination
        dst->BitBlt(x, y, w, h, src, srcx, srcy, SRCPAINT);

        mskDC.SelectObject(oldBmp);
    } else {
        transparentblt(*dst, x, y, w, h,
                       *src, srcx, srcy, w, h, BG_COLOUR);
    }
}