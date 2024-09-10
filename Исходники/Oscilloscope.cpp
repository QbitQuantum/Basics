void Oscilloscope::paint(juce::Graphics &g)
{
    g.fillAll (Colours::white);
    
    Path path;
    
    float xOffset = 21.f;
    float yOffset = 120.f;
    
    Rectangle<float> rect = logoPath.getBounds();
    Rectangle<int> rect2 = getLocalBounds();
    
    g.setColour (Colours::black);
    g.fillPath (logoPath, RectanglePlacement (RectanglePlacement::stretchToFit)
                .getTransformToFit (logoPath.getBounds(),
                                    getLocalBounds().toFloat()));
    

    // Horizontal zero line.
    path.addLineSegment(Line<float> (xOffset, yOffset, getLocalBounds().getWidth() - xOffset, yOffset), 1.);
    
    g.setColour (Colours::lightgrey);
    g.fillPath (path);
    
    float xIncrement = (getLocalBounds().getWidth() - 2 * xOffset) / (UIConstants::NUMBER_SCOPE_POINTS - 1);
    
    // Now iterate over points.
    int count = 0;
    float alpha = 0;
    for (auto& points : allPoints)
    {
        if ((currentPointsIndex - count + UIConstants::NUMBER_SCOPE_BUFFERS) % UIConstants::NUMBER_SCOPE_BUFFERS == 0)
        {
            // Current array is 'brightest'
            alpha = 1;
        } else
        {
            // Set older immediately to less than 0.5 alpha.
            alpha = 0.3 - ((currentPointsIndex - count + UIConstants::NUMBER_SCOPE_BUFFERS) % UIConstants::NUMBER_SCOPE_BUFFERS) * 0.03 ;
        }
        
//        g.setColour(Colour::fromFloatRGBA(0, 255 , 0, alpha)) ;
        g.setColour(scopeTraceColour.withAlpha(alpha));
        path.clear();

        float x = 0;
        path.startNewSubPath(xOffset, yOffset);
        for (auto& point : points)
        {
//            g.setPixel(x + xOffset, yOffset - 30 * point.x); // point.x in this case is the right value of the stereo pair.
            path.lineTo(x + xOffset, yOffset - 30 * point.x);
            x += xIncrement;
        }
//        path.closeSubPath();
        g.strokePath (path, PathStrokeType (1.0f));
        count++;
        
    }

    
}