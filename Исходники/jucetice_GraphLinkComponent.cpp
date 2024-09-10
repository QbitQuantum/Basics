//==============================================================================
void GraphLinkComponent::paint (Graphics& g)
{
    Colour wireColour = Colours::black;
    if ((to != 0 && from != 0))
    {
        GraphNodeComponent* node = to->getParentGraphComponent ();
        wireColour = node->getConnectorColour (to, isMouseOverOrDragging());
    }
    else
    {
        if (to)
        {
            GraphNodeComponent* node = to->getParentGraphComponent ();
            wireColour = node->getConnectorColour (to, true);
        }
        else if (from)
        {
            GraphNodeComponent* node = from->getParentGraphComponent ();
            wireColour = node->getConnectorColour (from, true);
        }
    }

    g.setColour (wireColour);
    g.strokePath (path, PathStrokeType (lineThickness));