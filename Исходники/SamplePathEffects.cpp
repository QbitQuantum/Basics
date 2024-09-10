static sk_sp<SkPathEffect> make_pe(int flags, SkScalar phase) {
    if (flags == 1) {
        return SkCornerPathEffect::Make(SkIntToScalar(CORNER_RADIUS));
    }

    SkPath  path;
    path.moveTo(SkIntToScalar(gXY[0]), SkIntToScalar(gXY[1]));
    for (unsigned i = 2; i < SK_ARRAY_COUNT(gXY); i += 2)
        path.lineTo(SkIntToScalar(gXY[i]), SkIntToScalar(gXY[i+1]));
    path.close();
    path.offset(SkIntToScalar(-6), 0);

    auto outer = SkPath1DPathEffect::Make(path, 12, phase, SkPath1DPathEffect::kRotate_Style);

    if (flags == 2)
        return outer;

    auto inner = SkCornerPathEffect::Make(SkIntToScalar(CORNER_RADIUS));

    return SkComposePathEffect::Make(outer, inner);
}