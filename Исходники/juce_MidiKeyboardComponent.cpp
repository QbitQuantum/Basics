void MidiKeyboardComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white.overlaidWith (findColour (whiteNoteColourId)));

    const Colour lineColour (findColour (keySeparatorLineColourId));
    const Colour textColour (findColour (textLabelColourId));

    int x, w, octave;

    for (octave = 0; octave < 128; octave += 12)
    {
        for (int white = 0; white < 7; ++white)
        {
            const int noteNum = octave + whiteNotes [white];

            if (noteNum >= rangeStart && noteNum <= rangeEnd)
            {
                const Rectangle<int> pos (getWhiteNotePos (noteNum));

                drawWhiteNote (noteNum, g, pos.getX(), pos.getY(), pos.getWidth(), pos.getHeight(),
                               state.isNoteOnForChannels (midiInChannelMask, noteNum),
                               mouseOverNotes.contains (noteNum), lineColour, textColour);
            }
        }
    }

    float x1 = 0.0f, y1 = 0.0f, x2 = 0.0f, y2 = 0.0f;

    if (orientation == verticalKeyboardFacingLeft)
    {
        x1 = getWidth() - 1.0f;
        x2 = getWidth() - 5.0f;
    }
    else if (orientation == verticalKeyboardFacingRight)
        x2 = 5.0f;
    else
        y2 = 5.0f;

    g.setGradientFill (ColourGradient (Colours::black.withAlpha (0.3f), x1, y1,
                                       Colours::transparentBlack, x2, y2, false));

    getKeyPos (rangeEnd, x, w);
    x += w;

    switch (orientation)
    {
        case horizontalKeyboard:            g.fillRect (0, 0, x, 5); break;
        case verticalKeyboardFacingLeft:    g.fillRect (getWidth() - 5, 0, 5, x); break;
        case verticalKeyboardFacingRight:   g.fillRect (0, 0, 5, x); break;
        default: break;
    }

    g.setColour (lineColour);

    switch (orientation)
    {
        case horizontalKeyboard:            g.fillRect (0, getHeight() - 1, x, 1); break;
        case verticalKeyboardFacingLeft:    g.fillRect (0, 0, 1, x); break;
        case verticalKeyboardFacingRight:   g.fillRect (getWidth() - 1, 0, 1, x); break;
        default: break;
    }

    const Colour blackNoteColour (findColour (blackNoteColourId));

    for (octave = 0; octave < 128; octave += 12)
    {
        for (int black = 0; black < 5; ++black)
        {
            const int noteNum = octave + blackNotes [black];

            if (noteNum >= rangeStart && noteNum <= rangeEnd)
            {
                getKeyPos (noteNum, x, w);
                Rectangle<int> pos;

                switch (orientation)
                {
                    case horizontalKeyboard:            pos.setBounds (x, 0, w, blackNoteLength); break;
                    case verticalKeyboardFacingLeft:    pos.setBounds (getWidth() - blackNoteLength, x, blackNoteLength, w); break;
                    case verticalKeyboardFacingRight:   pos.setBounds (0, getHeight() - x - w, blackNoteLength, w); break;
                    default: break;
                }

                drawBlackNote (noteNum, g, pos.getX(), pos.getY(), pos.getWidth(), pos.getHeight(),
                               state.isNoteOnForChannels (midiInChannelMask, noteNum),
                               mouseOverNotes.contains (noteNum), blackNoteColour);
            }
        }
    }
}