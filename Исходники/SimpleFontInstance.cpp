void SimpleFontInstance::getGlyphAdvance(LEGlyphID glyph, LEPoint &advance) const
{
#if 0
    if (u_getCombiningClass((UChar32) glyph) == 0) {
        advance.fX = xUnitsToPoints(2048);
    } else {
        advance.fX = 0;
    }
#else
    (void)glyph;  // Suppress unused parameter compiler warning.
    advance.fX = xUnitsToPoints(2048);
#endif

    advance.fY = 0;
}