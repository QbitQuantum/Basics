SkRect Text::onRevalidate(InvalidationController*, const SkMatrix&) {
    // TODO: we could potentially track invals which don't require rebuilding the blob.

    SkPaint font;
    font.setFlags(fFlags);
    font.setTypeface(fTypeface);
    font.setTextSize(fSize);
    font.setTextScaleX(fScaleX);
    font.setTextSkewX(fSkewX);
    font.setTextAlign(fAlign);
    font.setHinting(fHinting);

    // First, convert to glyphIDs.
    font.setTextEncoding(SkPaint::kUTF8_TextEncoding);
    SkSTArray<256, SkGlyphID, true> glyphs;
    glyphs.reset(font.textToGlyphs(fText.c_str(), fText.size(), nullptr));
    SkAssertResult(font.textToGlyphs(fText.c_str(), fText.size(), glyphs.begin()) == glyphs.count());
    font.setTextEncoding(SkPaint::kGlyphID_TextEncoding);

    // Next, build the cached blob.
    SkTextBlobBuilder builder;
    const auto& buf = builder.allocRun(font, glyphs.count(), 0, 0, nullptr);
    if (!buf.glyphs) {
        fBlob.reset();
        return SkRect::MakeEmpty();
    }

    memcpy(buf.glyphs, glyphs.begin(), glyphs.count() * sizeof(SkGlyphID));

    fBlob = builder.make();
    return fBlob
        ? fBlob->bounds().makeOffset(fPosition.x(), fPosition.y())
        : SkRect::MakeEmpty();
}