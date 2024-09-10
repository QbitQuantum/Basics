static void
client (int fd, int server_init)
{
  int ret;
  char buffer[MAX_BUF + 1];
  gnutls_anon_client_credentials_t anoncred;
  /* Need to enable anonymous KX specifically. */

  global_init ();

  if (debug)
    {
      gnutls_global_set_log_function (client_log_func);
      gnutls_global_set_log_level (4711);
    }

  gnutls_anon_allocate_client_credentials (&anoncred);

  /* Initialize TLS session
   */
  gnutls_init (&session, GNUTLS_CLIENT|GNUTLS_DATAGRAM);
  gnutls_dtls_set_mtu( session, 1500);

  /* Use default priorities */
  gnutls_priority_set_direct (session, "NONE:+VERS-DTLS1.0:+CIPHER-ALL:+MAC-ALL:+SIGN-ALL:+COMP-ALL:+ANON-ECDH:+CURVE-ALL", NULL);

  /* put the anonymous credentials to the current session
   */
  gnutls_credentials_set (session, GNUTLS_CRD_ANON, anoncred);

  gnutls_transport_set_ptr (session, (gnutls_transport_ptr_t) fd);
  gnutls_transport_set_push_function (session, push);

  /* Perform the TLS handshake
   */
  do 
    {
      ret = gnutls_handshake (session);
    }
  while (ret < 0 && gnutls_error_is_fatal(ret) == 0);

  if (ret < 0)
    {
      fail ("client: Handshake failed\n");
      gnutls_perror (ret);
      exit(1);
    }
  else
    {
      if (debug)
        success ("client: Handshake was completed\n");
    }

  if (debug)
    success ("client: TLS version is: %s\n",
             gnutls_protocol_get_name (gnutls_protocol_get_version
                                       (session)));

  if (!server_init)
    {
      if (debug) success("Initiating client rehandshake\n");
      do 
        {
          ret = gnutls_handshake (session);
        }
      while (ret < 0 && gnutls_error_is_fatal(ret) == 0);

      if (ret < 0)
        {
          fail ("2nd client gnutls_handshake: %s\n", gnutls_strerror(ret));
          terminate();
        }
    }
  else
    {
      do {
        ret = gnutls_record_recv (session, buffer, MAX_BUF);
      } while (ret == GNUTLS_E_AGAIN || ret == GNUTLS_E_INTERRUPTED);
    }

  if (ret == 0)
    {
      if (debug)
        success ("client: Peer has closed the TLS connection\n");
      goto end;
    }
  else if (ret < 0)
    {
      if (server_init && ret == GNUTLS_E_REHANDSHAKE)
        {
          if (debug) success("Initiating rehandshake due to server request\n");
          do 
            {
              ret = gnutls_handshake (session);
            }
          while (ret < 0 && gnutls_error_is_fatal(ret) == 0);
        }

      if (ret != 0)
        {
          fail ("client: Error: %s\n", gnutls_strerror (ret));
          exit(1);
        }
    }

  do {
    ret = gnutls_record_send (session, MSG, strlen (MSG));
  } while (ret == GNUTLS_E_AGAIN || ret == GNUTLS_E_INTERRUPTED);
  gnutls_bye (session, GNUTLS_SHUT_WR);

end:

  close (fd);

  gnutls_deinit (session);

  gnutls_anon_free_client_credentials (anoncred);

  gnutls_global_deinit ();
}