static bool sectsrgn_proc(SkRegion& a, SkRegion& b) {
    return a.intersects(b);
}