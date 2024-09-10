RunLoop::Timer::Timer(Clock::time_point& fireDate, Clock::duration& interval, TimerFn fn) : _fn(fn)
{
    using namespace std::chrono;
    
    if ( ::pipe(_pipeFDs) != 0 )
        throw std::system_error(errno, std::system_category(), "pipe() failed for Timer");
    
    struct sigevent ev;
    ev.sigev_signo = SIGALRM;
    ev.sigev_notify = SIGEV_THREAD;
    ev.sigev_value.sival_int = _pipeFDs[1];
    ev.sigev_notify_function = &_timer_handler;
    ev.sigev_notify_attributes = nullptr;
    ev.sigev_notify_thread_id = 0;
    
    if ( ::timer_create(CLOCK_REALTIME, &ev, &_timer) != 0 )
    {
        ::close(_pipeFDs[0]);
        ::close(_pipeFDs[1]);
        throw std::system_error(errno, std::system_category(), "timer_create() failed");
    }
    
    struct itimerspec its;
    its.it_value.tv_sec = duration_cast<seconds>(fireDate.time_since_epoch()).count();
    its.it_value.tv_nsec = duration_cast<nanoseconds>(fireDate.time_since_epoch()).count() % std::nano().den;
    its.it_interval.tv_sec = duration_cast<seconds>(interval).count();
    its.it_interval.tv_nsec = duration_cast<nanoseconds>(interval).count() % std::nano().den;
    
    // fireDate is an absolute time, not an interval relative to now()
    if ( ::timer_settime(_timer, TIMER_ABSTIME, &its, NULL) == -1 )
    {
        ::close(_pipeFDs[0]);
        ::close(_pipeFDs[1]);
        ::timer_delete(_timer);
        throw std::system_error(errno, std::system_category(), "timer_settime() failed");
    }
}