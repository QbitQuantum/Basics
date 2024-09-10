//==============================================================================
void GraphComponent::nodePaint (GraphNodeComponent* node, Graphics& g)
{
    int width = node->getWidth(),
        height = node->getHeight();

    bool selected = selectedNodes.isSelected (node),
         locked = node->isLocked();

    // background
    Colour background; 
#if 0
    if (selected)
        background = findColour (GraphComponent::nodeBackBrightColourId);
    else
        background = findColour (GraphComponent::nodeBackColourId);
#endif
    background = node->getNodeColour ();
    
    if (selected)
        background = background.brighter (0.3f);

#if 0
    g.setColour (background);
    g.fillRect (0, 0, width, height);
#else
    g.setGradientFill (ColourGradient(background, 0.0f, 0.0f,
                                      background.darker (0.3f),
                                      0.0f,
                                      height - 1.0f,
                                      false));
    g.fillAll();
#endif

    // plugin text
    if (selected)
        g.setColour (findColour (GraphComponent::nodeTextBrightColourId));
    else
        g.setColour (findColour (GraphComponent::nodeTextColourId));

    String textToDisplay = node->getText ();
    if (textToDisplay != String::empty)
    {
        g.setFont (currentFont);
        
        if (leftToRight)
        {
            int stringWidth = currentFont.getStringWidth (textToDisplay);
            int offX = width / 2 - (int) currentFont.getHeight () / 2;
            int offY = height / 2 - stringWidth / 2 ;
            
            g.drawTextAsPath (textToDisplay,
                              AffineTransform::rotation (double_Pi / 2.0)
                                              .translated (offX, offY));
        }
        else
        {
            g.drawText (textToDisplay,
                        0, 0, width, height,
                        Justification::centred,
                        false);
        }
    }

    // border
    Colour borderColour; 
    if (selected)
        borderColour = findColour (GraphComponent::nodeBorderBrightColourId);
    else
        borderColour = findColour (GraphComponent::nodeBorderColourId);

    if (locked)
        borderColour = borderColour.overlaidWith (Colours::red.withAlpha (0.3f));

    g.setColour (borderColour);
    g.drawRect (0, 0, width, height, 2);
}