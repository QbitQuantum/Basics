    void draw_stroke(SkCanvas* canvas, const SkPath& path, SkScalar width, SkScalar scale,
            bool drawText) {
        if (path.isEmpty()) {
            return;
        }
        SkRect bounds = path.getBounds();
        this->setWHZ(SkScalarCeilToInt(bounds.right()), drawText 
                ? SkScalarRoundToInt(scale * 3 / 2) : SkScalarRoundToInt(scale),
                SkScalarRoundToInt(950.0f / scale));
        erase(fMinSurface);
        SkPaint paint;
        paint.setColor(0x1f1f0f0f);
        paint.setStyle(SkPaint::kStroke_Style);
        paint.setStrokeWidth(width * scale * scale);
        paint.setColor(0x3f0f1f3f);
        if (drawText) {
            fMinSurface->getCanvas()->drawPath(path, paint);
            this->copyMinToMax();
            fMaxSurface->draw(canvas, 0, 0, NULL);
        }
        paint.setAntiAlias(true);
        paint.setStyle(SkPaint::kStroke_Style);
        paint.setStrokeWidth(1);

        paint.setColor(SKELETON_COLOR);
        SkPath scaled;
        SkMatrix matrix;
        matrix.reset();
        matrix.setScale(950 / scale, 950 / scale);
        if (drawText) {
            path.transform(matrix, &scaled);
        } else {
            scaled = path;
        }
        canvas->drawPath(scaled, paint);
        draw_points(canvas, scaled, SKELETON_COLOR, true);

        if (fDrawRibs) {
            draw_ribs(canvas, scaled, width, 0xFF00FF00);
        }

        SkPath fill;

        SkPaint p;
        p.setStyle(SkPaint::kStroke_Style);
        if (drawText) {
            p.setStrokeWidth(width * scale * scale);
        } else {
            p.setStrokeWidth(width);
        }
        p.getFillPath(path, &fill);
        SkPath scaledFill;
        if (drawText) {
            fill.transform(matrix, &scaledFill);
        } else {
            scaledFill = fill;
        }
        paint.setColor(WIREFRAME_COLOR);
        canvas->drawPath(scaledFill, paint);
        draw_points(canvas, scaledFill, WIREFRAME_COLOR, false);
    }