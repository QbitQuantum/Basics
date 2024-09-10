int main(int argc, char *argv[]) {
    int server_coid, self_coid, chid, rcvid;
    struct reg_msg msg;

    setvbuf (stdout, NULL, _IOLBF, 0);

    /* look for server */
    server_coid = name_open( RECV_NAME, 0 );
    while( server_coid == -1 )
    {
        sleep(1);
        server_coid = name_open( RECV_NAME, 0 );
    }

    chid = ChannelCreate(0);
    if( -1 == chid)
    {
        perror( PROGNAME "ChannelCreate");
        exit( EXIT_FAILURE );
    }
    self_coid = ConnectAttach( 0, 0, chid, _NTO_SIDE_CHANNEL, 0 );
    if( -1 == self_coid )
    {
        perror( PROGNAME "ConnectAttach");
        exit( EXIT_FAILURE );
    }

    msg.type = REG_MSG;

    /* class: Initialize the sigevent structure (msg.ev) in the message
     * to be sent to the server.
     */

    if (MsgSend( server_coid, &msg, sizeof( msg ), NULL, 0 ) == -1)
    {
        perror(PROGNAME "MsgSend");
        exit( EXIT_FAILURE );
    }

    while( 1 )
    {
        rcvid = MsgReceive( chid, &recv_buf, sizeof(recv_buf), NULL );
        if( -1 == rcvid )
        {
            perror(PROGNAME "MsgReceive");
            continue;
        }
        if ( 0 == rcvid )
        {
            if (MY_PULSE_CODE == recv_buf.pulse.code )
            {
                printf(PROGNAME "got my pulse\n");
            } else
            {
                printf(PROGNAME "got unexpected pulse with code %d\n",
                       recv_buf.pulse.code );
            }
            continue;
        }
        printf(PROGNAME "got unexpected message, type: %d\n", recv_buf.type );
        MsgError( rcvid, ENOSYS );
    }
}