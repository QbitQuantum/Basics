bool SockSpring::HandleBind(SockPoller *binder)
{
    bool result = false;
#if defined(LNE_WIN32)
    iocp_data_.child = socket(skpad_.family(), SOCK_STREAM, IPPROTO_TCP);
    if(iocp_data_.child != INVALID_SOCKET) {
#else
    int flags = fcntl(skpad_.socket(), F_GETFL);
    if(flags >= 0 && fcntl(skpad_.socket(), F_SETFL, flags | O_NONBLOCK) == 0) {
#endif
        set_poller(binder);
#if defined(LNE_WIN32)
        if(CreateIoCompletionPort(reinterpret_cast<HANDLE>(skpad_.socket()), poller()->Handle(), static_cast<ULONG_PTR>(skpad_.socket()), 0) != NULL) {
            DWORD bytes;
            if(AcceptEx(skpad_.socket(), iocp_data_.child, iocp_data_.address, 0, 0, sizeof(iocp_data_.address), &bytes, &iocp_data_)
                    || WSAGetLastError() == ERROR_IO_PENDING)
                result = true;
        }
#elif defined(LNE_LINUX)
        if(epoll_ctl(poller()->Handle(), EPOLL_CTL_ADD, skpad_.socket(), &epoll_data_) == 0)
            result = true;
#elif defined(LNE_FREEBSD)
        struct kevent kev[1];
        EV_SET(&kev[0], skpad_.socket(), EVFILT_READ, EV_ADD, 0, 0, static_cast<SockEventer *>(this));
        if(kevent(poller()->Handle(), kev, 1, NULL, 0, NULL) == 0)
            result = true;
#endif
    }
    if(!result)
        Clean();
    return result;
}

void SockSpring::HandleRead(void)
{
    AddRef();
    __HandleRead();
    Release();
}