void ShapeButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    if (! isEnabled())
    {
        isMouseOverButton = false;
        isButtonDown = false;
    }

    g.setColour ((isButtonDown) ? downColour
                                : (isMouseOverButton) ? overColour
                                                      : normalColour);

    int w = getWidth();
    int h = getHeight();

    if (getComponentEffect() != nullptr)
    {
        w -= 4;
        h -= 4;
    }

    const float offset = (outlineWidth * 0.5f) + (isButtonDown ? 1.5f : 0.0f);

    const AffineTransform trans (shape.getTransformToScaleToFit (offset, offset,
                                                                 w - offset - outlineWidth,
                                                                 h - offset - outlineWidth,
                                                                 maintainShapeProportions));
    g.fillPath (shape, trans);

    if (outlineWidth > 0.0f)
    {
        g.setColour (outlineColour);
        g.strokePath (shape, PathStrokeType (outlineWidth), trans);
    }
}