static void apply_paint_textalign(const SkPaint& paint, Json::Value* target) {
    SkPaint::Align textAlign = paint.getTextAlign();
    if (textAlign != SkPaint::kLeft_Align) {
        switch (textAlign) {
            case SkPaint::kCenter_Align: {
                (*target)[SKJSONCANVAS_ATTRIBUTE_TEXTALIGN] = SKJSONCANVAS_ALIGN_CENTER;
                break;
            }
            case SkPaint::kRight_Align: {
                (*target)[SKJSONCANVAS_ATTRIBUTE_TEXTALIGN] = SKJSONCANVAS_ALIGN_RIGHT;
                break;
            }
            default: SkASSERT(false);
        }
    }
}