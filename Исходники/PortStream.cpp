void PortStream::waitRead(base::Time const& timeout)
{
    if (!mPacketRead.data.empty())
        return;

    uint64_t sleep_time;
    int count;
    uint64_t full_timeout = timeout.toMicroseconds();
    if (full_timeout > 10000)
    {
        sleep_time = 10000;
        count = (full_timeout + sleep_time - 1) / sleep_time;
    }
    else
    {
        count = 1;
        sleep_time = full_timeout;
    }

    for (int i = 0; i < count; ++i)
    {
        if (mIn.read(mPacketRead, false) == RTT::NewData)
            return;
        usleep(sleep_time);
    }
    throw TimeoutError(TimeoutError::NONE, "waitRead(): timeout");
}