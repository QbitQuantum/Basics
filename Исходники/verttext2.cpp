    void drawText(SkCanvas* canvas, const SkString& string,
                  SkTypeface* family, SkPaint::Align alignment) {
        SkPaint paint;
        paint.setColor(SK_ColorBLACK);
        paint.setAntiAlias(true);
        paint.setVerticalText(true);
        paint.setTextAlign(alignment);
        paint.setTypeface(family);
        paint.setTextSize(textHeight);

        canvas->drawText(string.c_str(), string.size(), y, 
                alignment == SkPaint::kLeft_Align ? 10 : 240, paint);
        y += textHeight;
    }