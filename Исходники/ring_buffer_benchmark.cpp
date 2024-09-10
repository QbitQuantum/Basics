static int TestConsume(processor::RingBuffer<int, RingBufferSize>* ring_buffer) {

    int64_t prev_sequence = -1;
    int64_t next_sequence = -1;
    int num_events_processed = 0;
    while (true) {
        // Spin till a new sequence is available.
        while (next_sequence <= prev_sequence) {
            _mm_pause();
            next_sequence = ring_buffer->getProducerSequence();
        }
        // Process everything in the batch.
        for (int64_t index = prev_sequence + 1; index <= next_sequence; index++) {
            int entry = *(ring_buffer->get(index));
            assert(entry == index);
            ++num_events_processed;
        }
        // Mark events consumed.
        ring_buffer->markConsumed(next_sequence);
        prev_sequence = next_sequence;
        if (num_events_processed == kNumEventsToGenerate)
            break;
    }
    return 0;
}