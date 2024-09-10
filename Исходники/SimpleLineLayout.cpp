bool canUseFor(const RenderBlockFlow& flow)
{
#if !PLATFORM(MAC) && !PLATFORM(GTK) && !PLATFORM(EFL)
    // FIXME: Non-mac platforms are hitting ASSERT(run.charactersLength() >= run.length())
    // https://bugs.webkit.org/show_bug.cgi?id=123338
    return false;
#endif
    if (!flow.frame().settings().simpleLineLayoutEnabled())
        return false;
    if (!flow.firstChild())
        return false;
    // This currently covers <blockflow>#text</blockflow> case.
    // The <blockflow><inline>#text</inline></blockflow> case is also popular and should be relatively easy to cover.
    if (flow.firstChild() != flow.lastChild())
        return false;
    if (!flow.firstChild()->isText())
        return false;
    // Supporting floats would be very beneficial.
    if (flow.containsFloats())
        return false;
    if (!flow.isHorizontalWritingMode())
        return false;
    if (flow.flowThreadState() != RenderObject::NotInsideFlowThread)
        return false;
    if (flow.hasOutline())
        return false;
    if (flow.isRubyText() || flow.isRubyBase())
        return false;
    if (flow.parent()->isDeprecatedFlexibleBox())
        return false;
    // These tests only works during layout. Outside layout this function may give false positives.
    if (flow.view().layoutState()) {
#if ENABLE(CSS_SHAPES)
        if (flow.view().layoutState()->shapeInsideInfo())
            return false;
#endif
        if (flow.view().layoutState()->m_columnInfo)
            return false;
    }
    const RenderStyle& style = flow.style();
    if (style.textDecorationsInEffect() != TextDecorationNone)
        return false;
    if (style.textAlign() == JUSTIFY)
        return false;
    // Non-visible overflow should be pretty easy to support.
    if (style.overflowX() != OVISIBLE || style.overflowY() != OVISIBLE)
        return false;
    // Pre/no-wrap would be very helpful to support.
    if (style.whiteSpace() != NORMAL)
        return false;
    if (!style.textIndent().isZero())
        return false;
    if (style.wordSpacing() || style.letterSpacing())
        return false;
    if (style.textTransform() != TTNONE)
        return false;
    if (!style.isLeftToRightDirection())
        return false;
    if (style.lineBoxContain() != RenderStyle::initialLineBoxContain())
        return false;
    if (style.writingMode() != TopToBottomWritingMode)
        return false;
    if (style.lineBreak() != LineBreakAuto)
        return false;
    if (style.wordBreak() != NormalWordBreak)
        return false;
    if (style.unicodeBidi() != UBNormal || style.rtlOrdering() != LogicalOrder)
        return false;
    if (style.lineAlign() != LineAlignNone || style.lineSnap() != LineSnapNone)
        return false;
    if (style.hyphens() == HyphensAuto)
        return false;
    if (style.textEmphasisFill() != TextEmphasisFillFilled || style.textEmphasisMark() != TextEmphasisMarkNone)
        return false;
    if (style.textShadow())
        return false;
#if ENABLE(CSS_SHAPES)
    if (style.resolvedShapeInside())
        return true;
#endif
    if (style.textOverflow() || (flow.isAnonymousBlock() && flow.parent()->style().textOverflow()))
        return false;
    if (style.hasPseudoStyle(FIRST_LINE) || style.hasPseudoStyle(FIRST_LETTER))
        return false;
    if (style.hasTextCombine())
        return false;
    if (style.overflowWrap() != NormalOverflowWrap)
        return false;
    if (style.backgroundClip() == TextFillBox)
        return false;
    if (style.borderFit() == BorderFitLines)
        return false;
    const RenderText& textRenderer = toRenderText(*flow.firstChild());
    if (textRenderer.isCombineText() || textRenderer.isCounter() || textRenderer.isQuote() || textRenderer.isTextFragment()
#if ENABLE(SVG)
        || textRenderer.isSVGInlineText()
#endif
        )
        return false;
    if (style.font().codePath(TextRun(textRenderer.text())) != Font::Simple)
        return false;

    // We assume that all lines have metrics based purely on the primary font.
    auto& primaryFontData = *style.font().primaryFont();
    if (primaryFontData.isLoading())
        return false;

    unsigned length = textRenderer.textLength();
    for (unsigned i = 0; i < length; ++i) {
        UChar character = textRenderer.characterAt(i);
        if (character == ' ')
            continue;

        // These would be easy to support.
        if (character == noBreakSpace)
            return false;
        if (character == softHyphen)
            return false;

        UCharDirection direction = u_charDirection(character);
        if (direction == U_RIGHT_TO_LEFT || direction == U_RIGHT_TO_LEFT_ARABIC
            || direction == U_RIGHT_TO_LEFT_EMBEDDING || direction == U_RIGHT_TO_LEFT_OVERRIDE
            || direction == U_LEFT_TO_RIGHT_EMBEDDING || direction == U_LEFT_TO_RIGHT_OVERRIDE
            || direction == U_POP_DIRECTIONAL_FORMAT || direction == U_BOUNDARY_NEUTRAL)
            return false;

        if (!primaryFontData.glyphForCharacter(character))
            return false;
    }
    return true;
}