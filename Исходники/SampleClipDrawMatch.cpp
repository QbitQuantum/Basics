SkPath create_concave_path(const SkPoint& offset) {
    SkPath concavePath;
    concavePath.moveTo(kMin, kMin);
    concavePath.lineTo(kMid, 105.0f);
    concavePath.lineTo(kMax, kMin);
    concavePath.lineTo(295.0f, kMid);
    concavePath.lineTo(kMax, kMax);
    concavePath.lineTo(kMid, 295.0f);
    concavePath.lineTo(kMin, kMax);
    concavePath.lineTo(105.0f, kMid);
    concavePath.close();

    concavePath.offset(offset.fX, offset.fY);
    return concavePath;
}