static void *Thread(void *data)
{
    demux_t *demux = data;
    demux_sys_t *sys = demux->p_sys;
    struct wl_display *display = sys->display;
    struct pollfd ufd[1];
    unsigned interval = lroundf(CLOCK_FREQ / (sys->rate * 1000.f));

    int canc = vlc_savecancel();
    vlc_cleanup_push(cleanup_wl_display_read, display);

    ufd[0].fd = wl_display_get_fd(display);
    ufd[0].events = POLLIN;

    for (;;)
    {
        if (DisplayError(demux, display))
            break;

        if (sys->es != NULL)
        {
            block_t *block = Shoot(demux);

            block->i_pts = block->i_dts = vlc_tick_now();
            es_out_SetPCR(demux->out, block->i_pts);
            es_out_Send(demux->out, sys->es, block);
        }

        while (wl_display_prepare_read(display) != 0)
            wl_display_dispatch_pending(display);
        wl_display_flush(display);
        vlc_restorecancel(canc);

        while (poll(ufd, 1, interval) < 0);

        canc = vlc_savecancel();
        wl_display_read_events(display);
        wl_display_dispatch_pending(display);
    }
    vlc_cleanup_pop();
    vlc_restorecancel(canc);
    return NULL;
}