KMError VPoll::wait(uint32_t wait_ms)
{
#ifdef KUMA_OS_WIN
    int num_revts = WSAPoll(&poll_fds_[0], poll_fds_.size(), wait_ms);
#else
    int num_revts = poll(&poll_fds_[0], (nfds_t)poll_fds_.size(), wait_ms);
#endif
    if (-1 == num_revts) {
        if(EINTR == errno) {
            errno = 0;
        } else {
            KUMA_ERRTRACE("VPoll::wait, err="<<getLastError());
        }
        return KMError::INVALID_STATE;
    }

    // copy poll fds since event handler may unregister fd
    PollFdVector poll_fds = poll_fds_;
    
    int idx = 0;
    int last_idx = int(poll_fds.size() - 1);
    while(num_revts > 0 && idx <= last_idx) {
        if(poll_fds[idx].revents) {
            --num_revts;
            if(poll_fds[idx].fd < poll_items_.size()) {
                auto &item = poll_items_[poll_fds[idx].fd];
                auto revents = get_kuma_events(poll_fds[idx].revents);
                revents &= item.events;
                if (revents && item.cb) {
                    item.cb(revents, nullptr, 0);
                }
            }
        }
        ++idx;
    }
    return KMError::NOERR;
}