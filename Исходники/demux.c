static void ResetTime( demux_t *p_demux, int64_t i_time )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    vlc_tick_t t;

    if( p_sys->ic->start_time == (int64_t)AV_NOPTS_VALUE || i_time < 0 )
    {
        t = VLC_TICK_INVALID;
    }
    else
    {
#if CLOCK_FREQ == AV_TIME_BASE
        t = FROM_AV_TS(i_time);
#else
        lldiv_t q = lldiv( i_time, AV_TIME_BASE );
        t = vlc_tick_from_sec(q.quot) + FROM_AV_TS(q.rem);
#endif

        if( t == VLC_TICK_INVALID )
            t = VLC_TICK_0;
    }

    p_sys->i_pcr = t;
    for( unsigned i = 0; i < p_sys->i_tracks; i++ )
        p_sys->tracks[i].i_pcr = VLC_TICK_INVALID;

    if( t != VLC_TICK_INVALID )
    {
        es_out_Control( p_demux->out, ES_OUT_SET_NEXT_DISPLAY_TIME, t );
        UpdateSeekPoint( p_demux, t );
    }
}