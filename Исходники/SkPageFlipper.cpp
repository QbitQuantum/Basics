void SkPageFlipper::inval(const SkRect& rect, bool antialias) {
    SkIRect r;
    rect.round(&r);
    if (antialias) {
        r.inset(-1, -1);
    }
    this->inval(r);
}