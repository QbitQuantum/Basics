float SimpleFontData::platformWidthForGlyph(Glyph glyph) const
{
    if (!m_platformData.size())
        return 0;

    HWndDC dc(0);
    HGDIOBJ oldFont = SelectObject(dc, m_platformData.hfont());

    int width = 0;
    if (!GetCharWidthI(dc, glyph, 1, 0, &width)) {
        // Ask the browser to preload the font and retry.
        if (FontPlatformData::ensureFontLoaded(m_platformData.hfont())) {
            // FIXME: Handle gracefully the error if this call also fails.
            // See http://crbug.com/6401.
            if (!GetCharWidthI(dc, glyph, 1, 0, &width))
                LOG_ERROR("Unable to get the char width after second attempt");
        }
    }

    SelectObject(dc, oldFont);

    return static_cast<float>(width);
}