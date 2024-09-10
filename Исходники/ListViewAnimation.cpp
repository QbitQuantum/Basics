    SkBitmap createRandomCharIcon() {
        int size = cardHeight - (dp(10) * 2);
        SkBitmap bitmap = TestUtils::createSkBitmap(size, size);
        SkCanvas canvas(bitmap);
        canvas.clear(0);

        SkPaint paint;
        paint.setAntiAlias(true);
        SkColor randomColor = BrightColors[rand() % BrightColorsCount];
        paint.setColor(randomColor);
        canvas.drawCircle(size / 2, size / 2, size / 2, paint);

        bool bgDark = SkColorGetR(randomColor) + SkColorGetG(randomColor) + SkColorGetB(randomColor)
                < 128 * 3;
        paint.setColor(bgDark ? Color::White : Color::Grey_700);
        paint.setTextAlign(SkPaint::kCenter_Align);
        paint.setTextSize(size / 2);
        char charToShow = 'A' + (rand() % 26);
        canvas.drawText(&charToShow, 1, size / 2, /*approximate centering*/ size * 0.7, paint);
        return bitmap;
    }