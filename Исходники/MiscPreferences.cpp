//------------------------------------------------------------------------------
void MiscPreferences::drawGroupComponentOutline(Graphics& g,
												int width,
												int height,
                                             	const String& text,
                                             	const Justification& position)
{
    const float textH = 15.0f;
    const float indent = 3.0f;
    const float textEdgeGap = 4.0f;
    float cs = 5.0f;

    Font f (textH, Font::bold);

    Path p;
    float x = indent;
    float y = f.getAscent() - 3.0f;
    float w = width - x * 2.0f;
    float h = height - y  - indent;
    cs = jmin (cs, w * 0.5f, h * 0.5f);
    const float cs2 = 2.0f * cs;

    float textW = jlimit (0.0f, f.getStringWidth (text) + textEdgeGap * 2.0f, w - cs2);
    float textX = cs + textEdgeGap;

    if (position.testFlags (Justification::verticallyCentred))
        textX = cs + (w - cs2 - textW) * 0.5f;
    else if (position.testFlags (Justification::right))
        textX = w - cs - textW - textEdgeGap;

    p.startNewSubPath (x + textX + textW, y);
    p.lineTo (x + w - cs, y);

    p.addArc (x + w - cs2, y, cs2, cs2, 0, float_Pi * 0.5f);
    p.lineTo (x + w, y + h - cs);

    p.addArc (x + w - cs2, y + h - cs2, cs2, cs2, float_Pi * 0.5f, float_Pi);
    p.lineTo (x + cs, y + h);

    p.addArc (x, y + h - cs2, cs2, cs2, float_Pi, float_Pi * 1.5f);
    p.lineTo (x, y + cs);

    p.addArc (x, y, cs2, cs2, float_Pi * 1.5f, float_Pi * 2.0f);
    p.lineTo (x + textX, y);

    g.setColour (textColour);
    g.strokePath (p, PathStrokeType (2.0f));

    g.setColour (textColour);
    g.setFont (f);
    g.drawText (text,
                roundFloatToInt (x + textX), 0,
                roundFloatToInt (textW),
                roundFloatToInt (textH),
                Justification::centred, true);
}