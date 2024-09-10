static void *
client (void *arg)
{
  ACE_INET_Addr *remote_addr = reinterpret_cast<ACE_INET_Addr *> (arg);

  ACE_INET_Addr server_addr (remote_addr->get_port_number (),
                             "::1");

  ACE_SOCK_Stream cli_stream;

  ACE_SOCK_Connector con;
  ACE_Time_Value timeout (ACE_DEFAULT_TIMEOUT);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%P|%t) Connecting to port %d\n"),
              server_addr.get_port_number()));

  // Initiate connection with server; don't wait forever
  if (con.connect (cli_stream,
                   server_addr,
                   &timeout) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("(%P|%t) %p\n"),
                  ACE_TEXT ("connection failed")));

      return 0;
    }

  // if connect succesful, what is the max port number we connected
  // up to now.
  int connected_port = server_addr.get_port_number ();

  if (connected_port > max_connected_port)
    max_connected_port = connected_port;

  cli_stream.close ();

  return 0;
}