void SkOverdrawCanvas::onDrawText(const void* text, size_t byteLength, SkScalar x, SkScalar y,
                                  const SkPaint& paint) {
    ProcessOneGlyphBounds processBounds(this);
    SkSurfaceProps props(0, kUnknown_SkPixelGeometry);
    this->getProps(&props);
    auto cache = SkStrikeCache::FindOrCreateStrikeExclusive(
            paint, &props, SkScalerContextFlags::kNone, &this->getTotalMatrix());
    SkFindAndPlaceGlyph::ProcessText(paint.getTextEncoding(), (const char*) text, byteLength,
                                     SkPoint::Make(x, y), SkMatrix(), paint.getTextAlign(),
                                     cache.get(), processBounds);
}