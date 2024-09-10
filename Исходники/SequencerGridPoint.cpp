void SequencerGridPoint::paint (Graphics &g)
{
    thePath.clear();
    
    if (status == 0)
        g.setColour(Colours::transparentWhite); //off
    else //1-127
    {
        /*ColourGradient seqGradient(Colours::white.withAlpha(float(status*(1.0/127.0))), (getWidth()*0.5),(getHeight()*0.5), AlphaTheme::getInstance()->foregroundColourLighter.withAlpha(float(status*(1.0/127.0))), (getWidth()*0.8),(getHeight()*0.8), true);
         g.setGradientFill(seqGradient);
         //g.fillEllipse((getWidth()*0.05), (getHeight()*0.05), (getWidth()*0.9), (getHeight()*0.9));
         //g.setColour(AlphaTheme::getInstance()->backgroundColour); //on*/
		
        float alphaValue = float(status*(1.0/127.0));
        if (alphaValue < 0)
            alphaValue = 0;
        else if (alphaValue > 1.0)
            alphaValue = 1;
        
		g.setColour(AlphaTheme::getInstance()->mainColour.withAlpha(alphaValue));
    }
	
    
	theWidth = getWidth() - 16;
	theWidth = theWidth / getWidth();
	
	
	thePath.addPieSegment(0, 0, getWidth(), getHeight(), startRadians, endRadians, theWidth);
    
    g.fillPath(thePath, getTransform());
    
}