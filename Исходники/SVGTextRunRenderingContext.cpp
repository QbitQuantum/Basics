void SVGTextRunRenderingContext::drawSVGGlyphs(GraphicsContext* context, const TextRun& run, const SimpleFontData* fontData, const GlyphBuffer& glyphBuffer, int from, int numGlyphs, const FloatPoint& point) const
{
    SVGFontElement* fontElement = 0;
    SVGFontFaceElement* fontFaceElement = 0;

    const SVGFontData* svgFontData = svgFontAndFontFaceElementForFontData(fontData, fontFaceElement, fontElement);
    if (!fontElement || !fontFaceElement)
        return;

    // We can only paint SVGFonts if a context is available.
    RenderSVGResource* activePaintingResource = activePaintingResourceFromRun(run);
    RenderObject* renderObject = renderObjectFromRun(run);
    RenderObject* parentRenderObject = firstParentRendererForNonTextNode(renderObject);
    RenderStyle* parentRenderObjectStyle = 0;

    ASSERT(renderObject);
    if (!activePaintingResource) {
        // TODO: We're only supporting simple filled HTML text so far.
        RenderSVGResourceSolidColor* solidPaintingResource = RenderSVGResource::sharedSolidPaintingResource();
        solidPaintingResource->setColor(context->fillColor());
        activePaintingResource = solidPaintingResource;
    }
 
    bool isVerticalText = false;
    if (parentRenderObject) {
        parentRenderObjectStyle = parentRenderObject->style();
        ASSERT(parentRenderObjectStyle);
        isVerticalText = parentRenderObjectStyle->svgStyle()->isVerticalWritingMode();
    }

    float scale = scaleEmToUnits(fontData->platformData().size(), fontFaceElement->unitsPerEm());
    ASSERT(activePaintingResource);

    FloatPoint glyphOrigin;
    glyphOrigin.setX(svgFontData->horizontalOriginX() * scale);
    glyphOrigin.setY(svgFontData->horizontalOriginY() * scale);

    FloatPoint currentPoint = point;
    RenderSVGResourceMode resourceMode = context->textDrawingMode() == TextModeStroke ? ApplyToStrokeMode : ApplyToFillMode;
    for (int i = 0; i < numGlyphs; ++i) {
        Glyph glyph = glyphBuffer.glyphAt(from + i);
        if (!glyph)
            continue;

        float advance = glyphBuffer.advanceAt(from + i);
        SVGGlyph svgGlyph = fontElement->svgGlyphForGlyph(glyph);
        ASSERT(!svgGlyph.isPartOfLigature);
        ASSERT(svgGlyph.tableEntry == glyph);

        SVGGlyphElement::inheritUnspecifiedAttributes(svgGlyph, svgFontData);

        // FIXME: Support arbitary SVG content as glyph (currently limited to <glyph d="..."> situations).
        if (svgGlyph.pathData.isEmpty()) {
            if (isVerticalText)
                currentPoint.move(0, advance);
            else
                currentPoint.move(advance, 0);
            continue;
         }

        context->save();

        if (isVerticalText) {
            glyphOrigin.setX(svgGlyph.verticalOriginX * scale);
            glyphOrigin.setY(svgGlyph.verticalOriginY * scale);
         }

        AffineTransform glyphPathTransform;
        glyphPathTransform.translate(currentPoint.x() + glyphOrigin.x(), currentPoint.y() + glyphOrigin.y());
        glyphPathTransform.scale(scale, -scale);

        Path glyphPath = svgGlyph.pathData;
        glyphPath.transform(glyphPathTransform);

        if (activePaintingResource->applyResource(parentRenderObject, parentRenderObjectStyle, context, resourceMode)) {
            if (renderObject && renderObject->isSVGInlineText()) {
                const RenderSVGInlineText* textRenderer = toRenderSVGInlineText(renderObject);
                context->setStrokeThickness(context->strokeThickness() * textRenderer->scalingFactor());
            }
            activePaintingResource->postApplyResource(parentRenderObject, context, resourceMode, &glyphPath, 0);
         }
 
        context->restore();

        if (isVerticalText)
            currentPoint.move(0, advance);
        else
            currentPoint.move(advance, 0);
    }
}