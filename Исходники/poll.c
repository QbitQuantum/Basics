static apr_status_t impl_pollcb_poll(apr_pollcb_t *pollcb,
                                     apr_interval_time_t timeout,
                                     apr_pollcb_cb_t func,
                                     void *baton)
{
    int ret;
    apr_status_t rv = APR_SUCCESS;
    apr_uint32_t i;

    if (timeout > 0) {
        timeout /= 1000;
    }
#ifdef WIN32
    ret = WSAPoll(pollcb->pollset.ps, pollcb->nelts, (int)timeout);
#else
    ret = poll(pollcb->pollset.ps, pollcb->nelts, timeout);
#endif
    if (ret < 0) {
        return apr_get_netos_error();
    }
    else if (ret == 0) {
        return APR_TIMEUP;
    }
    else {
        for (i = 0; i < pollcb->nelts; i++) {
            if (pollcb->pollset.ps[i].revents != 0) {
                apr_pollfd_t *pollfd = pollcb->copyset[i];

                if ((pollcb->flags & APR_POLLSET_WAKEABLE) &&
                    pollfd->desc_type == APR_POLL_FILE &&
                    pollfd->desc.f == pollcb->wakeup_pipe[0]) {
                    apr_poll_drain_wakeup_pipe(pollcb->wakeup_pipe);
                    return APR_EINTR;
                }

                pollfd->rtnevents = get_revent(pollcb->pollset.ps[i].revents);                    
                rv = func(baton, pollfd);
                if (rv) {
                    return rv;
                }
            }
        }
    }
    return rv;
}