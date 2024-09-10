PassRefPtr<ShapeResult> HarfBuzzShaper::shapeResult()
{
    RefPtr<ShapeResult> result = ShapeResult::create(m_font,
        m_normalizedBufferLength, m_textRun.direction());
    HarfBuzzScopedPtr<hb_buffer_t> harfBuzzBuffer(hb_buffer_create(), hb_buffer_destroy);

    const FontDescription& fontDescription = m_font->getFontDescription();
    const String& localeString = fontDescription.locale();
    CString locale = localeString.latin1();
    const hb_language_t language = hb_language_from_string(locale.data(), locale.length());

    bool needsCapsHandling = fontDescription.variantCaps() != FontDescription::CapsNormal;
    OpenTypeCapsSupport capsSupport;

    RunSegmenter::RunSegmenterRange segmentRange = {
        0,
        0,
        USCRIPT_INVALID_CODE,
        OrientationIterator::OrientationInvalid,
        FontFallbackPriority::Invalid };
    RunSegmenter runSegmenter(
        m_normalizedBuffer.get(),
        m_normalizedBufferLength,
        m_font->getFontDescription().orientation());

    Vector<UChar32> fallbackCharsHint;

    // TODO: Check whether this treatAsZerowidthspace from the previous script
    // segmentation plays a role here, does the new scriptRuniterator handle that correctly?
    while (runSegmenter.consume(&segmentRange)) {
        RefPtr<FontFallbackIterator> fallbackIterator =
            m_font->createFontFallbackIterator(
            segmentRange.fontFallbackPriority);

        appendToHolesQueue(HolesQueueNextFont, 0, 0);
        appendToHolesQueue(HolesQueueRange, segmentRange.start, segmentRange.end - segmentRange.start);

        RefPtr<FontDataForRangeSet> currentFontDataForRangeSet;

        bool fontCycleQueued = false;
        while (m_holesQueue.size()) {
            HolesQueueItem currentQueueItem = m_holesQueue.takeFirst();

            if (currentQueueItem.m_action == HolesQueueNextFont) {
                // For now, we're building a character list with which we probe
                // for needed fonts depending on the declared unicode-range of a
                // segmented CSS font. Alternatively, we can build a fake font
                // for the shaper and check whether any glyphs were found, or
                // define a new API on the shaper which will give us coverage
                // information?
                if (!collectFallbackHintChars(fallbackCharsHint, fallbackIterator->needsHintList())) {
                    // Give up shaping since we cannot retrieve a font fallback
                    // font without a hintlist.
                    m_holesQueue.clear();
                    break;
                }

                currentFontDataForRangeSet = fallbackIterator->next(fallbackCharsHint);

                if (!currentFontDataForRangeSet->fontData()) {
                    ASSERT(!m_holesQueue.size());
                    break;
                }
                fontCycleQueued = false;
                continue;
            }

            SmallCapsIterator::SmallCapsBehavior smallCapsBehavior = SmallCapsIterator::SmallCapsSameCase;
            if (needsCapsHandling) {
                capsSupport = OpenTypeCapsSupport(
                    currentFontDataForRangeSet->fontData()->platformData().harfBuzzFace(),
                    fontDescription.variantCaps(),
                    ICUScriptToHBScript(segmentRange.script));
                if (capsSupport.needsRunCaseSplitting())
                    splitUntilNextCaseChange(currentQueueItem, smallCapsBehavior);
            }

            ASSERT(currentQueueItem.m_numCharacters);

            const SimpleFontData* smallcapsAdjustedFont = needsCapsHandling
                && capsSupport.needsSyntheticFont(smallCapsBehavior)
                ? currentFontDataForRangeSet->fontData()->smallCapsFontData(fontDescription).get()
                : currentFontDataForRangeSet->fontData();

            // Compatibility with SimpleFontData approach of keeping a flag for overriding drawing direction.
            // TODO: crbug.com/506224 This should go away in favor of storing that information elsewhere, for example in
            // ShapeResult.
            const SimpleFontData* directionAndSmallCapsAdjustedFont = fontDataAdjustedForOrientation(smallcapsAdjustedFont,
                m_font->getFontDescription().orientation(),
                segmentRange.renderOrientation);

            CaseMapIntend caseMapIntend = CaseMapIntend::KeepSameCase;
            if (needsCapsHandling) {
                caseMapIntend = capsSupport.needsCaseChange(smallCapsBehavior);
            }

            CaseMappingHarfBuzzBufferFiller(
                caseMapIntend,
                fontDescription.locale(),
                harfBuzzBuffer.get(),
                m_normalizedBuffer.get(),
                m_normalizedBufferLength,
                currentQueueItem.m_startIndex,
                currentQueueItem.m_numCharacters);

            CapsFeatureSettingsScopedOverlay capsOverlay(m_features, capsSupport.fontFeatureToUse(smallCapsBehavior));

            if (!shapeRange(harfBuzzBuffer.get(),
                currentQueueItem.m_startIndex,
                currentQueueItem.m_numCharacters,
                directionAndSmallCapsAdjustedFont,
                currentFontDataForRangeSet->ranges(),
                segmentRange.script,
                language))
                DLOG(ERROR) << "Shaping range failed.";

            if (!extractShapeResults(harfBuzzBuffer.get(),
                result.get(),
                fontCycleQueued,
                currentQueueItem,
                directionAndSmallCapsAdjustedFont,
                segmentRange.script,
                !fallbackIterator->hasNext()))
                DLOG(ERROR) << "Shape result extraction failed.";

            hb_buffer_reset(harfBuzzBuffer.get());
        }
    }
    return result.release();
}