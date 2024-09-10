DEF_TEST(Matrix44, reporter) {
    SkMatrix44 mat(SkMatrix44::kUninitialized_Constructor);
    SkMatrix44 inverse(SkMatrix44::kUninitialized_Constructor);
    SkMatrix44 iden1(SkMatrix44::kUninitialized_Constructor);
    SkMatrix44 iden2(SkMatrix44::kUninitialized_Constructor);
    SkMatrix44 rot(SkMatrix44::kUninitialized_Constructor);

    mat.setTranslate(1, 1, 1);
    mat.invert(&inverse);
    iden1.setConcat(mat, inverse);
    REPORTER_ASSERT(reporter, is_identity(iden1));

    mat.setScale(2, 2, 2);
    mat.invert(&inverse);
    iden1.setConcat(mat, inverse);
    REPORTER_ASSERT(reporter, is_identity(iden1));

    mat.setScale(SK_MScalar1/2, SK_MScalar1/2, SK_MScalar1/2);
    mat.invert(&inverse);
    iden1.setConcat(mat, inverse);
    REPORTER_ASSERT(reporter, is_identity(iden1));

    mat.setScale(3, 3, 3);
    rot.setRotateDegreesAbout(0, 0, -1, 90);
    mat.postConcat(rot);
    REPORTER_ASSERT(reporter, mat.invert(NULL));
    mat.invert(&inverse);
    iden1.setConcat(mat, inverse);
    REPORTER_ASSERT(reporter, is_identity(iden1));
    iden2.setConcat(inverse, mat);
    REPORTER_ASSERT(reporter, is_identity(iden2));

    // test tiny-valued matrix inverse
    mat.reset();
    mat.setScale(1.0e-12, 1.0e-12, 1.0e-12);
    rot.setRotateDegreesAbout(0, 0, -1, 90);
    mat.postConcat(rot);
    mat.postTranslate(1.0e-12, 1.0e-12, 1.0e-12);
    REPORTER_ASSERT(reporter, mat.invert(NULL));
    mat.invert(&inverse);
    iden1.setConcat(mat, inverse);
    REPORTER_ASSERT(reporter, is_identity(iden1));

    // test mixed-valued matrix inverse
    mat.reset();
    mat.setScale(1.0e-10, 3.0, 1.0e+10);
    rot.setRotateDegreesAbout(0, 0, -1, 90);
    mat.postConcat(rot);
    mat.postTranslate(1.0e+10, 3.0, 1.0e-10);
    REPORTER_ASSERT(reporter, mat.invert(NULL));
    mat.invert(&inverse);
    iden1.setConcat(mat, inverse);
    REPORTER_ASSERT(reporter, is_identity(iden1));

    // test degenerate matrix
    mat.reset();
    mat.set3x3(1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    REPORTER_ASSERT(reporter, !mat.invert(NULL));

    // test rol/col Major getters
    {
        mat.setTranslate(2, 3, 4);
        float dataf[16];
        double datad[16];

        mat.asColMajorf(dataf);
        assert16<float>(reporter, dataf,
                 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 2, 3, 4, 1);
        mat.asColMajord(datad);
        assert16<double>(reporter, datad, 1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        2, 3, 4, 1);
        mat.asRowMajorf(dataf);
        assert16<float>(reporter, dataf, 1, 0, 0, 2,
                        0, 1, 0, 3,
                        0, 0, 1, 4,
                        0, 0, 0, 1);
        mat.asRowMajord(datad);
        assert16<double>(reporter, datad, 1, 0, 0, 2,
                        0, 1, 0, 3,
                        0, 0, 1, 4,
                        0, 0, 0, 1);
    }

    test_concat(reporter);

    if (false) { // avoid bit rot, suppress warning (working on making this pass)
        test_common_angles(reporter);
    }

    test_constructor(reporter);
    test_gettype(reporter);
    test_determinant(reporter);
    test_invert(reporter);
    test_transpose(reporter);
    test_get_set_double(reporter);
    test_set_row_col_major(reporter);
    test_translate(reporter);
    test_scale(reporter);
    test_map2(reporter);
    test_3x3_conversion(reporter);
    test_has_perspective(reporter);
    test_preserves_2d_axis_alignment(reporter);
}