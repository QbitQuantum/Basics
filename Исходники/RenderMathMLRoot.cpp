void RenderMathMLRoot::paint(PaintInfo& info, const LayoutPoint& paintOffset)
{
    RenderMathMLBlock::paint(info, paintOffset);
    
    if (info.context->paintingDisabled())
        return;
    
    IntPoint adjustedPaintOffset = roundedIntPoint(paintOffset + location() + contentBoxRect().location());
    
    int startX = adjustedPaintOffset.x();
    int frontWidth = lroundf(gFrontWidthEms * style()->fontSize());
    int overbarWidth = roundToInt(contentLogicalWidth()) + m_overbarLeftPointShift;
    
    int baseHeight = roundToInt(contentLogicalHeight());
    int rootPad = lroundf(gSpaceAboveEms * style()->fontSize());
    adjustedPaintOffset.setY(adjustedPaintOffset.y() - rootPad);
    
    float radicalDipLeftPointYPos = (index() ? gRootRadicalDipLeftPointYPos : gSqrtRadicalDipLeftPointYPos) * baseHeight;
    
    FloatPoint overbarLeftPoint(startX - m_overbarLeftPointShift, adjustedPaintOffset.y());
    FloatPoint bottomPoint(startX - gRadicalBottomPointXFront * frontWidth, adjustedPaintOffset.y() + baseHeight + gRadicalBottomPointLower);
    FloatPoint dipLeftPoint(startX - gRadicalDipLeftPointXFront * frontWidth, adjustedPaintOffset.y() + radicalDipLeftPointYPos);
    FloatPoint leftEnd(startX - frontWidth, dipLeftPoint.y() + gRadicalLeftEndYShiftEms * style()->fontSize());
    
    GraphicsContextStateSaver stateSaver(*info.context);
    
    info.context->setStrokeThickness(gRadicalLineThicknessEms * style()->fontSize());
    info.context->setStrokeStyle(SolidStroke);
    info.context->setStrokeColor(style()->visitedDependentColor(CSSPropertyColor), ColorSpaceDeviceRGB);
    info.context->setLineJoin(MiterJoin);
    info.context->setMiterLimit(style()->fontSize());
    
    Path root;
    
    root.moveTo(FloatPoint(overbarLeftPoint.x() + overbarWidth, adjustedPaintOffset.y()));
    // draw top
    root.addLineTo(overbarLeftPoint);
    // draw from top left corner to bottom point of radical
    root.addLineTo(bottomPoint);
    // draw from bottom point to top of left part of radical base "dip"
    root.addLineTo(dipLeftPoint);
    // draw to end
    root.addLineTo(leftEnd);
    
    info.context->strokePath(root);
    
    GraphicsContextStateSaver maskStateSaver(*info.context);
    
    // Build a mask to draw the thick part of the root.
    Path mask;
    
    mask.moveTo(overbarLeftPoint);
    mask.addLineTo(bottomPoint);
    mask.addLineTo(dipLeftPoint);
    mask.addLineTo(FloatPoint(2 * dipLeftPoint.x() - leftEnd.x(), 2 * dipLeftPoint.y() - leftEnd.y()));
    
    info.context->clip(mask);
    
    // Draw the thick part of the root.
    info.context->setStrokeThickness(gRadicalThickLineThicknessEms * style()->fontSize());
    info.context->setLineCap(SquareCap);
    
    Path line;
    line.moveTo(bottomPoint);
    line.addLineTo(dipLeftPoint);
    
    info.context->strokePath(line);
}