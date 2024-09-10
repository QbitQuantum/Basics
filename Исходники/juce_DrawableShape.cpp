//==============================================================================
void DrawableShape::paint (Graphics& g)
{
    transformContextToCorrectOrigin (g);

    g.setFillType (mainFill.fill);
    g.fillPath (path);

    if (isStrokeVisible())
    {
        g.setFillType (strokeFill.fill);
        g.fillPath (strokePath);
    }
}