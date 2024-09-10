void SnapGridPainter::draw (Graphics& g)
{
    if (backgroundFill.isNull() && snapShown)
    {
        backgroundFill = Image (Image::ARGB, snapGridSize, snapGridSize, true);

        Graphics g (backgroundFill);

        Colour col (Colours::black);

        if (snapGridSize > 2)
        {
            g.setColour (col.withAlpha (0.1f));
            g.drawRect (0, 0, snapGridSize + 1, snapGridSize + 1);
        }

        g.setColour (col.withAlpha (0.2f));
        g.setPixel (0, 0);
    }

    if (backgroundFill.isValid())
    {
        g.setTiledImageFill (backgroundFill, 0, 0, 1.0f);
        g.fillAll();
    }
}