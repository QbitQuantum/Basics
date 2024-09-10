static void draw_rect(SkCanvas* canvas, const SkRect& r, SkColor c, SkColorProfileType profile,
                      const SkAlpha aa[]) {
    const SkIRect ir = r.round();

    SkBitmap bm;
    bm.allocN32Pixels(ir.width(), ir.height());
    bm.eraseColor(0xFFFFFFFF);
    SkPixmap pm;
    bm.peekPixels(&pm);

    uint32_t flags = 0;
    if (SkColorGetA(c) == 0xFF) {
        flags |= SkXfermode::kSrcIsOpaque_PM4fFlag;
    }
    if (kSRGB_SkColorProfileType == profile) {
        flags |= SkXfermode::kDstIsSRGB_PM4fFlag;
    }

    const SkXfermode::PM4fState state { nullptr, flags };

    const SkPM4f src = SkColor4f::FromColor(c).premul();
    auto proc1 = SkXfermode::GetPM4fProc1(SkXfermode::kSrcOver_Mode, flags);
    for (int y = 0; y < ir.height()/2; ++y) {
        proc1(state, pm.writable_addr32(0, y), src, ir.width(), aa);
    }

    SkPM4f srcRow[1000];
    for (int i = 0; i < ir.width(); ++i) {
        srcRow[i] = src;
    }
    auto procN = SkXfermode::GetPM4fProcN(SkXfermode::kSrcOver_Mode, flags);
    // +1 to skip a row, so we can see the boundary between proc1 and procN
    for (int y = ir.height()/2 + 1; y < ir.height(); ++y) {
        procN(state, pm.writable_addr32(0, y), srcRow, ir.width(), aa);
    }

    canvas->drawBitmap(bm, r.left(), r.top(), nullptr);
}