static void test4(SkCanvas* canvas) {
    SkPaint paint;
    paint.setAntiAlias(true);
    SkPoint pts[] = {
        {10, 160}, {610, 160},
        {610, 160}, {10, 160},

        {610, 160}, {610, 160},
        {610, 199}, {610, 199},

        {10, 198}, {610, 198},
        {610, 199}, {10, 199},

        {10, 160}, {10, 160},
        {10, 199}, {10, 199}
    };
    char verbs[] = {
        0, 1, 1, 1, 4,
        0, 1, 1, 1, 4,
        0, 1, 1, 1, 4,
        0, 1, 1, 1, 4
    };
    SkPath path;
    SkPoint* ptPtr = pts;
    for (size_t i = 0; i < sizeof(verbs); ++i) {
        switch ((SkPath::Verb) verbs[i]) {
            case SkPath::kMove_Verb:
                path.moveTo(ptPtr->fX, ptPtr->fY);
                ++ptPtr;
                break;
            case SkPath::kLine_Verb:
                path.lineTo(ptPtr->fX, ptPtr->fY);
                ++ptPtr;
                break;
            case SkPath::kClose_Verb:
                path.close();
                break;
            default:
                SkASSERT(false);
                break;
        }
    }
    SkRect clip = {0, 130, 772, 531};
    canvas->clipRect(clip);
    canvas->drawPath(path, paint);
}