/*****************************************************************************
 * Run: main loop
 *****************************************************************************/
static void Run( intf_thread_t *p_intf )
{
    intf_sys_t *p_sys = p_intf->p_sys;

    for( ;; )
    {
        /* Wait for data */
        struct pollfd ufd = { .fd = p_sys->i_fd, .events = POLLIN, .revents = 0 };
        if( poll( &ufd, 1, -1 ) == -1 )
            break;

        /* Process */
        int canc = vlc_savecancel();
        Process( p_intf );
        vlc_restorecancel(canc);
    }
}

static int Process( intf_thread_t *p_intf )
{
    for( ;; )
    {
        char *code, *c;
        int i_ret = lirc_nextcode( &code );

        if( i_ret )
            return i_ret;

        if( code == NULL )
            return 0;

        while( vlc_object_alive( p_intf )
                && (lirc_code2char( p_intf->p_sys->config, code, &c ) == 0)
                && (c != NULL) )
        {
            vlc_value_t keyval;

            if( !strncmp( "key-", c, 4 ) )
            {
                keyval.i_int = config_GetInt( p_intf, c );
                var_Set( p_intf->p_libvlc, "key-pressed", keyval );
            }
            else if( !strncmp( "menu ", c, 5)  )
            {
                if( !strncmp( c, "menu on", 7 ) ||
                    !strncmp( c, "menu show", 9 ))
                    osd_MenuShow( VLC_OBJECT(p_intf) );
                else if( !strncmp( c, "menu off", 8 ) ||
                         !strncmp( c, "menu hide", 9 ) )
                    osd_MenuHide( VLC_OBJECT(p_intf) );
                else if( !strncmp( c, "menu up", 7 ) )
                    osd_MenuUp( VLC_OBJECT(p_intf) );
                else if( !strncmp( c, "menu down", 9 ) )
                    osd_MenuDown( VLC_OBJECT(p_intf) );
                else if( !strncmp( c, "menu left", 9 ) )
                    osd_MenuPrev( VLC_OBJECT(p_intf) );
                else if( !strncmp( c, "menu right", 10 ) )
                    osd_MenuNext( VLC_OBJECT(p_intf) );
                else if( !strncmp( c, "menu select", 11 ) )
                    osd_MenuActivate( VLC_OBJECT(p_intf) );
                else
                {
                    msg_Err( p_intf, "Please provide one of the following parameters:" );
                    msg_Err( p_intf, "[on|off|up|down|left|right|select]" );
                    break;
                }
            }
            else
            {
                msg_Err( p_intf, "this doesn't appear to be a valid keycombo lirc sent us. Please look at the doc/lirc/example.lirc file in VLC" );
                break;
            }
        }
        free( code );
    }
}