static void test_empty_crbug_458524(skiatest::Reporter* reporter) {
    SkRRect rr;
    const SkRect bounds = { 3709, 3709, 3709 + 7402, 3709 + 29825 };
    const SkScalar rad = 40;
    rr.setRectXY(bounds, rad, rad);
    path_contains_rrect_check(reporter, rr);

    SkRRect other;
    SkMatrix matrix;
    matrix.setScale(0, 1);
    rr.transform(matrix, &other);
    path_contains_rrect_check(reporter, rr);
}