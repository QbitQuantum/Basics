int CFX_FloatRect::Substract4(CFX_FloatRect& s, CFX_FloatRect* pRects) {
    Normalize();
    s.Normalize();
    int nRects = 0;
    CFX_FloatRect rects[4];
    if (left < s.left) {
        rects[nRects].left = left;
        rects[nRects].right = s.left;
        rects[nRects].bottom = bottom;
        rects[nRects].top = top;
        nRects++;
    }
    if (s.left < right && s.top < top) {
        rects[nRects].left = s.left;
        rects[nRects].right = right;
        rects[nRects].bottom = s.top;
        rects[nRects].top = top;
        nRects++;
    }
    if (s.top > bottom && s.right < right) {
        rects[nRects].left = s.right;
        rects[nRects].right = right;
        rects[nRects].bottom = bottom;
        rects[nRects].top = s.top;
        nRects++;
    }
    if (s.bottom > bottom) {
        rects[nRects].left = s.left;
        rects[nRects].right = s.right;
        rects[nRects].bottom = bottom;
        rects[nRects].top = s.bottom;
        nRects++;
    }
    if (nRects == 0) {
        return 0;
    }
    for (int i = 0; i < nRects; i++) {
        pRects[i] = rects[i];
        pRects[i].Intersect(*this);
    }
    return nRects;
}