void MyLookAndFeel::drawRotarySlider(Graphics& g,
                                     int x, int y,
                                     int width, int height,
                                     float sliderPos,
                                     const float rotaryStartAngle,
                                     const float rotaryEndAngle,
                                     Slider& /*slider*/)
{
    const float radius = jmin (width / 2, height / 2) - 2.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    //const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
    //const float zeroPos = rotaryStartAngle + std::abs((float)slider.getMinimum() / ((float)slider.getMaximum() - (float)slider.getMinimum())) * (rotaryEndAngle - rotaryStartAngle);

    Path p;

    PathStrokeType (rw * 0.01f).createStrokedPath (p, p);

    p.addLineSegment (Line<float>(0.0f, -radius * 0.5f, 0.00f, -radius), rw * 0.08f);

    g.setColour (Colours::white.withAlpha (1.0f));

    g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));

    g.setColour (Colours::black.withAlpha (0.7f));
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
}