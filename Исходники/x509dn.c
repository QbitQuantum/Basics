static void
server (void)
{
  /* this must be called once in the program
   */
  gnutls_global_init ();

  gnutls_global_set_log_function (tls_log_func);
  if (debug)
    gnutls_global_set_log_level (4711);

  gnutls_certificate_allocate_credentials (&x509_cred);
  gnutls_certificate_set_x509_trust_mem (x509_cred, &ca, GNUTLS_X509_FMT_PEM);

  gnutls_certificate_set_x509_key_mem (x509_cred, &server_cert, &server_key,
				       GNUTLS_X509_FMT_PEM);

  if (debug)
    success ("Launched, generating DH parameters...\n");

  generate_dh_params ();

  gnutls_certificate_set_dh_params (x509_cred, dh_params);

  client_len = sizeof (sa_cli);

  session = initialize_tls_session ();

  sd = accept (listen_sd, (SA *) & sa_cli, &client_len);

  if (debug)
    success ("server: connection from %s, port %d\n",
	     inet_ntop (AF_INET, &sa_cli.sin_addr, topbuf,
			sizeof (topbuf)), ntohs (sa_cli.sin_port));

  gnutls_transport_set_ptr (session, (gnutls_transport_ptr_t) sd);
  ret = gnutls_handshake (session);
  if (ret < 0)
    {
      close (sd);
      gnutls_deinit (session);
      fail ("server: Handshake has failed (%s)\n\n", gnutls_strerror (ret));
      return;
    }
  if (debug)
    success ("server: Handshake was completed\n");

  if (debug)
    success ("server: TLS version is: %s\n",
	     gnutls_protocol_get_name (gnutls_protocol_get_version
				       (session)));

  /* see the Getting peer's information example */
  if (debug)
    print_info (session);

  i = 0;
  for (;;)
    {
      memset (buffer, 0, MAX_BUF + 1);
      ret = gnutls_record_recv (session, buffer, MAX_BUF);

      if (ret == 0)
	{
	  if (debug)
	    success ("server: Peer has closed the GnuTLS connection\n");
	  break;
	}
      else if (ret < 0)
	{
	  fail ("server: Received corrupted data(%d). Closing...\n", ret);
	  break;
	}
      else if (ret > 0)
	{
	  /* echo data back to the client
	   */
	  gnutls_record_send (session, buffer, strlen (buffer));
	}
    }
  /* do not wait for the peer to close the connection.
   */
  gnutls_bye (session, GNUTLS_SHUT_WR);

  close (sd);
  gnutls_deinit (session);

  close (listen_sd);

  gnutls_certificate_free_credentials (x509_cred);

  gnutls_dh_params_deinit (dh_params);

  gnutls_global_deinit ();

  if (debug)
    success ("server: finished\n");
}