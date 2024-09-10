void NTLookAndFeel::drawTickBox(juce::Graphics &g, juce::Component &button, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown){
    
    auto& toggle = dynamic_cast<ToggleButton&>(button);
    
    if (toggle.getRadioGroupId() > 0) {
        auto rect = Rectangle<float>(x,y,w,h);
        rect.reduce(w * .2, h*.2);
        
        g.setColour(Colours::white);
        g.fillEllipse(rect);
        g.setColour(Colours::lightgrey);
        g.drawEllipse(rect,2);
        
        if (ticked) {
            rect.reduce(rect.getWidth() * .2,rect.getHeight() *.2);

            g.fillEllipse(rect);
        }
    }else{
        auto rect = Rectangle<float>(x,y,w,h);
        g.setColour(Colours::white);
        g.fillRect(rect);
        g.setColour(Colours::lightgrey);
        g.drawRect(rect,3);
        if (ticked) {
            rect.reduce(rect.getWidth() * .25,rect.getHeight() *.25);
            g.fillRect(rect);
        }

    }
    
    
}