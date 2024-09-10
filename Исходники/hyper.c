static void
make_server_connections(void)
{
    int i, wait_time;

    /*
     * Try to open the menuserver socket, if I can not, then set a flag
     */

    if (open_server(MenuServerName) == -2) {
        fprintf(stderr, "(HyperDoc) Warning: Not connected to FriCAS Server!\n");
        MenuServerOpened = 0;
    } else {
        atexit(&clean_socket);
        MenuServerOpened = 1;
    }


    /*
     * If I have opened the MenuServer socket, then I should also try to open
     * the SpadServer socket, so I can send stuff right to SPAD.
     */

    if (MenuServerOpened) {

        /*
         * If I am a ht server, then I should not continue on unless I
         * establish some sort of connection
         */

        /*
         * Modified on 11/20 so that it prints an error message every ten for
         * ten tries at opeing the socket. If it fails all ten times, it
         * gives up and exits.
         */

        if (!is_fricas_server)
            wait_time = 2;
        else
            wait_time = 1000;

        for (i = 0, spad_socket = NULL; i < 2 && spad_socket == NULL; i++) {
            spad_socket = connect_to_local_server(SpadServer,
                                                  MenuServer, wait_time);
            if (is_fricas_server && spad_socket == NULL)
                fprintf(stderr, "(HyperDoc) Error opening FriCAS server. Retrying ...\n");
            else
                i = 11;
        }
        if (! spad_socket) {
            fprintf(stderr, "(HyperDoc) Couldn't connect to FriCAS server!\n");
            if (!is_fricas_server)
                MenuServerOpened = 0;
            else {
                fprintf(stderr, "(HyperDoc) Couldn't connect to FriCAS server!\n");
                exit(-1);
            }
        }
        else {

            /*
             * Do the same thing for the SessionServer
             */

            for (i = 0, session_server = NULL; i < 2 && session_server == NULL
                 ; i++) {
                session_server =
                    connect_to_local_server(SessionServer, MenuServer,
                                            wait_time);
                if (is_fricas_server && session_server == NULL) {
                    fprintf(stderr,
                            "(HyperDoc) Error opening SessionServer, Retrying ...\n");
                }
                else
                    i = 11;
            }
            if (session_server == NULL) {
                fprintf(stderr, "(HyperDoc) Connection attempt to session manager timed out.\n");
                if (is_fricas_server) {
                    fprintf(stderr,
                            "(HyperDoc) Server unable to connect to session server\n");
                    exit(-1);
                }
                else {
                    MenuServerOpened = 0;
                }
            }
        }
    }
}