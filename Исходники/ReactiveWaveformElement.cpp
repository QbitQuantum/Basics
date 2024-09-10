void ReactiveWaveformElement::paint(juce::Graphics &g)
{
    g.saveState();
    g.setColour(colour());
    g.strokePath(path, PathStrokeType(lineThickness()));
    
    if (fill)
    {
        g.setColour(fillColour());
        g.fillPath(path);
    }
    
    if (clip)
    {
        g.reduceClipRegion(path);
    }
    
    GraphicsElement::paint(g);
    g.restoreState();
}