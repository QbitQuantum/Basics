void socket_watcher_thread(void *arg)
{
    FILETIME prev_time;
    GetSystemTimeAsFileTime(&prev_time);

    for (;;) {
        const DWORD ms = 100;

        EnterCriticalSection(&m_watcher.queue_lock);
        if (m_watcher.queue_head != m_watcher.queue_tail) {
            pubnub_t *pbp = m_watcher.queue_apb[m_watcher.queue_tail++];
            LeaveCriticalSection(&m_watcher.queue_lock);
            if (pbp != NULL) {
                pubnub_mutex_lock(pbp->monitor);
                pbnc_fsm(pbp);
                pubnub_mutex_unlock(pbp->monitor);
            }
            EnterCriticalSection(&m_watcher.queue_lock);
            if (m_watcher.queue_tail == m_watcher.queue_size) {
                m_watcher.queue_tail = 0;
            }
        }
        LeaveCriticalSection(&m_watcher.queue_lock);

        EnterCriticalSection(&m_watcher.mutw);
        if (0 == m_watcher.apoll_size) {
            LeaveCriticalSection(&m_watcher.mutw);
            continue;
        }
        {
            int rslt = WSAPoll(m_watcher.apoll, m_watcher.apoll_size, ms);
            if (SOCKET_ERROR == rslt) {
                /* error? what to do about it? */
                PUBNUB_LOG_WARNING("poll size = %d, error = %d\n", m_watcher.apoll_size, WSAGetLastError());
            }
            else if (rslt > 0) {
                size_t i;
                size_t apoll_size = m_watcher.apoll_size;
                for (i = 0; i < apoll_size; ++i) {
                    if (m_watcher.apoll[i].revents & (POLLIN | POLLOUT)) {
                        pubnub_t *pbp = m_watcher.apb[i];
                        pubnub_mutex_lock(pbp->monitor);
                        pbnc_fsm(pbp);
                        if (apoll_size == m_watcher.apoll_size) {
                            if (m_watcher.apoll[i].events == POLLOUT) {
                                if ((pbp->state == PBS_WAIT_DNS_RCV) ||
                                    (pbp->state >= PBS_RX_HTTP_VER)) {
                                    m_watcher.apoll[i].events = POLLIN;
                                }
                            }
                            else {
                                if ((pbp->state > PBS_WAIT_DNS_RCV) &&
                                    (pbp->state < PBS_RX_HTTP_VER)) {
                                    m_watcher.apoll[i].events = POLLOUT;
                                }
                            }
                        }
                        else {
                            PUBNUB_ASSERT_OPT(apoll_size == m_watcher.apoll_size + 1);
                            apoll_size = m_watcher.apoll_size;
                            --i;
                        }
                        pubnub_mutex_unlock(pbp->monitor);
                    }
                }
            }
        }
        if (PUBNUB_TIMERS_API) {
            FILETIME current_time;
            int elapsed;
            GetSystemTimeAsFileTime(&current_time);
            elapsed = elapsed_ms(prev_time, current_time);
            if (elapsed > 0) {
                pubnub_t *expired = pubnub_timer_list_as_time_goes_by(&m_watcher.timer_head, elapsed);
                while (expired != NULL) {
                    pubnub_t *next = expired->next;

                    pubnub_mutex_lock(expired->monitor);
                    pbnc_stop(expired, PNR_TIMEOUT);
                    pubnub_mutex_unlock(expired->monitor);

                    expired->next = NULL;
                    expired->previous = NULL;
                    expired = next;
                }
                prev_time = current_time;
            }
        }

        LeaveCriticalSection(&m_watcher.mutw);
    }
}