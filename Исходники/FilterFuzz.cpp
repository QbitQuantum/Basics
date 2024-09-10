static SkPath make_path() {
    SkPath path;
    uint8_t numOps;
    fuzz->nextRange(&numOps, 0, 30);
    for (uint8_t i = 0; i < numOps; ++i) {
        uint8_t op;
        fuzz->nextRange(&op, 0, 5);
        SkScalar a, b, c, d, e, f;
        switch (op) {
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
            default:
                fuzz->next(&a, &b, &c, &d, &e);
                path.arcTo(a, b, c, d, e);
                break;
        }
    }
    path.close();
    return path;
}