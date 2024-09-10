    void drawRect(const SkRect& r, SkColor c) override {
        HDC hdc = (HDC)fCanvas->accessTopRasterHandle();

        COLORREF cr = RGB(SkColorGetR(c), SkColorGetG(c), SkColorGetB(c));// SkEndian_Swap32(c) >> 8;
        FillRect(hdc, &toRECT(r.round()), CreateSolidBrush(cr));

        // Assuming GDI wrote zeros for alpha, this will or-in 0xFF for alpha
        SkPaint paint;
        paint.setBlendMode(SkBlendMode::kDstATop);
        fCanvas->drawRect(r, paint);
    }