/*****************************************************************************
 * Open: open the audio device
 *****************************************************************************
 * This function opens and setups Win32 waveOut
 *****************************************************************************/
static int Open( vlc_object_t *p_this )
{
    aout_instance_t *p_aout = (aout_instance_t *)p_this;
    vlc_value_t val;
    int i;

    /* Allocate structure */
    p_aout->output.p_sys = malloc( sizeof( aout_sys_t ) );

    if( p_aout->output.p_sys == NULL )
    {
        msg_Err( p_aout, "out of memory" );
        return VLC_EGENERIC;
    }

    p_aout->output.pf_play = Play;
    p_aout->b_die = VLC_FALSE;

    if( var_Type( p_aout, "audio-device" ) == 0 )
    {
        Probe( p_aout );
    }

    if( var_Get( p_aout, "audio-device", &val ) < 0 )
    {
        /* Probe() has failed. */
        free( p_aout->output.p_sys );
        return VLC_EGENERIC;
    }

    var_Create( p_aout, "waveout-float32", VLC_VAR_BOOL | VLC_VAR_DOINHERIT );

    /* Open the device */
    if( val.i_int == AOUT_VAR_SPDIF )
    {
        p_aout->output.output.i_format = VLC_FOURCC('s','p','d','i');

        if( OpenWaveOut( p_aout, VLC_FOURCC('s','p','d','i'),
                         p_aout->output.output.i_physical_channels,
                         aout_FormatNbChannels( &p_aout->output.output ),
                         p_aout->output.output.i_rate, VLC_FALSE )
            != VLC_SUCCESS )
        {
            msg_Err( p_aout, "cannot open waveout audio device" );
            free( p_aout->output.p_sys );
            return VLC_EGENERIC;
        }

        /* Calculate the frame size in bytes */
        p_aout->output.i_nb_samples = A52_FRAME_NB;
        p_aout->output.output.i_bytes_per_frame = AOUT_SPDIF_SIZE;
        p_aout->output.output.i_frame_length = A52_FRAME_NB;
        p_aout->output.p_sys->i_buffer_size =
            p_aout->output.output.i_bytes_per_frame;

        aout_VolumeNoneInit( p_aout );
    }
    else
    {
        if( val.i_int == AOUT_VAR_5_1 )
        {
            p_aout->output.output.i_physical_channels
                = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER
                   | AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT
                   | AOUT_CHAN_LFE;
        }
        else if( val.i_int == AOUT_VAR_2F2R )
        {
            p_aout->output.output.i_physical_channels
                = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT
                   | AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT;
        }
        else if( val.i_int == AOUT_VAR_MONO )
        {
            p_aout->output.output.i_physical_channels = AOUT_CHAN_CENTER;
        }
        else
        {
            p_aout->output.output.i_physical_channels
                = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT;
        }

        if( OpenWaveOutPCM( p_aout, &p_aout->output.output.i_format,
                            p_aout->output.output.i_physical_channels,
                            aout_FormatNbChannels( &p_aout->output.output ),
                            p_aout->output.output.i_rate, VLC_FALSE )
            != VLC_SUCCESS )
        {
            msg_Err( p_aout, "cannot open waveout audio device" );
            free( p_aout->output.p_sys );
            return VLC_EGENERIC;
        }

        /* Calculate the frame size in bytes */
        p_aout->output.i_nb_samples = FRAME_SIZE;
        aout_FormatPrepare( &p_aout->output.output );
        p_aout->output.p_sys->i_buffer_size = FRAME_SIZE *
            p_aout->output.output.i_bytes_per_frame;

        aout_VolumeSoftInit( p_aout );
    }


    waveOutReset( p_aout->output.p_sys->h_waveout );

    /* Allocate silence buffer */
    p_aout->output.p_sys->p_silence_buffer =
        malloc( p_aout->output.p_sys->i_buffer_size );
    if( p_aout->output.p_sys->p_silence_buffer == NULL )
    {
        free( p_aout->output.p_sys );
        msg_Err( p_aout, "out of memory" );
        return 1;
    }

    /* Zero the buffer. WinCE doesn't have calloc(). */
    memset( p_aout->output.p_sys->p_silence_buffer, 0,
            p_aout->output.p_sys->i_buffer_size );

    /* Now we need to setup our waveOut play notification structure */
    p_aout->output.p_sys->p_notif =
        vlc_object_create( p_aout, sizeof(notification_thread_t) );
    p_aout->output.p_sys->p_notif->p_aout = p_aout;
    p_aout->output.p_sys->event = CreateEvent( NULL, FALSE, FALSE, NULL );

    /* Then launch the notification thread */
    if( vlc_thread_create( p_aout->output.p_sys->p_notif,
                           "waveOut Notification Thread", WaveOutThread,
                           VLC_THREAD_PRIORITY_HIGHEST, VLC_FALSE ) )
    {
        msg_Err( p_aout, "cannot create WaveOutThread" );
    }

    /* We need to kick off the playback in order to have the callback properly
     * working */
    for( i = 0; i < FRAMES_NUM; i++ )
    {
        p_aout->output.p_sys->waveheader[i].dwFlags = WHDR_DONE;
        p_aout->output.p_sys->waveheader[i].dwUser = 0;
    }
    PlayWaveOut( p_aout, p_aout->output.p_sys->h_waveout,
                 &p_aout->output.p_sys->waveheader[0], NULL );

    return 0;
}