float SVGTextLayoutEngineBaseline::calculateGlyphOrientationAngle(bool isVerticalText, const SVGRenderStyle& style, const UChar& character) const
{
    switch (isVerticalText ? style.glyphOrientationVertical() : style.glyphOrientationHorizontal()) {
    case GO_AUTO:
        // Spec: Fullwidth ideographic and fullwidth Latin text will be set with a glyph-orientation of 0-degrees.
        // Text which is not fullwidth will be set with a glyph-orientation of 90-degrees.
        // FIXME: There's not an accurate way to tell if text is fullwidth by looking at a single character.
        switch (static_cast<UEastAsianWidth>(u_getIntPropertyValue(character, UCHAR_EAST_ASIAN_WIDTH))) {
        case U_EA_NEUTRAL:
        case U_EA_HALFWIDTH:
        case U_EA_NARROW:
            return 90;
        case U_EA_AMBIGUOUS:
        case U_EA_FULLWIDTH:
        case U_EA_WIDE:
            return 0;
        case U_EA_COUNT:
            ASSERT_NOT_REACHED();
            break;
        }
        ASSERT_NOT_REACHED();
        break;
    case GO_90DEG:
        return 90;
    case GO_180DEG:
        return 180;
    case GO_270DEG:
        return 270;
    case GO_0DEG:
        return 0;
    }
    ASSERT_NOT_REACHED();
    return 0;
}