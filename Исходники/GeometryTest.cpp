static void test_conic_tangents(skiatest::Reporter* reporter) {
    SkPoint pts[] = {
        { 10, 20}, {10, 20}, {20, 30},
        { 10, 20}, {15, 25}, {20, 30},
        { 10, 20}, {20, 30}, {20, 30}
    };
    int count = (int) SK_ARRAY_COUNT(pts) / 3;
    for (int index = 0; index < count; ++index) {
        SkConic conic(&pts[index * 3], 0.707f);
        SkVector start = conic.evalTangentAt(0);
        SkVector mid = conic.evalTangentAt(.5f);
        SkVector end = conic.evalTangentAt(1);
        REPORTER_ASSERT(reporter, start.fX && start.fY);
        REPORTER_ASSERT(reporter, mid.fX && mid.fY);
        REPORTER_ASSERT(reporter, end.fX && end.fY);
        REPORTER_ASSERT(reporter, SkScalarNearlyZero(start.cross(mid)));
        REPORTER_ASSERT(reporter, SkScalarNearlyZero(mid.cross(end)));
    }
}