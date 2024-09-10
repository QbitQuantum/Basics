inline unsigned WidthIterator::advanceInternal(TextIterator& textIterator, GlyphBuffer* glyphBuffer)
{
    bool rtl = m_run.rtl();
    bool hasExtraSpacing = (m_font->letterSpacing() || m_font->wordSpacing() || m_expansion) && !m_run.spacingDisabled();

    float widthSinceLastRounding = m_runWidthSoFar;
    m_runWidthSoFar = floorf(m_runWidthSoFar);
    widthSinceLastRounding -= m_runWidthSoFar;

    float lastRoundingWidth = m_finalRoundingWidth;
    FloatRect bounds;

    const SimpleFontData* primaryFont = m_font->primaryFont();
    const SimpleFontData* lastFontData = primaryFont;
    int lastGlyphCount = glyphBuffer ? glyphBuffer->size() : 0;

    UChar32 character = 0;
    unsigned clusterLength = 0;
    CharactersTreatedAsSpace charactersTreatedAsSpace;
    String normalizedSpacesStringCache;
    while (textIterator.consume(character, clusterLength)) {
        unsigned advanceLength = clusterLength;
        int currentCharacter = textIterator.currentCharacter();
        const GlyphData& glyphData = glyphDataForCharacter(character, rtl, currentCharacter, advanceLength, normalizedSpacesStringCache);
        Glyph glyph = glyphData.glyph;
        const SimpleFontData* fontData = glyphData.fontData;

        ASSERT(fontData);

        // Now that we have a glyph and font data, get its width.
        float width;
        if (character == '\t' && m_run.allowTabs())
            width = m_font->tabWidth(*fontData, m_run.tabSize(), m_run.xPos() + m_runWidthSoFar + widthSinceLastRounding);
        else {
            width = fontData->widthForGlyph(glyph);

            // SVG uses horizontalGlyphStretch(), when textLength is used to stretch/squeeze text.
            width *= m_run.horizontalGlyphStretch();

            // We special case spaces in two ways when applying word rounding.
            // First, we round spaces to an adjusted width in all fonts.
            // Second, in fixed-pitch fonts we ensure that all characters that
            // match the width of the space character have the same width as the space character.
            if (m_run.applyWordRounding() && width == fontData->spaceWidth() && (fontData->pitch() == FixedPitch || glyph == fontData->spaceGlyph()))
                width = fontData->adjustedSpaceWidth();
        }

        if (fontData != lastFontData && width) {
            if (shouldApplyFontTransforms()) {
                m_runWidthSoFar += applyFontTransforms(glyphBuffer, m_run.ltr(), lastGlyphCount, lastFontData, *this, m_typesettingFeatures, charactersTreatedAsSpace);
                lastGlyphCount = glyphBuffer->size(); // applyFontTransforms doesn't update when there had been only one glyph.
            }

            lastFontData = fontData;
            if (m_fallbackFonts && fontData != primaryFont) {
                // FIXME: This does a little extra work that could be avoided if
                // glyphDataForCharacter() returned whether it chose to use a small caps font.
                if (!m_font->isSmallCaps() || character == u_toupper(character))
                    m_fallbackFonts->add(fontData);
                else {
                    const GlyphData& uppercaseGlyphData = m_font->glyphDataForCharacter(u_toupper(character), rtl);
                    if (uppercaseGlyphData.fontData != primaryFont)
                        m_fallbackFonts->add(uppercaseGlyphData.fontData);
                }
            }
        }

        if (hasExtraSpacing) {
            // Account for letter-spacing.
            if (width && m_font->letterSpacing())
                width += m_font->letterSpacing();

            static bool expandAroundIdeographs = Font::canExpandAroundIdeographsInComplexText();
            bool treatAsSpace = Font::treatAsSpace(character);
            if (treatAsSpace || (expandAroundIdeographs && Font::isCJKIdeographOrSymbol(character))) {
                // Distribute the run's total expansion evenly over all expansion opportunities in the run.
                if (m_expansion) {
                    float previousExpansion = m_expansion;
                    if (!treatAsSpace && !m_isAfterExpansion) {
                        // Take the expansion opportunity before this ideograph.
                        m_expansion -= m_expansionPerOpportunity;
                        float expansionAtThisOpportunity = !m_run.applyWordRounding() ? m_expansionPerOpportunity : roundf(previousExpansion) - roundf(m_expansion);
                        m_runWidthSoFar += expansionAtThisOpportunity;
                        if (glyphBuffer) {
                            if (glyphBuffer->isEmpty()) {
                                if (m_forTextEmphasis)
                                    glyphBuffer->add(fontData->zeroWidthSpaceGlyph(), fontData, m_expansionPerOpportunity, currentCharacter);
                                else
                                    glyphBuffer->add(fontData->spaceGlyph(), fontData, expansionAtThisOpportunity, currentCharacter);
                            } else
                                glyphBuffer->expandLastAdvance(expansionAtThisOpportunity);
                        }
                        previousExpansion = m_expansion;
                    }
                    if (m_run.allowsTrailingExpansion() || (m_run.ltr() && currentCharacter + advanceLength < static_cast<size_t>(m_run.length()))
                        || (m_run.rtl() && currentCharacter)) {
                        m_expansion -= m_expansionPerOpportunity;
                        width += !m_run.applyWordRounding() ? m_expansionPerOpportunity : roundf(previousExpansion) - roundf(m_expansion);
                        m_isAfterExpansion = true;
                    }
                } else
                    m_isAfterExpansion = false;

                // Account for word spacing.
                // We apply additional space between "words" by adding width to the space character.
                if (treatAsSpace && (character != '\t' || !m_run.allowTabs()) && (currentCharacter || character == noBreakSpace) && m_font->wordSpacing())
                    width += m_font->wordSpacing();
            } else
                m_isAfterExpansion = false;
        }

        if (shouldApplyFontTransforms() && glyphBuffer && Font::treatAsSpace(character))
            charactersTreatedAsSpace.append(std::make_pair(glyphBuffer->size(),
                OriginalAdvancesForCharacterTreatedAsSpace(character == ' ', glyphBuffer->size() ? glyphBuffer->advanceAt(glyphBuffer->size() - 1).width() : 0, width)));

        if (m_accountForGlyphBounds) {
            bounds = fontData->boundsForGlyph(glyph);
            if (!currentCharacter)
                m_firstGlyphOverflow = std::max<float>(0, -bounds.x());
        }

        if (m_forTextEmphasis && !Font::canReceiveTextEmphasis(character))
            glyph = 0;

        // Advance past the character we just dealt with.
        textIterator.advance(advanceLength);

        float oldWidth = width;

        // Force characters that are used to determine word boundaries for the rounding hack
        // to be integer width, so following words will start on an integer boundary.
        if (m_run.applyWordRounding() && Font::isRoundingHackCharacter(character)) {
            width = ceilf(width);

            // Since widthSinceLastRounding can lose precision if we include measurements for
            // preceding whitespace, we bypass it here.
            m_runWidthSoFar += width;

            // Since this is a rounding hack character, we should have reset this sum on the previous
            // iteration.
            ASSERT(!widthSinceLastRounding);
        } else {
            // Check to see if the next character is a "rounding hack character", if so, adjust
            // width so that the total run width will be on an integer boundary.
            if ((m_run.applyWordRounding() && textIterator.currentCharacter() < m_run.length() && Font::isRoundingHackCharacter(*(textIterator.characters())))
                || (m_run.applyRunRounding() && textIterator.currentCharacter() >= m_run.length())) {
                float totalWidth = widthSinceLastRounding + width;
                widthSinceLastRounding = ceilf(totalWidth);
                width += widthSinceLastRounding - totalWidth;
                m_runWidthSoFar += widthSinceLastRounding;
                widthSinceLastRounding = 0;
            } else
                widthSinceLastRounding += width;
        }

        if (glyphBuffer)
            glyphBuffer->add(glyph, fontData, (rtl ? oldWidth + lastRoundingWidth : width), currentCharacter);

        lastRoundingWidth = width - oldWidth;

        if (m_accountForGlyphBounds) {
            m_maxGlyphBoundingBoxY = std::max(m_maxGlyphBoundingBoxY, bounds.maxY());
            m_minGlyphBoundingBoxY = std::min(m_minGlyphBoundingBoxY, bounds.y());
            m_lastGlyphOverflow = std::max<float>(0, bounds.maxX() - width);
        }
    }

    if (shouldApplyFontTransforms())
        m_runWidthSoFar += applyFontTransforms(glyphBuffer, m_run.ltr(), lastGlyphCount, lastFontData, *this, m_typesettingFeatures, charactersTreatedAsSpace);

    unsigned consumedCharacters = textIterator.currentCharacter() - m_currentCharacter;
    m_currentCharacter = textIterator.currentCharacter();
    m_runWidthSoFar += widthSinceLastRounding;
    m_finalRoundingWidth = lastRoundingWidth;
    return consumedCharacters;
}