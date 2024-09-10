bool EventDispatcherEPollPrivate::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    Q_Q(EventDispatcherEPoll);

    const bool exclude_notifiers = (flags & QEventLoop::ExcludeSocketNotifiers);
    const bool exclude_timers    = (flags & QEventLoop::X11ExcludeTimers);

    exclude_notifiers && disableSocketNotifiers(true);
    exclude_timers    && disableTimers(true);

    m_interrupt = false;
    Q_EMIT q->awake();

    bool result = q->hasPendingEvents();

    QCoreApplication::sendPostedEvents();

    bool can_wait =
            !m_interrupt
            && (flags & QEventLoop::WaitForMoreEvents)
            && !result
            ;

    int n_events = 0;

    if (!m_interrupt) {
        int timeout = 0;

        if (!exclude_timers && !m_zero_timers.isEmpty()) {
            QVector<ZeroTimer*> timers;
            auto it = m_zero_timers.constBegin();
            while (it != m_zero_timers.constEnd()) {
                ZeroTimer *data = it.value();
                data->ref();
                timers.push_back(data);
                ++it;
            }

            for (ZeroTimer *data : timers) {
                if (data->canProcess() && data->active) {
                    data->active = false;

                    QTimerEvent event(data->timerId);
                    QCoreApplication::sendEvent(data->object, &event);

                    result = true;
                    if (!data->active) {
                        data->active = true;
                    }
                }

                data->deref();
            }
        }

        if (can_wait && !result) {
            Q_EMIT q->aboutToBlock();
            timeout = -1;
        }

        struct epoll_event events[10024];
        do {
            n_events = epoll_wait(m_epoll_fd, events, 10024, timeout);
        } while (Q_UNLIKELY(-1 == n_events && errno == EINTR));

        for (int i = 0; i < n_events; ++i) {
            struct epoll_event &e = events[i];
            auto data = static_cast<EpollAbastractEvent*>(e.data.ptr);
            data->ref();
        }

        for (int i = 0; i < n_events; ++i) {
            struct epoll_event &e = events[i];
            auto data = static_cast<EpollAbastractEvent*>(e.data.ptr);
            if (data->canProcess()) {
                data->process(e.events);
            }

            data->deref();
        }
    }

    exclude_notifiers && disableSocketNotifiers(false);
    exclude_timers    && disableTimers(false);

    return result || n_events > 0;
}