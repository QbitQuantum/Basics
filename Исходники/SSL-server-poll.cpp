static void
handle_connections (ACE_SSL_SOCK_Acceptor &peer_acceptor,
                    size_t &n_handles)
{
  if (ACE_BIT_ENABLED (poll_array[0].revents, POLLIN))
    {
      ACE_SSL_SOCK_Stream new_stream;

      ACE_INET_Addr client;
      ACE_Time_Value nonblock (0, 0);

      // Handle all pending connection requests (note use of "polling"
      // feature that doesn't block).

      while (ACE_OS::poll (poll_array, 1, nonblock) > 0)
        if (peer_acceptor.accept (new_stream, &client) == -1)
          ACE_OS::perror ("accept");
        else
          {
            const char *s = client.get_host_name ();

            ACE_ASSERT (s != 0);
            ACE_DEBUG ((LM_DEBUG,
                        "(%P|%t) client %s\n",
                        s));
            poll_array[n_handles++].fd = new_stream.get_handle ();
          }
    }
}