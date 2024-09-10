void Font::drawGlyphs(GraphicsContext* graphicsContext, const SimpleFontData* font, const GlyphBuffer& glyphBuffer, 
    int from, int numGlyphs, const FloatPoint& point) const
{
    CGContextRef cgContext = graphicsContext->platformContext();
    bool shouldUseFontSmoothing = WebCoreShouldUseFontSmoothing();

    switch(fontDescription().fontSmoothing()) {
    case Antialiased: {
        graphicsContext->setShouldAntialias(true);
        shouldUseFontSmoothing = false;
        break;
    }
    case SubpixelAntialiased: {
        graphicsContext->setShouldAntialias(true);
        shouldUseFontSmoothing = true;
        break;
    }
    case NoSmoothing: {
        graphicsContext->setShouldAntialias(false);
        shouldUseFontSmoothing = false;
        break;
    }
    case AutoSmoothing: {
        // For the AutoSmooth case, don't do anything! Keep the default settings.
        break; 
    }
    default: 
        ASSERT_NOT_REACHED();
    }

    uint32_t oldFontSmoothingStyle = wkSetFontSmoothingStyle(cgContext, shouldUseFontSmoothing);

    const FontPlatformData& platformData = font->platformData();

    CGContextSetFont(cgContext, platformData.cgFont());

    CGAffineTransform matrix = CGAffineTransformIdentity;
    matrix.b = -matrix.b;
    matrix.d = -matrix.d;

    if (platformData.syntheticOblique()) {
        static float skew = -tanf(syntheticObliqueAngle * piFloat / 180.0f);
        matrix = CGAffineTransformConcat(matrix, CGAffineTransformMake(1, 0, skew, 1, 0, 0));
    }

    CGContextSetTextMatrix(cgContext, matrix);

    // Uniscribe gives us offsets to help refine the positioning of combining glyphs.
    FloatSize translation = glyphBuffer.offsetAt(from);

    CGContextSetFontSize(cgContext, platformData.size());
    wkSetCGContextFontRenderingStyle(cgContext, font->isSystemFont(), false, font->platformData().useGDI());

    FloatSize shadowOffset;
    float shadowBlur;
    Color shadowColor;
    ColorSpace shadowColorSpace;
    graphicsContext->getShadow(shadowOffset, shadowBlur, shadowColor, shadowColorSpace);

    bool hasSimpleShadow = graphicsContext->textDrawingMode() == TextModeFill && shadowColor.isValid() && !shadowBlur && (!graphicsContext->shadowsIgnoreTransforms() || graphicsContext->getCTM().isIdentityOrTranslationOrFlipped());
    if (hasSimpleShadow) {
        // Paint simple shadows ourselves instead of relying on CG shadows, to avoid losing subpixel antialiasing.
        graphicsContext->clearShadow();
        Color fillColor = graphicsContext->fillColor();
        ColorSpace fillColorSpace = graphicsContext->fillColorSpace();
        Color shadowFillColor(shadowColor.red(), shadowColor.green(), shadowColor.blue(), shadowColor.alpha() * fillColor.alpha() / 255);
        graphicsContext->setFillColor(shadowFillColor, shadowColorSpace);
        float shadowTextX = point.x() + translation.width() + shadowOffset.width();
        // If shadows are ignoring transforms, then we haven't applied the Y coordinate flip yet, so down is negative.
        float shadowTextY = point.y() + translation.height() + shadowOffset.height() * (graphicsContext->shadowsIgnoreTransforms() ? -1 : 1);
        CGContextSetTextPosition(cgContext, shadowTextX, shadowTextY);
        CGContextShowGlyphsWithAdvances(cgContext, glyphBuffer.glyphs(from), static_cast<const CGSize*>(glyphBuffer.advances(from)), numGlyphs);
        if (font->syntheticBoldOffset()) {
            CGContextSetTextPosition(cgContext, point.x() + translation.width() + shadowOffset.width() + font->syntheticBoldOffset(), point.y() + translation.height() + shadowOffset.height());
            CGContextShowGlyphsWithAdvances(cgContext, glyphBuffer.glyphs(from), static_cast<const CGSize*>(glyphBuffer.advances(from)), numGlyphs);
        }
        graphicsContext->setFillColor(fillColor, fillColorSpace);
    }

    CGContextSetTextPosition(cgContext, point.x() + translation.width(), point.y() + translation.height());
    CGContextShowGlyphsWithAdvances(cgContext, glyphBuffer.glyphs(from), static_cast<const CGSize*>(glyphBuffer.advances(from)), numGlyphs);
    if (font->syntheticBoldOffset()) {
        CGContextSetTextPosition(cgContext, point.x() + translation.width() + font->syntheticBoldOffset(), point.y() + translation.height());
        CGContextShowGlyphsWithAdvances(cgContext, glyphBuffer.glyphs(from), static_cast<const CGSize*>(glyphBuffer.advances(from)), numGlyphs);
    }

    if (hasSimpleShadow)
        graphicsContext->setShadow(shadowOffset, shadowBlur, shadowColor, shadowColorSpace);

    wkRestoreFontSmoothingStyle(cgContext, oldFontSmoothingStyle);
}