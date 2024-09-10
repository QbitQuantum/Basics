void poller::add(socket& sock)
{
    zpoller_add(self_, sock.self());
}