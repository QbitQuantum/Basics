void FDStream::waitWrite(base::Time const& timeout)
{
    fd_set set;
    FD_ZERO(&set);
    FD_SET(m_fd, &set);

    timeval timeout_spec = { static_cast<time_t>(timeout.toSeconds()), timeout.toMicroseconds() % 1000000 };
    int ret = select(m_fd + 1, NULL, &set, NULL, &timeout_spec);
    if (ret < 0 && errno != EINTR)
        throw UnixError("waitWrite(): error in select()");
    else if (ret == 0)
        throw TimeoutError(TimeoutError::NONE, "waitWrite(): timeout");
}