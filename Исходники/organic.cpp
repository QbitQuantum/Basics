organicInstrument::organicInstrument( InstrumentTrack * _instrument_track ) :
    Instrument( _instrument_track, &organic_plugin_descriptor ),
    m_modulationAlgo( Oscillator::SignalMix, Oscillator::SignalMix, Oscillator::SignalMix),
    m_fx1Model( 0.0f, 0.0f, 0.99f, 0.01f , this, tr( "Distortion" ) ),
    m_volModel( 100.0f, 0.0f, 200.0f, 1.0f, this, tr( "Volume" ) )
{
    m_numOscillators = 8;

    m_osc = new OscillatorObject*[ m_numOscillators ];
    for (int i=0; i < m_numOscillators; i++)
    {
        m_osc[i] = new OscillatorObject( this, i );
        m_osc[i]->m_numOscillators = m_numOscillators;

        // Connect events
        connect( &m_osc[i]->m_oscModel, SIGNAL( dataChanged() ),
                 m_osc[i], SLOT ( oscButtonChanged() ) );
        connect( &m_osc[i]->m_harmModel, SIGNAL( dataChanged() ),
                 m_osc[i], SLOT( updateDetuning() ) );
        connect( &m_osc[i]->m_volModel, SIGNAL( dataChanged() ),
                 m_osc[i], SLOT( updateVolume() ) );
        connect( &m_osc[i]->m_panModel, SIGNAL( dataChanged() ),
                 m_osc[i], SLOT( updateVolume() ) );
        connect( &m_osc[i]->m_detuneModel, SIGNAL( dataChanged() ),
                 m_osc[i], SLOT( updateDetuning() ) );

        m_osc[i]->updateVolume();

    }

    /*	m_osc[0]->m_harmonic = log2f( 0.5f );	// one octave below
    	m_osc[1]->m_harmonic = log2f( 0.75f );	// a fifth below
    	m_osc[2]->m_harmonic = log2f( 1.0f );	// base freq
    	m_osc[3]->m_harmonic = log2f( 2.0f );	// first overtone
    	m_osc[4]->m_harmonic = log2f( 3.0f );	// second overtone
    	m_osc[5]->m_harmonic = log2f( 4.0f );	// .
    	m_osc[6]->m_harmonic = log2f( 5.0f );	// .
    	m_osc[7]->m_harmonic = log2f( 6.0f );	// .*/

    if( s_harmonics == NULL )
    {
        s_harmonics = new float[ NUM_HARMONICS ];
        s_harmonics[0] = log2f( 0.5f );
        s_harmonics[1] = log2f( 0.75f );
        s_harmonics[2] = log2f( 1.0f );
        s_harmonics[3] = log2f( 2.0f );
        s_harmonics[4] = log2f( 3.0f );
        s_harmonics[5] = log2f( 4.0f );
        s_harmonics[6] = log2f( 5.0f );
        s_harmonics[7] = log2f( 6.0f );
        s_harmonics[8] = log2f( 7.0f );
        s_harmonics[9] = log2f( 8.0f );
        s_harmonics[10] = log2f( 9.0f );
        s_harmonics[11] = log2f( 10.0f );
        s_harmonics[12] = log2f( 11.0f );
        s_harmonics[13] = log2f( 12.0f );
        s_harmonics[14] = log2f( 13.0f );
        s_harmonics[15] = log2f( 14.0f );
        s_harmonics[16] = log2f( 15.0f );
        s_harmonics[17] = log2f( 16.0f );
    }

    for (int i=0; i < m_numOscillators; i++) {
        m_osc[i]->updateVolume();
        m_osc[i]->updateDetuning();
    }


    connect( engine::mixer(), SIGNAL( sampleRateChanged() ),
             this, SLOT( updateAllDetuning() ) );
}