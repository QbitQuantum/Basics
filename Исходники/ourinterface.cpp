int OurInterface::closeVirtualChannel()
{
    /* channel must be opened first */
    if (!channel)
        return -1;

    WTSVirtualChannelClose(channel);
    return 0;
}