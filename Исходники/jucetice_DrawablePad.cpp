//==============================================================================
void DrawablePad::drawButtonBackground (Graphics& g,
                                        Button& button,
                                        const Colour& backgroundColour,
                                        bool isMouseOverButton,
                                        bool isButtonDown)
{
    const int width = button.getWidth();
    const int height = button.getHeight();

    const float indent = 2.0f;
    const int cornerSize = jmin (roundFloatToInt (width * roundness),
                                 roundFloatToInt (height * roundness));

    Colour bc (backgroundColour);
    if (isMouseOverButton)
    {
        if (isButtonDown)
            bc = bc.brighter();
        else if (bc.getBrightness() > 0.5f)
            bc = bc.darker (0.1f);
        else
            bc = bc.brighter (0.1f);
    }

    g.setColour (bc);

    if (hex)
    {
        g.fillPath (hexpath);

        g.setColour (bc.contrasting().withAlpha ((isMouseOverButton) ? 0.6f : 0.4f));
        g.strokePath (hexpath, PathStrokeType ((isMouseOverButton) ? 2.0f : 1.4f));
    }
    else
    {
        Path p;
        p.addRoundedRectangle (indent, indent,
                               width - indent * 2.0f,
                               height - indent * 2.0f,
                               (float) cornerSize);
        g.fillPath (p);

        g.setColour (bc.contrasting().withAlpha ((isMouseOverButton) ? 0.6f : 0.4f));
        g.strokePath (p, PathStrokeType ((isMouseOverButton) ? 2.0f : 1.4f));
    }
}