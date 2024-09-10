void AnimatedImage::flushPr(CDC &dc, const CPoint &p, PixRect *src, double scaleFactor) const {
  if(scaleFactor == 1.0) {
    PixRect::bitBlt(dc, p, src->getSize(), SRCCOPY, src, ORIGIN);
  } else {
    const CSize sz = src->getSize();
    const CSize dstSize(scaleFactor*sz.cx, scaleFactor*sz.cy);
    dc.SetStretchBltMode(COLORONCOLOR /*HALFTONE*/);
    PixRect::stretchBlt(dc, p,dstSize, SRCCOPY, src, ORIGIN, sz);
  }
}