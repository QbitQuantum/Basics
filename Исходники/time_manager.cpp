uint Timer::State()
{
    if (request == buffer - 1) {
        uint now = Clock();
        delay = now - last;
        if (delay < kClockDelay) {
            last_buffer = buffer;
            buffer *= 2;
        }
        last = now;
        request = 0;
    } else
        ++request;
    return last + request * delay / last_buffer - begin;
}