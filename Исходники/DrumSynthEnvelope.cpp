//==============================================================================
void DrumSynthEnvelope::paint (Graphics& g)
{
    const int dotSize = MAX_ENVELOPE_DOT_SIZE;
    const int halfDotSize = dotSize / 2;

    g.fillAll (Colour (0x47ffffff));

    Path myPath;
    myPath.startNewSubPath (0, points[0][1]);
    for (int i = 1; i < MAX_ENVELOPE_POINTS; i++)
        myPath.lineTo (points[i][0], points[i][1]);

    g.setColour (Colours::white);
    g.strokePath (myPath, PathStrokeType (2.0f));

    g.setColour (Colours::black);
    for (int i = 0; i < MAX_ENVELOPE_POINTS; i++)
    {
        int x = (int) (points[i][0]);
        int y = (int) (points[i][1]);
        
        g.setColour (Colours::white);
        g.fillEllipse (x - halfDotSize, y - halfDotSize, dotSize, dotSize);
        
        if (draggingPoint == i) {
            g.setColour (Colours::red);
            g.drawEllipse (x - halfDotSize, y - halfDotSize, dotSize, dotSize, 2);
        } else {
            g.setColour (Colours::black);
            g.drawEllipse (x - halfDotSize, y - halfDotSize, dotSize, dotSize, 1);
        }