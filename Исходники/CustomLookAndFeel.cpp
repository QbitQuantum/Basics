void CustomLookAndFeel::drawLinearSliderThumb (Graphics& g, int x, int y, int width,
                                               int height, float sliderPos,
                                               float minSliderPos, float maxSliderPos,
                                               const Slider::SliderStyle style,
                                               Slider& slider)
{
    if (style == Slider::LinearVertical)
    {
        bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
        Colour knobColour (slider.findColour (Slider::thumbColourId).withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f));
        
        const float thumbWidth = jmin (slider.getWidth() - 2 * spaceBetweenThumbAndComponentBorder,
                                       maxThumbWidthVertical);
        const float thumbHeight = thumbWidth * heightToWidthRatioVertical;
        
        const float xCenter = x + width * 0.5f;
        // Originally it was yCenter = sliderPos. But that way the thumb (and especially the center line) did
        // not always look the same because of aliasing. With this additional rounding it is ensured that the
        // vertical position of the thumb "snaps" to the closest pixel and therefore looks always the same.
        const float yCenter = (int)(sliderPos) + 0.5f;
        const float xThumb = xCenter - 0.5f * thumbWidth;
        const float yThumb = yCenter - 0.5f * thumbHeight;
        
        // The shape of the thumb
        Path p;
        p.addRoundedRectangle(xThumb, yThumb, thumbWidth, thumbHeight, 5.0f);
        
        // Drop shadow
        const DropShadow ds (Colours::black, 4, Point<int> (0, 0));
        ds.drawForPath (g, p);
        
        // Outline
        const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;
        g.setColour (Colours::black);
        //g.setColour (knobColour.darker());
        g.strokePath (p, PathStrokeType (outlineThickness));
        
        // Fill
        ColourGradient gradient (knobColour.darker(), xThumb, yThumb,
                                 knobColour.darker(), xThumb, yThumb + thumbHeight, false);
        gradient.addColour (0.5, knobColour.brighter());
        g.setGradientFill(gradient);
        g.fillPath (p);
//        g.setColour (knobColour);
//        g.fillPath (p);
        
        // Middle line
        g.setColour(Colours::black);
        g.drawLine(xThumb, yCenter, xThumb + thumbWidth, yCenter);
    }
    else
    {
        // Just call the base class for the demo
        LookAndFeel_V3::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}