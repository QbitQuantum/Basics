void draw(SkCanvas* canvas) {
    SkRegion region;
    SkRegion::Iterator iter(region);
    auto r1 = iter.rect();
    SkDebugf("rect={%d,%d,%d,%d}\n", r1.fLeft, r1.fTop, r1.fRight, r1.fBottom);
    region.setRect({1, 2, 3, 4});
    iter.rewind();
    auto r2 = iter.rect();
    SkDebugf("rect={%d,%d,%d,%d}\n", r2.fLeft, r2.fTop, r2.fRight, r2.fBottom);
}