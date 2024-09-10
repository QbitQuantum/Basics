bool UniscribeController::shapeAndPlaceItem(const UChar* cp, unsigned i, const SimpleFontData* fontData, GlyphBuffer* glyphBuffer)
{
    // Determine the string for this item.
    const UChar* str = cp + m_items[i].iCharPos;
    int len = m_items[i+1].iCharPos - m_items[i].iCharPos;
    SCRIPT_ITEM item = m_items[i];

    // Set up buffers to hold the results of shaping the item.
    Vector<WORD> glyphs;
    Vector<WORD> clusters;
    Vector<SCRIPT_VISATTR> visualAttributes;
    clusters.resize(len);
     
    // Shape the item.
    // The recommended size for the glyph buffer is 1.5 * the character length + 16 in the uniscribe docs.
    // Apparently this is a good size to avoid having to make repeated calls to ScriptShape.
    glyphs.resize(1.5 * len + 16);
    visualAttributes.resize(glyphs.size());

    if (!shape(str, len, item, fontData, glyphs, clusters, visualAttributes))
        return true;

    // We now have a collection of glyphs.
    Vector<GOFFSET> offsets;
    Vector<int> advances;
    offsets.resize(glyphs.size());
    advances.resize(glyphs.size());
    int glyphCount = 0;
    HRESULT placeResult = ScriptPlace(0, fontData->scriptCache(), glyphs.data(), glyphs.size(), visualAttributes.data(),
                                      &item.a, advances.data(), offsets.data(), 0);
    if (placeResult == E_PENDING) {
        // The script cache isn't primed with enough info yet.  We need to select our HFONT into
        // a DC and pass the DC in to ScriptPlace.
        HDC hdc = GetDC(0);
        HFONT hfont = fontData->platformData().hfont();
        HFONT oldFont = (HFONT)SelectObject(hdc, hfont);
        placeResult = ScriptPlace(hdc, fontData->scriptCache(), glyphs.data(), glyphs.size(), visualAttributes.data(),
                                  &item.a, advances.data(), offsets.data(), 0);
        SelectObject(hdc, oldFont);
        ReleaseDC(0, hdc);
    }
    
    if (FAILED(placeResult) || glyphs.isEmpty())
        return true;

    // Convert all chars that should be treated as spaces to use the space glyph.
    // We also create a map that allows us to quickly go from space glyphs or rounding
    // hack glyphs back to their corresponding characters.
    Vector<int> spaceCharacters(glyphs.size());
    spaceCharacters.fill(-1);
    Vector<int> roundingHackCharacters(glyphs.size());
    roundingHackCharacters.fill(-1);
    Vector<int> roundingHackWordBoundaries(glyphs.size());
    roundingHackWordBoundaries.fill(-1);

    const float cLogicalScale = fontData->platformData().useGDI() ? 1.0f : 32.0f;
    unsigned logicalSpaceWidth = fontData->spaceWidth() * cLogicalScale;
    float roundedSpaceWidth = roundf(fontData->spaceWidth());

    for (int k = 0; k < len; k++) {
        UChar ch = *(str + k);
        if (Font::treatAsSpace(ch)) {
            // Substitute in the space glyph at the appropriate place in the glyphs
            // array.
            glyphs[clusters[k]] = fontData->spaceGlyph();
            advances[clusters[k]] = logicalSpaceWidth;
            spaceCharacters[clusters[k]] = m_currentCharacter + k + item.iCharPos;
        }

        if (Font::isRoundingHackCharacter(ch))
            roundingHackCharacters[clusters[k]] = m_currentCharacter + k + item.iCharPos;

        int boundary = k + m_currentCharacter + item.iCharPos;
        if (boundary < m_run.length() &&
            Font::isRoundingHackCharacter(*(str + k + 1)))
            roundingHackWordBoundaries[clusters[k]] = boundary;
    }

    // Populate our glyph buffer with this information.
    bool hasExtraSpacing = m_font.letterSpacing() || m_font.wordSpacing() || m_padding;
    
    float leftEdge = m_runWidthSoFar;

    for (unsigned k = 0; k < glyphs.size(); k++) {
        Glyph glyph = glyphs[k];
        float advance = advances[k] / cLogicalScale;
        float offsetX = offsets[k].du / cLogicalScale;
        float offsetY = offsets[k].dv / cLogicalScale;

        // Match AppKit's rules for the integer vs. non-integer rendering modes.
        float roundedAdvance = roundf(advance);
        if (!m_font.isPrinterFont() && !fontData->isSystemFont()) {
            advance = roundedAdvance;
            offsetX = roundf(offsetX);
            offsetY = roundf(offsetY);
        }

        advance += fontData->syntheticBoldOffset();

        // We special case spaces in two ways when applying word rounding.
        // First, we round spaces to an adjusted width in all fonts.
        // Second, in fixed-pitch fonts we ensure that all glyphs that
        // match the width of the space glyph have the same width as the space glyph.
        if (roundedAdvance == roundedSpaceWidth && (fontData->pitch() == FixedPitch || glyph == fontData->spaceGlyph()) &&
            m_run.applyWordRounding())
            advance = fontData->adjustedSpaceWidth();

        if (hasExtraSpacing) {
            // If we're a glyph with an advance, go ahead and add in letter-spacing.
            // That way we weed out zero width lurkers.  This behavior matches the fast text code path.
            if (advance && m_font.letterSpacing())
                advance += m_font.letterSpacing();

            // Handle justification and word-spacing.
            if (glyph == fontData->spaceGlyph()) {
                // Account for padding. WebCore uses space padding to justify text.
                // We distribute the specified padding over the available spaces in the run.
                if (m_padding) {
                    // Use leftover padding if not evenly divisible by number of spaces.
                    if (m_padding < m_padPerSpace) {
                        advance += m_padding;
                        m_padding = 0;
                    } else {
                        advance += m_padPerSpace;
                        m_padding -= m_padPerSpace;
                    }
                }

                // Account for word-spacing.
                int characterIndex = spaceCharacters[k];
                if (characterIndex > 0 && !Font::treatAsSpace(*m_run.data(characterIndex - 1)) && m_font.wordSpacing())
                    advance += m_font.wordSpacing();
            }
        }

        // Deal with the float/integer impedance mismatch between CG and WebCore. "Words" (characters 
        // followed by a character defined by isRoundingHackCharacter()) are always an integer width.
        // We adjust the width of the last character of a "word" to ensure an integer width.
        // Force characters that are used to determine word boundaries for the rounding hack
        // to be integer width, so the following words will start on an integer boundary.
        int roundingHackIndex = roundingHackCharacters[k];
        if (m_run.applyWordRounding() && roundingHackIndex != -1)
            advance = ceilf(advance);

        // Check to see if the next character is a "rounding hack character", if so, adjust the
        // width so that the total run width will be on an integer boundary.
        int position = m_currentCharacter + len;
        bool lastGlyph = (k == glyphs.size() - 1) && (m_run.rtl() ? i == 0 : i == m_items.size() - 2) && (position >= m_end);
        if ((m_run.applyWordRounding() && roundingHackWordBoundaries[k] != -1) ||
            (m_run.applyRunRounding() && lastGlyph)) { 
            float totalWidth = m_runWidthSoFar + advance;
            advance += ceilf(totalWidth) - totalWidth;
        }

        m_runWidthSoFar += advance;

        // FIXME: We need to take the GOFFSETS for combining glyphs and store them in the glyph buffer
        // as well, so that when the time comes to draw those glyphs, we can apply the appropriate
        // translation.
        if (glyphBuffer) {
            FloatSize size(offsetX, -offsetY);
            glyphBuffer->add(glyph, fontData, advance, &size);
        }

        // Mutate the glyph array to contain our altered advances.
        if (m_computingOffsetPosition)
            advances[k] = advance;
    }

    while (m_computingOffsetPosition && m_offsetX >= leftEdge && m_offsetX < m_runWidthSoFar) {
        // The position is somewhere inside this run.
        int trailing = 0;
        ScriptXtoCP(m_offsetX - leftEdge, clusters.size(), glyphs.size(), clusters.data(), visualAttributes.data(),
                    advances.data(), &item.a, &m_offsetPosition, &trailing);
        if (trailing && m_includePartialGlyphs && m_offsetPosition < len - 1) {
            m_offsetPosition += m_currentCharacter + m_items[i].iCharPos;
            m_offsetX += m_run.rtl() ? -trailing : trailing;
        } else {
            m_computingOffsetPosition = false;
            m_offsetPosition += m_currentCharacter + m_items[i].iCharPos;
            if (trailing && m_includePartialGlyphs)
               m_offsetPosition++;
            return false;
        }
    }

    return true;
}