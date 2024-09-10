void
TFeedbackView::DoFeedback( const TEventArgs& inArgs )
{
    const GenericSignal& signal = *inArgs.signal;
    float               xNormalized = 0.5,
                        yNormalized = 0.5,
                        bNormalized = 1.0;
    int                 actualChannels = signal.Channels();

    if( xChannel >= 0 && xChannel < actualChannels )
        xNormalized = ( signal( xChannel, 0 ) + 100.0 ) / 200.0;
    if( yChannel >= 0 && yChannel < actualChannels )
        yNormalized = ( signal( yChannel, 0 ) + 100.0 ) / 200.0;
    if( bChannel >= 0 && bChannel < actualChannels )
        bNormalized = ( - signal( bChannel, 0 ) + 100.0 ) / 200.0;

    xNormalized = MAX( 0.0, MIN( xNormalized, 1.0 ) );
    yNormalized = MAX( 0.0, MIN( yNormalized, 1.0 ) );
    bNormalized = MAX( 0.0, MIN( bNormalized, 1.0 ) );

    switch( visFBMode )
    {
        case 0: // none
            break;
        case 1: // cursor from file
        case 2: // ball
#ifdef PERUVIAN_BRIGHTNESS_HACK
        case 3: // brightness
#endif // PERUVIAN_BRIGHTNESS_HACK
            {
                float   xPos = xNormalized,
                        yPos = yNormalized,
                        brightness = bNormalized;
                unsigned short  curArtifactState = artifact.GetStateValue();

                if( SUPPRESS_CURSOR_BIT( inArgs.targetCode ) )
                {
                    TGUIFeedbackView::HideCursor();
                    if( curArtifactState == 1 )
                        TGUIFeedbackView::InvertCursor();
                    TGUIFeedbackView::SetCursorCoordinates( xPos, yPos, brightness );
                }
                else
                {
                    if( curArtifactState == 1 )
                        TGUIFeedbackView::InvertCursor();
                    TGUIFeedbackView::SetCursorCoordinates( xPos, yPos, brightness );
                    TGUIFeedbackView::ShowCursor();
                }
            }
            break;
        default:
            assert( false );
    }

    switch( audFBMode )
    {
        case 0: // none
            break;
        case 1: // MIDI
            if( !SUPPRESS_CURSOR_BIT( inArgs.targetCode ) )
            {
                // curNote is the note in the current scale's units.
                int curNote = ROUND( ( 0.5 - yNormalized )  // We add 1 to get full octaves.
                                        * ( gmFBInterval * ( float )scaleLength + 1 ) ),
                    curMidiNote = lastMidiNote;
                if( curNote > lastNote || curMidiNote < 1 /* For the very first note, use the upScale */ )
                {
                    curMidiNote = upScale[ MOD( curNote, scaleLength ) ] + 12 * DIV( curNote, scaleLength ) + gmFBCenterNote;
                    if( curMidiNote > 127 )
                        curMidiNote = 127;
                }
                else if( curNote < lastNote )
                {
                    curMidiNote = downScale[ MOD( curNote, scaleLength ) ] + 12 * DIV( curNote, scaleLength ) + gmFBCenterNote;
                    if( curMidiNote < 1 )
                        curMidiNote = 1;
                }
                midiPlayer->Play( curMidiNote );
                lastMidiNote = curMidiNote;
                lastNote = curNote;
            }
            break;
#ifdef USE_WAVE_SYNTH
        case 2: // continuous synth
            if( !SUPPRESS_CURSOR_BIT( inArgs.targetCode ) )
            {
              float centerFreq = 440.0 * pow( 2.0, ( gmFBCenterNote - 69 ) / 12.0 ),
                    freq = centerFreq * pow( 2.0, ( 0.5 - yNormalized ) * gmFBInterval );
              waveSynth->SetPitch( freq );
              waveSynth->Play();
            }
            else
              waveSynth->Stop();
            break;
#endif // USE_WAVE_SYNTH
        default:
            assert( false );
    }
}