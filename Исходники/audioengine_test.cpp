TEST( AudioEngine, OutputAtLoopStart )
{
    AudioEngine::test_program    = 3;   // help mocked OpenSL IO identify which test is running
    AudioEngine::test_successful = false;

    // setup sequencer

    std::vector<AudioChannel*>* channels = new std::vector<AudioChannel*>();
    BaseInstrument* instrument1 = new BaseInstrument();
    BaseInstrument* instrument2 = new BaseInstrument();

    // prepare engine environment

    SequencerController* controller = new SequencerController();
    controller->prepare( 11025, 44100, 120.0f, 4, 4 ); // 44.1 kHz, 4/4 time at 120 BPM w/ buffer size of 11025 samples
    controller->setTempoNow( 120.0f, 4, 4 );
    controller->rewind();

    // setup audio events

    // test is working at 88200 samples per bar (emulates 44.1 kHz sample rate at 120 BPM 4/4 time)
    // use a buffer size that is the size of an 8th note (11025 samples)

    AudioEngine::min_buffer_position = 0;
    AudioEngine::max_buffer_position = AudioEngine::samples_per_bar - 1;
    Sequencer::playing               = true;
    int bufferSize                   = AudioEngineProps::BUFFER_SIZE;

    // audioEvent1 start: 77175 end: 88199 (length: 11025)
    // audioEvent2 start: 0 end: 11024 (length: 11025)

    BaseAudioEvent* audioEvent1 = enqueuedAudioEvent( instrument1, bufferSize, 0, 16, 14 );
    BaseAudioEvent* audioEvent2 = enqueuedAudioEvent( instrument2, bufferSize, 0, 16, 0 );

    // fill event 1 and event 2 with values (are validated in mock_opensl_io)

    AudioBuffer* buffer1 = new AudioBuffer( 1, audioEvent1->getSampleLength() );
    AudioBuffer* buffer2 = new AudioBuffer( 1, audioEvent2->getSampleLength() );

    for ( int i = 0; i < buffer1->bufferSize; ++i )
        buffer1->getBufferForChannel( 0 )[ i ] = ( SAMPLE_TYPE ) -0.25;

    for ( int i = 0; i < buffer2->bufferSize; ++i )
        buffer2->getBufferForChannel( 0 )[ i ] = ( SAMPLE_TYPE ) +0.5;

    audioEvent1->setBuffer( buffer1, false );
    audioEvent2->setBuffer( buffer2, false );

    // test check if Sequencer returns events when loop is about to start
    // e.g. start offset is 88100 while there are 88200 samples in the measure / loop range
    // buffer size is 11025 samples, we expect to collect events at offsets 88100 to 88199
    // and events at offset 0 to 10924 (as we read ( max_buffer_position - startOffset ) + 1 ) samples from the start
    // of the requested range and can subtract this value from the bufferSize to calculate how many samples
    // we need to read from the start of the full Sequencer loop range, as such the calculation is:
    // ( 11025 - (( 88199 - 88100 ) + 1 )) == 10925 samples to read from start (which is min_buffer_position == 0 )

    // start the engine

    AudioEngine::bufferPosition = 88100;
    AudioEngine::volume         = 1;
    controller->setPlaying( true );
    AudioEngine::start();

    // evaluate results (assertions are made in mock_opensl_io.cpp)

    ASSERT_TRUE( AudioEngine::test_successful )
        << "expected test to be successful";

    EXPECT_EQ( 4, AudioEngine::test_program )
        << "expected test program to have incremented";

    // clean up

    controller->setPlaying( false );
    AudioEngine::render_iterations = 0;

    delete channels;
    delete controller;
    delete audioEvent1;
    delete audioEvent2;
    delete buffer1;
    delete buffer2;
    delete instrument1;
    delete instrument2;
}