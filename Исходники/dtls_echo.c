void dtls_server (int port)
{
    int listen_sd;
    int sock, ret;
    struct sockaddr_in sa_serv;
    char buffer[MAX_MESSAGE_SIZE];
    int mtu = 1400;
    unsigned char sequence[8];
    gnutls_datum_t cookie_key; // Should this be regenerated for each incoming conn?
    
    // Certs
    char *cafile = "./certs/cert.pem";
    char *crlfile = "./certs/crl.pem";
    char *certfile = "./certs/cert.pem";
    char *keyfile = "./certs/key.pem";
    
    // Configure credentials and session
    gnutls_certificate_allocate_credentials (&x509_cred);
    gnutls_certificate_set_x509_trust_file (x509_cred, cafile, GNUTLS_X509_FMT_PEM);
    gnutls_certificate_set_x509_crl_file (x509_cred, crlfile, GNUTLS_X509_FMT_PEM);
    ret = gnutls_certificate_set_x509_key_file (x509_cred, certfile, keyfile,
                                          GNUTLS_X509_FMT_PEM);
    if (ret < 0) Die("No keys or certs were found");
    
    // Set some crypto params and other stuff
    generate_dh_params (); // Diffie-Hellman
    gnutls_priority_init (&priority_cache,
            "PERFORMANCE:-VERS-TLS-ALL:+VERS-DTLS1.0:%SERVER_PRECEDENCE", 
            NULL);
    gnutls_key_generate (&cookie_key, GNUTLS_COOKIE_KEY_SIZE);
    
    /* Socket operations
     */
    listen_sd = socket (AF_INET, SOCK_DGRAM, 0);

    memset (&sa_serv, '\0', sizeof (sa_serv));
    sa_serv.sin_family = AF_INET;
    sa_serv.sin_addr.s_addr = INADDR_ANY;
    sa_serv.sin_port = htons (port);

/* DTLS requires the IP don't fragment (DF) bit to be set */
#if defined(IP_DONTFRAG)
      int optval = 1;
      setsockopt (listen_sd, IPPROTO_IP, IP_DONTFRAG,
                  (const void *) &optval, sizeof (optval));
#elif defined(IP_MTU_DISCOVER)
      int optval = IP_PMTUDISC_DO;
      setsockopt(listen_sd, IPPROTO_IP, IP_MTU_DISCOVER, 
                 (const void*) &optval, sizeof (optval));
#endif

    bind (listen_sd, (struct sockaddr *) &sa_serv, sizeof (sa_serv));

    printf ("UDP server ready. Listening to port '%d'.\n\n", port);
    
    for (;;)
    {
        printf ("Waiting for connection...\n");

        sock = wait_for_connection (listen_sd);
        if (sock < 0) continue;

        // Someone is accepting a connection, get data structures ready
        priv_data_st priv;
        gnutls_dtls_prestate_st prestate;
        gnutls_session_t session;
        struct sockaddr_in cli_addr;
        socklen_t cli_addr_size;

        cli_addr_size = sizeof (cli_addr);
        ret = recvfrom (sock, buffer, sizeof (buffer), MSG_PEEK,
                        (struct sockaddr *) &cli_addr, &cli_addr_size);
        if (ret > 0)
        {
            memset (&prestate, 0, sizeof (prestate));
            ret = gnutls_dtls_cookie_verify (&cookie_key, &cli_addr,
                                             sizeof (cli_addr), buffer, ret,
                                             &prestate);
            if (ret < 0) /* cookie not valid */
            {
                priv_data_st s;

                memset (&s, 0, sizeof (s));
                s.fd = sock;
                s.cli_addr = (void *) &cli_addr;
                s.cli_addr_size = sizeof (cli_addr);

                printf ("Sending hello verify request to %s\n",
                        human_addr ((struct sockaddr *) &cli_addr,
                                    sizeof (cli_addr), buffer,
                                    sizeof (buffer)));

                gnutls_dtls_cookie_send (&cookie_key, &cli_addr,
                                         sizeof (cli_addr), &prestate,
                                         (gnutls_transport_ptr_t) & s,
                                         push_func);

                /* discard peeked data */
                recvfrom (sock, buffer, sizeof (buffer), 0,
                          (struct sockaddr *) &cli_addr, &cli_addr_size);
                usleep (100);
                continue;
              }
            printf ("Accepted connection from %s\n",
                    human_addr ((struct sockaddr *)
                                &cli_addr, sizeof (cli_addr), buffer,
                                sizeof (buffer)));
          }
        else
          continue;

        session = initialize_tls_session ();
        gnutls_dtls_prestate_set (session, &prestate);
        gnutls_dtls_set_mtu (session, mtu);

        priv.session = session;
        priv.fd = sock;
        priv.cli_addr = (struct sockaddr *) &cli_addr;
        priv.cli_addr_size = sizeof (cli_addr);

        gnutls_transport_set_ptr (session, &priv);
        gnutls_transport_set_push_function (session, push_func);
        gnutls_transport_set_pull_function (session, pull_func);
        gnutls_transport_set_pull_timeout_function (session, pull_timeout_func);

        do
          {
            ret = gnutls_handshake (session);
          }
        while (ret < 0 && gnutls_error_is_fatal (ret) == 0);

        if (ret < 0)
          {
            fprintf (stderr, "Error in handshake(): %s\n",
                     gnutls_strerror (ret));
            gnutls_deinit (session);
            continue;
          }

        printf ("- Handshake was completed\n");

        for (;;)
          {
            do
              {
                ret = gnutls_record_recv_seq (session, buffer, MAX_MESSAGE_SIZE,
                                              sequence);
              }
            while (ret == GNUTLS_E_AGAIN || ret == GNUTLS_E_INTERRUPTED);

            if (ret < 0)
              {
                fprintf (stderr, "Error in recv(): %s\n",
                         gnutls_strerror (ret));
                break;
              }
            if (ret == 0)
              {
                printf ("EOF\n\n");
                break;
              }
            buffer[ret] = 0;
            printf ("received[%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x]: %s\n",
                    sequence[0], sequence[1], sequence[2], sequence[3],
                    sequence[4], sequence[5], sequence[6], sequence[7], buffer);

            /* reply back */
            ret = gnutls_record_send (session, buffer, ret);
            if (ret < 0)
              {
                fprintf (stderr, "Error in send(): %s\n",
                         gnutls_strerror (ret));
                break;
              }
          }

        gnutls_bye (session, GNUTLS_SHUT_WR);
        gnutls_deinit (session);

    }
    close (listen_sd);

    gnutls_certificate_free_credentials (x509_cred);
    gnutls_priority_deinit (priority_cache);

    gnutls_global_deinit ();
}