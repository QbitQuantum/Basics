std::pair<GlyphData, GlyphPage*> FontGlyphs::glyphDataAndPageForCharacter(const FontDescription& description, UChar32 c, bool mirror, FontDataVariant variant) const
{
    ASSERT(isMainThread());

    if (variant == AutoVariant) {
        if (description.smallCaps() && !primarySimpleFontData(description)->isSVGFont()) {
            UChar32 upperC = u_toupper(c);
            if (upperC != c) {
                c = upperC;
                variant = SmallCapsVariant;
            } else
                variant = NormalVariant;
        } else
            variant = NormalVariant;
    }

    if (mirror)
        c = u_charMirror(c);

    unsigned pageNumber = (c / GlyphPage::size);

    GlyphPageTreeNode* node = pageNumber ? m_pages.get(pageNumber) : m_pageZero;
    if (!node) {
        node = GlyphPageTreeNode::getRootChild(realizeFontDataAt(description, 0), pageNumber);
        if (pageNumber)
            m_pages.set(pageNumber, node);
        else
            m_pageZero = node;
    }

    GlyphPage* page = 0;
    if (variant == NormalVariant) {
        // Fastest loop, for the common case (normal variant).
        while (true) {
            page = node->page();
            if (page) {
                GlyphData data = page->glyphDataForCharacter(c);
                if (data.fontData && (data.fontData->platformData().orientation() == Horizontal || data.fontData->isTextOrientationFallback()))
                    return std::make_pair(data, page);

                if (data.fontData) {
                    if (Font::isCJKIdeographOrSymbol(c)) {
                        if (!data.fontData->hasVerticalGlyphs()) {
                            // Use the broken ideograph font data. The broken ideograph font will use the horizontal width of glyphs
                            // to make sure you get a square (even for broken glyphs like symbols used for punctuation).
                            variant = BrokenIdeographVariant;
                            break;
                        }
#if PLATFORM(COCOA)
                        else if (data.fontData->platformData().syntheticOblique())
                            return glyphDataAndPageForCJKCharacterWithoutSyntheticItalic(c, data, page, pageNumber);
#endif
                    } else
                        return glyphDataAndPageForNonCJKCharacterWithGlyphOrientation(c, description.nonCJKGlyphOrientation(), data, page, pageNumber);

                    return std::make_pair(data, page);
                }

                if (node->isSystemFallback())
                    break;
            }

            node = node->getChild(realizeFontDataAt(description, node->level()), pageNumber);
            if (pageNumber)
                m_pages.set(pageNumber, node);
            else
                m_pageZero = node;
        }
    }
    if (variant != NormalVariant) {
        while (true) {
            page = node->page();
            if (page) {
                GlyphData data = page->glyphDataForCharacter(c);
                if (data.fontData) {
                    // The variantFontData function should not normally return 0.
                    // But if it does, we will just render the capital letter big.
                    RefPtr<SimpleFontData> variantFontData = data.fontData->variantFontData(description, variant);
                    if (!variantFontData)
                        return std::make_pair(data, page);

                    GlyphPageTreeNode* variantNode = GlyphPageTreeNode::getRootChild(variantFontData.get(), pageNumber);
                    GlyphPage* variantPage = variantNode->page();
                    if (variantPage) {
                        GlyphData data = variantPage->glyphDataForCharacter(c);
                        if (data.fontData)
                            return std::make_pair(data, variantPage);
                    }

                    // Do not attempt system fallback off the variantFontData. This is the very unlikely case that
                    // a font has the lowercase character but the small caps font does not have its uppercase version.
                    return std::make_pair(variantFontData->missingGlyphData(), page);
                }

                if (node->isSystemFallback())
                    break;
            }

            node = node->getChild(realizeFontDataAt(description, node->level()), pageNumber);
            if (pageNumber)
                m_pages.set(pageNumber, node);
            else
                m_pageZero = node;
        }
    }

    ASSERT(page);
    ASSERT(node->isSystemFallback());

    // System fallback is character-dependent. When we get here, we
    // know that the character in question isn't in the system fallback
    // font's glyph page. Try to lazily create it here.
    UChar codeUnits[2];
    int codeUnitsLength;
    if (c <= 0xFFFF) {
        codeUnits[0] = Font::normalizeSpaces(c);
        codeUnitsLength = 1;
    } else {
        codeUnits[0] = U16_LEAD(c);
        codeUnits[1] = U16_TRAIL(c);
        codeUnitsLength = 2;
    }
    const SimpleFontData* originalFontData = primaryFontData(description)->fontDataForCharacter(c);
    RefPtr<SimpleFontData> characterFontData = fontCache().systemFallbackForCharacters(description, originalFontData, m_isForPlatformFont, codeUnits, codeUnitsLength);
    if (characterFontData) {
        if (characterFontData->platformData().orientation() == Vertical && !characterFontData->hasVerticalGlyphs() && Font::isCJKIdeographOrSymbol(c))
            variant = BrokenIdeographVariant;
        if (variant != NormalVariant)
            characterFontData = characterFontData->variantFontData(description, variant);
    }
    if (characterFontData) {
        // Got the fallback glyph and font.
        GlyphPage* fallbackPage = GlyphPageTreeNode::getRootChild(characterFontData.get(), pageNumber)->page();
        GlyphData data = fallbackPage && fallbackPage->fontDataForCharacter(c) ? fallbackPage->glyphDataForCharacter(c) : characterFontData->missingGlyphData();
        // Cache it so we don't have to do system fallback again next time.
        if (variant == NormalVariant) {
#if OS(WINCE)
            // missingGlyphData returns a null character, which is not suitable for GDI to display.
            // Also, sometimes we cannot map a font for the character on WINCE, but GDI can still
            // display the character, probably because the font package is not installed correctly.
            // So we just always set the glyph to be same as the character, and let GDI solve it.
            page->setGlyphDataForCharacter(c, c, characterFontData.get());
            characterFontData->setMaxGlyphPageTreeLevel(std::max(characterFontData->maxGlyphPageTreeLevel(), node->level()));
            return std::make_pair(page->glyphDataForCharacter(c), page);
#else
            page->setGlyphDataForCharacter(c, data.glyph, data.fontData);
            data.fontData->setMaxGlyphPageTreeLevel(std::max(data.fontData->maxGlyphPageTreeLevel(), node->level()));
            if (!Font::isCJKIdeographOrSymbol(c) && data.fontData->platformData().orientation() != Horizontal && !data.fontData->isTextOrientationFallback())
                return glyphDataAndPageForNonCJKCharacterWithGlyphOrientation(c, description.nonCJKGlyphOrientation(), data, fallbackPage, pageNumber);
#endif
        }
        return std::make_pair(data, page);
    }

    // Even system fallback can fail; use the missing glyph in that case.
    // FIXME: It would be nicer to use the missing glyph from the last resort font instead.
    GlyphData data = primarySimpleFontData(description)->missingGlyphData();
    if (variant == NormalVariant) {
#if OS(WINCE)
        // See comment about WINCE GDI handling near setGlyphDataForCharacter above.
        page->setGlyphDataForCharacter(c, c, data.fontData);
        data.fontData->setMaxGlyphPageTreeLevel(std::max(data.fontData->maxGlyphPageTreeLevel(), node->level()));
        return std::make_pair(page->glyphDataForCharacter(c), page);
#else
        page->setGlyphDataForCharacter(c, data.glyph, data.fontData);
        data.fontData->setMaxGlyphPageTreeLevel(std::max(data.fontData->maxGlyphPageTreeLevel(), node->level()));
#endif
    }
    return std::make_pair(data, page);
}