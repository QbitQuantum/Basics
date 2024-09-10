void SkScan::FillRect(const SkRect& r, const SkRegion* clip,
                       SkBlitter* blitter) {
    SkIRect ir;

    r.round(&ir);
    SkScan::FillIRect(ir, clip, blitter);
}