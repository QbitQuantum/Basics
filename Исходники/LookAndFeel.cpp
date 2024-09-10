void NonShinyLookAndFeel::drawTickBox (Graphics& g,
                               Component& component,
                               float x, float y, float w, float h,
                               const bool ticked,
                               const bool isEnabled,
                               const bool isMouseOverButton,
                               const bool isButtonDown)
{
    const float boxSize = w * 0.8f;

    drawGlassLozenge (g,x,y+(h-boxSize)*0.5f,boxSize,boxSize,
					  createBaseColour (component.findColour (TextButton::buttonColourId)
                                                 .withMultipliedAlpha (isEnabled ? 1.0f : 0.5f),
									    true,
                                        isMouseOverButton,
                                        isButtonDown),
					  isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.2f : 0.7f) : 0.4f,
					  -1.0f,true,true,true,true);

    if (ticked)
    {
        Path tick;
        tick.startNewSubPath (2.0f, 3.0f);
        tick.lineTo (3.5f, 6.0f);
        tick.lineTo (6.5f, 0.0f);

        g.setColour (isEnabled ? Colours::black : Colours::grey);

        const AffineTransform trans (AffineTransform::scale (w / 9.0f, h / 9.0f)
                                         .translated (x, y));

        g.strokePath (tick, PathStrokeType (2.5f), trans);
    }
}