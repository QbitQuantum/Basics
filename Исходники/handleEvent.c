void handleEvent(THREAD_ARG *arg)
{
    BYTE i=0;

    struct event_base* base = event_base_new();
    if (!base)
    {
        fprintf(stderr, "Could not initialize libevent!\n");
        exit(1);
    }
    eventarg.base = base;
    eventarg.UART0_fd = openUart("uart0");
    eventarg.CAN0_fd  = openCAN("can0");
    eventarg.output_socket = NULL;
    eventarg.GUIPipe_fd  = arg->GUIPipe_fd;
    eventarg.CTRLPipe_fd  = arg->CTRLPipe_fd;
    eventarg.UARTPipe_fd = arg->UARTPipe_fd;
    eventarg.lock = arg->lock;
    eventarg.cond = arg->cond;
    setEvent(base);
    for(i=0; i<MAX_CHANNEL; i++)
    {
        eventarg.timer_arg[i].channel = i+1;
        eventarg.timer_arg[i].channelTimer = event_new(base, -1, EV_TIMEOUT,
                                             cbChannelTimer, (void*)(&eventarg.timer_arg[i]));
    }
    event_base_dispatch(base);
}