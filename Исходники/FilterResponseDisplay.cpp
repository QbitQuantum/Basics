void FilterResponseDisplay::paint(Graphics& g)
{
    float width = (float) getWidth();
    float height = (float) getHeight();
    
    g.setColour(displayBackgroundColor);
    g.fillRect(0.0, 0.0, width, height);
    
    magnitudeResponsePath.clear();
    
    int filterType = filterToUse->getFilterType();
    switch (filterType) {
        case AudioFilter::filterTypeList::LowPass:
            drawLowpass();
            break;
        case AudioFilter::filterTypeList::HighPass:
            drawHighpass();
            break;
    }

    //Close the response path drawn
    magnitudeResponsePath.closeSubPath();
    
    g.setColour(magResponseColour);
    g.strokePath(magnitudeResponsePath, PathStrokeType(filterPathThickness));
    
    /*
       Fill area under/inside path with same colour at a lower alpha / highlight value.
       Try setting magResponseColour.withAlpha value to different values to get a fill shade you like.
     */
    g.setColour(magResponseColour.withAlpha((uint8) 0x9a));
    g.fillPath(magnitudeResponsePath);
    
}