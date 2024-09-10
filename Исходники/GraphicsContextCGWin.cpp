void GraphicsContext::drawLineForDocumentMarker(const FloatPoint& point, float width, DocumentMarkerLineStyle style)
{
    if (paintingDisabled())
        return;

    if (style != DocumentMarkerSpellingLineStyle && style != DocumentMarkerGrammarLineStyle)
        return;

    // These are the same for misspelling or bad grammar
    const int patternHeight = 3; // 3 rows
    ASSERT(cMisspellingLineThickness == patternHeight);
    const int patternWidth = 4; // 4 pixels
    ASSERT(patternWidth == cMisspellingLinePatternWidth);

    // Make sure to draw only complete dots.
    // NOTE: Code here used to shift the underline to the left and increase the width
    // to make sure everything gets underlined, but that results in drawing out of
    // bounds (e.g. when at the edge of a view) and could make it appear that the
    // space between adjacent misspelled words was underlined.
    // allow slightly more considering that the pattern ends with a transparent pixel
    float widthMod = fmodf(width, patternWidth);
    if (patternWidth - widthMod > cMisspellingLinePatternGapWidth)
        width -= widthMod;
      
    // Draw the underline
    CGContextRef context = platformContext();
    CGContextSaveGState(context);

    const Color& patternColor = style == DocumentMarkerGrammarLineStyle ? grammarPatternColor() : spellingPatternColor();
    setCGStrokeColor(context, patternColor);

    wkSetPatternPhaseInUserSpace(context, point);
    CGContextSetBlendMode(context, kCGBlendModeNormal);
    
    // 3 rows, each offset by half a pixel for blending purposes
    const CGPoint upperPoints [] = {{point.x(), point.y() + patternHeight - 2.5 }, {point.x() + width, point.y() + patternHeight - 2.5}};
    const CGPoint middlePoints [] = {{point.x(), point.y() + patternHeight - 1.5 }, {point.x() + width, point.y() + patternHeight - 1.5}};
    const CGPoint lowerPoints [] = {{point.x(), point.y() + patternHeight - 0.5 }, {point.x() + width, point.y() + patternHeight - 0.5 }};
    
    // Dash lengths for the top and bottom of the error underline are the same.
    // These are magic.
    static const float edge_dash_lengths[] = {2.0f, 2.0f};
    static const float middle_dash_lengths[] = {2.76f, 1.24f};
    static const float edge_offset = -(edge_dash_lengths[1] - 1.0f) / 2.0f;
    static const float middle_offset = -(middle_dash_lengths[1] - 1.0f) / 2.0f;

    // Line opacities.  Once again, these are magic.
    const float upperOpacity = 0.33f;
    const float middleOpacity = 0.75f;
    const float lowerOpacity = 0.88f;

    //Top line
    CGContextSetLineDash(context, edge_offset, edge_dash_lengths, WTF_ARRAY_LENGTH(edge_dash_lengths));
    CGContextSetAlpha(context, upperOpacity);
    CGContextStrokeLineSegments(context, upperPoints, 2);
 
    // Middle line
    CGContextSetLineDash(context, middle_offset, middle_dash_lengths, WTF_ARRAY_LENGTH(middle_dash_lengths));
    CGContextSetAlpha(context, middleOpacity);
    CGContextStrokeLineSegments(context, middlePoints, 2);
    
    // Bottom line
    CGContextSetLineDash(context, edge_offset, edge_dash_lengths, WTF_ARRAY_LENGTH(edge_dash_lengths));
    CGContextSetAlpha(context, lowerOpacity);
    CGContextStrokeLineSegments(context, lowerPoints, 2);

    CGContextRestoreGState(context);
}