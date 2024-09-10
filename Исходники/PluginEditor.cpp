//==============================================================================
void Ambix_encoderAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //g.fillAll (Colours::white);
    
    g.setGradientFill (ColourGradient (Colour (0xff4e4e4e),
                                       (float) (proportionOfWidth (0.6314f)), (float) (proportionOfHeight (0.5842f)),
                                       Colours::black,
                                       (float) (proportionOfWidth (0.1143f)), (float) (proportionOfHeight (0.0800f)),
                                       true));
    g.fillRect (0, 0, 330, 400);
    
    g.setColour (Colours::black);
    g.drawRect (0, 0, 330, 400, 1);
    
    g.setColour (Colour (0xff2b1d69));
    g.fillRoundedRectangle (165.0f, 310.0f, 154.0f, 77.0f, 4.0000f);
    
    g.setColour (Colours::white);
    g.setFont (Font (17.2000f, Font::bold));
    g.drawText ("AMBIX-ENCODER",
                -6, 2, 343, 30,
                Justification::centred, true);
    
    g.setColour (Colours::white);
    g.setFont (Font (10.0000f, Font::plain));
    g.drawText ("elevation",
                266, 29, 48, 16,
                Justification::centred, true);
    
    g.setColour (Colours::white);
    g.setFont (Font (10.0000f, Font::plain));
    g.drawText ("azimuth",
                216, 272, 48, 16,
                Justification::centredRight, true);
    
    g.setColour (Colours::white);
    g.setFont (Font (10.0000f, Font::plain));
    g.drawText ("size",
                31, 382, 23, 16,
                Justification::centredRight, true);
    
    g.setColour (Colours::white);
    g.setFont (Font (10.0000f, Font::plain));
    g.drawText ("max speed",
                206, 372, 57, 16,
                Justification::centredRight, true);
    
#if INPUT_CHANNELS > 1
    g.setColour (Colours::white);
    g.setFont (Font (10.0000f, Font::plain));
    g.drawText ("multiple source width",
                61, 382, 95, 16,
                Justification::centredRight, true);
#endif
    
    g.setColour (Colour (0xff2b1d69));
    g.fillRoundedRectangle (24.0f, 310.0f, 226.0f, 43.0f, 4.0000f);
    
    g.setColour (Colours::white);
    g.setFont (Font (10.0000f, Font::plain));
    g.drawText ("elevation move",
                219, 338, 81, 16,
                Justification::centredRight, true);
    
    g.setColour (Colours::white);
    g.setFont (Font (10.0000f, Font::plain));
    g.drawText ("azimuth move",
                59, 338, 81, 16,
                Justification::centredRight, true);

    
    /* Version text */
    g.setColour (Colours::white);
    g.setFont (Font (10.00f, Font::plain));
    String version_string;
    version_string << "v" << QUOTE(VERSION);
    g.drawText (version_string,
                getWidth()-51, getHeight()-11, 50, 10,
                Justification::bottomRight, true);
    
    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}