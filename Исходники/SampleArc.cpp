    static void draw_label(SkCanvas* canvas, const SkRect& rect,
                            int start, int sweep) {
        SkPaint paint;

        paint.setAntiAlias(true);
        paint.setTextAlign(SkPaint::kCenter_Align);

        SkString    str;

        str.appendS32(start);
        str.append(", ");
        str.appendS32(sweep);
        canvas->drawText(str.c_str(), str.size(), rect.centerX(),
                         rect.fBottom + paint.getTextSize() * 5/4, paint);
    }