// Called to test various transforms on a single SkRRect.
static void test_transform_helper(skiatest::Reporter* reporter, const SkRRect& orig) {
    SkRRect dst;
    dst.setEmpty();

    // The identity matrix will duplicate the rrect.
    bool success = orig.transform(SkMatrix::I(), &dst);
    REPORTER_ASSERT(reporter, success);
    REPORTER_ASSERT(reporter, orig == dst);

    // Skew and Perspective make transform fail.
    SkMatrix matrix;
    matrix.reset();
    matrix.setSkewX(SkIntToScalar(2));
    assert_transform_failure(reporter, orig, matrix);

    matrix.reset();
    matrix.setSkewY(SkIntToScalar(3));
    assert_transform_failure(reporter, orig, matrix);

    matrix.reset();
    matrix.setPerspX(4);
    assert_transform_failure(reporter, orig, matrix);

    matrix.reset();
    matrix.setPerspY(5);
    assert_transform_failure(reporter, orig, matrix);

    // Rotation fails.
    matrix.reset();
    matrix.setRotate(SkIntToScalar(90));
    assert_transform_failure(reporter, orig, matrix);
    matrix.setRotate(SkIntToScalar(37));
    assert_transform_failure(reporter, orig, matrix);

    // Translate will keep the rect moved, but otherwise the same.
    matrix.reset();
    SkScalar translateX = SkIntToScalar(32);
    SkScalar translateY = SkIntToScalar(15);
    matrix.setTranslateX(translateX);
    matrix.setTranslateY(translateY);
    dst.setEmpty();
    success = orig.transform(matrix, &dst);
    REPORTER_ASSERT(reporter, success);
    for (int i = 0; i < 4; ++i) {
        REPORTER_ASSERT(reporter,
                orig.radii((SkRRect::Corner) i) == dst.radii((SkRRect::Corner) i));
    }
    REPORTER_ASSERT(reporter, orig.rect().width() == dst.rect().width());
    REPORTER_ASSERT(reporter, orig.rect().height() == dst.rect().height());
    REPORTER_ASSERT(reporter, dst.rect().left() == orig.rect().left() + translateX);
    REPORTER_ASSERT(reporter, dst.rect().top() == orig.rect().top() + translateY);

    // Keeping the translation, but adding skew will make transform fail.
    matrix.setSkewY(SkIntToScalar(7));
    assert_transform_failure(reporter, orig, matrix);

    // Scaling in -x will flip the round rect horizontally.
    matrix.reset();
    matrix.setScaleX(SkIntToScalar(-1));
    dst.setEmpty();
    success = orig.transform(matrix, &dst);
    REPORTER_ASSERT(reporter, success);
    {
        GET_RADII;
        // Radii have swapped in x.
        REPORTER_ASSERT(reporter, origUL == dstUR);
        REPORTER_ASSERT(reporter, origUR == dstUL);
        REPORTER_ASSERT(reporter, origLR == dstLL);
        REPORTER_ASSERT(reporter, origLL == dstLR);
    }
    // Width and height remain the same.
    REPORTER_ASSERT(reporter, orig.rect().width() == dst.rect().width());
    REPORTER_ASSERT(reporter, orig.rect().height() == dst.rect().height());
    // Right and left have swapped (sort of)
    REPORTER_ASSERT(reporter, orig.rect().right() == -dst.rect().left());
    // Top has stayed the same.
    REPORTER_ASSERT(reporter, orig.rect().top() == dst.rect().top());

    // Keeping the scale, but adding a persp will make transform fail.
    matrix.setPerspX(7);
    assert_transform_failure(reporter, orig, matrix);

    // Scaling in -y will flip the round rect vertically.
    matrix.reset();
    matrix.setScaleY(SkIntToScalar(-1));
    dst.setEmpty();
    success = orig.transform(matrix, &dst);
    REPORTER_ASSERT(reporter, success);
    {
        GET_RADII;
        // Radii have swapped in y.
        REPORTER_ASSERT(reporter, origUL == dstLL);
        REPORTER_ASSERT(reporter, origUR == dstLR);
        REPORTER_ASSERT(reporter, origLR == dstUR);
        REPORTER_ASSERT(reporter, origLL == dstUL);
    }
    // Width and height remain the same.
    REPORTER_ASSERT(reporter, orig.rect().width() == dst.rect().width());
    REPORTER_ASSERT(reporter, orig.rect().height() == dst.rect().height());
    // Top and bottom have swapped (sort of)
    REPORTER_ASSERT(reporter, orig.rect().top() == -dst.rect().bottom());
    // Left has stayed the same.
    REPORTER_ASSERT(reporter, orig.rect().left() == dst.rect().left());

    // Scaling in -x and -y will swap in both directions.
    matrix.reset();
    matrix.setScaleY(SkIntToScalar(-1));
    matrix.setScaleX(SkIntToScalar(-1));
    dst.setEmpty();
    success = orig.transform(matrix, &dst);
    REPORTER_ASSERT(reporter, success);
    {
        GET_RADII;
        REPORTER_ASSERT(reporter, origUL == dstLR);
        REPORTER_ASSERT(reporter, origUR == dstLL);
        REPORTER_ASSERT(reporter, origLR == dstUL);
        REPORTER_ASSERT(reporter, origLL == dstUR);
    }
    // Width and height remain the same.
    REPORTER_ASSERT(reporter, orig.rect().width() == dst.rect().width());
    REPORTER_ASSERT(reporter, orig.rect().height() == dst.rect().height());
    REPORTER_ASSERT(reporter, orig.rect().top() == -dst.rect().bottom());
    REPORTER_ASSERT(reporter, orig.rect().right() == -dst.rect().left());

    // Scale in both directions.
    SkScalar xScale = SkIntToScalar(3);
    SkScalar yScale = 3.2f;
    matrix.reset();
    matrix.setScaleX(xScale);
    matrix.setScaleY(yScale);
    dst.setEmpty();
    success = orig.transform(matrix, &dst);
    REPORTER_ASSERT(reporter, success);
    // Radii are scaled.
    for (int i = 0; i < 4; ++i) {
        REPORTER_ASSERT(reporter, SkScalarNearlyEqual(dst.radii((SkRRect::Corner) i).fX,
                                    SkScalarMul(orig.radii((SkRRect::Corner) i).fX, xScale)));
        REPORTER_ASSERT(reporter, SkScalarNearlyEqual(dst.radii((SkRRect::Corner) i).fY,
                                    SkScalarMul(orig.radii((SkRRect::Corner) i).fY, yScale)));
    }
    REPORTER_ASSERT(reporter, SkScalarNearlyEqual(dst.rect().width(),
                                                  SkScalarMul(orig.rect().width(), xScale)));
    REPORTER_ASSERT(reporter, SkScalarNearlyEqual(dst.rect().height(),
                                                  SkScalarMul(orig.rect().height(), yScale)));
    REPORTER_ASSERT(reporter, SkScalarNearlyEqual(dst.rect().left(),
                                                  SkScalarMul(orig.rect().left(), xScale)));
    REPORTER_ASSERT(reporter, SkScalarNearlyEqual(dst.rect().top(),
                                                  SkScalarMul(orig.rect().top(), yScale)));
}