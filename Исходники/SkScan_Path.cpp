void SkScan::FillPath(const SkPath& path, const SkIRect& ir,
                      SkBlitter* blitter) {
    SkRegion rgn(ir);
    FillPath(path, rgn, blitter);
}