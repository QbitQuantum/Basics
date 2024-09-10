void GraphNode::paint (Graphics& g)
{
    Array<bool> recordStatuses = editor->getRecordStatusArray();
    
    Path recordPath;
    
    const int numRecordStatuses = recordStatuses.size();
    for (int i = 0; i < numRecordStatuses; ++i)
    {
        float stepSize      = 2 * float_Pi / numRecordStatuses;
        float startRadians  = stepSize * i;
        float endRadians    = startRadians + stepSize;
        
        if (recordStatuses[i])
            recordPath.addPieSegment (0, 0, 20, 20, startRadians, endRadians, 0.5);
    }
    
    g.setColour (Colours::red);
    g.fillPath (recordPath);
    
    g.setColour (isMouseOver ? Colours::yellow : editor->getBackgroundColor());
    g.fillEllipse (2, 2, 16, 16);
    
    g.drawText (getName(), 25, 0, getWidth() - 25, 20, Justification::left, true);
}