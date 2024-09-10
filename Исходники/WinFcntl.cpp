int thrift_poll(THRIFT_POLLFD *fdArray, ULONG nfds, INT timeout)
{
    return WSAPoll(fdArray, nfds, timeout);
}