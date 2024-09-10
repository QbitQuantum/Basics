static void fuzz_drawPath(Fuzz* fuzz) {
    SkPaint p;
    init_paint(fuzz, &p);
    sk_sp<SkSurface> surface;
    init_surface(fuzz, &surface);

    // TODO(kjlubick): put the ability to fuzz a path in shared file, with
    // other common things (e.g. rects, lines)
    uint8_t i, j;
    fuzz->nextRange(&i, 0, 10); // set i to number of operations to perform
    SkPath path;
    SkScalar a, b, c, d, e, f;
    for (int k = 0; k < i; ++k) {
        fuzz->nextRange(&j, 0, 5); // set j to choose operation to perform
        switch (j) {
            case 0:
                fuzz->next(&a, &b);
                path.moveTo(a, b);
                break;
            case 1:
                fuzz->next(&a, &b);
                path.lineTo(a, b);
                break;
            case 2:
                fuzz->next(&a, &b, &c, &d);
                path.quadTo(a, b, c, d);
                break;
            case 3:
                fuzz->next(&a, &b, &c, &d, &e);
                path.conicTo(a, b, c, d, e);
                break;
            case 4:
                fuzz->next(&a, &b, &c, &d, &e, &f);
                path.cubicTo(a, b, c, d, e, f);
                break;
            case 5:
                fuzz->next(&a, &b, &c, &d, &e);
                path.arcTo(a, b, c, d, e);
                break;
        }
    }
    path.close();

    SkCanvas* cnv = surface->getCanvas();
    cnv->drawPath(path, p);

    bool bl;
    fuzz->next(&bl);
    cnv->clipPath(path, kIntersect_SkClipOp, bl);
}