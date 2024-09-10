void SkFlipPixelRef::CopyBitsFromAddr(const SkBitmap& dst, const SkRegion& clip,
                                      const void* srcAddr) {
    const int shift = getShift(dst.config());
    if (shift < 0) {
        return;
    }
    
    const SkIRect bounds = {0, 0, dst.width(), dst.height()};
    SkRegion::Cliperator iter(clip, bounds);
    
    while (!iter.done()) {
        copyRect(dst, iter.rect(), srcAddr, shift);
        iter.next();
    }
}