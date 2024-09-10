// asserts if halfway case is not handled
static void test_halfway() {
    SkPaint paint;
    SkPath path;
    path.moveTo(16365.5f, 1394);
    path.lineTo(16365.5f, 1387.5f);
    path.quadTo(16365.5f, 1385.43f, 16367, 1383.96f);
    path.quadTo(16368.4f, 1382.5f, 16370.5f, 1382.5f);
    path.lineTo(16465.5f, 1382.5f);
    path.quadTo(16467.6f, 1382.5f, 16469, 1383.96f);
    path.quadTo(16470.5f, 1385.43f, 16470.5f, 1387.5f);
    path.lineTo(16470.5f, 1394);
    path.quadTo(16470.5f, 1396.07f, 16469, 1397.54f);
    path.quadTo(16467.6f, 1399, 16465.5f, 1399);
    path.lineTo(16370.5f, 1399);
    path.quadTo(16368.4f, 1399, 16367, 1397.54f);
    path.quadTo(16365.5f, 1396.07f, 16365.5f, 1394);
    path.close();
    SkPath p2;
    SkMatrix m;
    m.reset();
    m.postTranslate(0.001f, 0.001f);
    path.transform(m, &p2);

    auto surface(SkSurface::MakeRasterN32Premul(640, 480));
    SkCanvas* canvas = surface->getCanvas();
    canvas->translate(-16366, -1383);
    canvas->drawPath(p2, paint);

    m.reset();
    m.postTranslate(-0.001f, -0.001f);
    path.transform(m, &p2);
    canvas->drawPath(p2, paint);

    m.reset();
    path.transform(m, &p2);
    canvas->drawPath(p2, paint);
}