TEST( SequencerController, Rewind )
{
    SequencerController* controller = new SequencerController();

    int minPosition                  = randomInt( 0, 44100 );
    int maxPosition                  = randomInt( 88200, 192000 );
    AudioEngine::min_buffer_position = minPosition;
    AudioEngine::max_buffer_position = maxPosition;

    controller->setBufferPosition( randomInt( AudioEngine::min_buffer_position + 1,
                                              AudioEngine::max_buffer_position - 1 ));

    controller->rewind();

    EXPECT_EQ( minPosition, AudioEngine::min_buffer_position )
        << "expected engine to have 'rewound'";

    delete controller;
}