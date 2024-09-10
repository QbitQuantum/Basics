Path CairoGlyphToPathTranslator::path()
{
    Path path;
    path.ensurePlatformPath();

    cairo_glyph_t cairoGlyph;
    cairoGlyph.index = m_glyphBuffer.glyphAt(m_index);
    cairo_set_scaled_font(path.platformPath()->context(), m_fontData->platformData().scaledFont());
    cairo_glyph_path(path.platformPath()->context(), &cairoGlyph, 1);

    float syntheticBoldOffset = m_fontData->syntheticBoldOffset();
    if (syntheticBoldOffset) {
        cairo_translate(path.platformPath()->context(), syntheticBoldOffset, 0);
        cairo_show_glyphs(path.platformPath()->context(), &cairoGlyph, 1);
    }

    path.transform(m_translation);
    return path;
}