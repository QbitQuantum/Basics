static void test_regressions() {
    // these should not assert in the debug build
    // bug was introduced in rev. 3209
    {
        SkAAClip clip;
        SkRect r;
        r.fLeft = 129.892181f;
        r.fTop = 10.3999996f;
        r.fRight = 130.892181f;
        r.fBottom = 20.3999996f;
        clip.setRect(r, true);
    }
}