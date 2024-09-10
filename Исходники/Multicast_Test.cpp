int send_dgram (ACE_SOCK_Dgram &socket, ACE_INET_Addr addr, int done = 0)
{

  // Send each message twice, once to the right port, and once to the "wrong"
  // port.  This helps generate noise and lets us see if port filtering is
  // working properly.
  const char *address = addr.get_host_addr ();
  int port = addr.get_port_number ();

  for (int i = 0; i < 2; ++i)
    {
      char buf[MAX_STRING_SIZE];
      if (done)
        buf[0] = 0;
      else
        ACE_OS::sprintf (buf, "%s/%d", address, port);

      if (socket.send (buf, ACE_OS::strlen (buf),addr) == -1)
        ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("Send to %C, %p\n"),
                           address,
                           ACE_TEXT ("send_dgram - error calling send on ")
                           ACE_TEXT ("ACE_SOCK_Dgram.")), -1);
      addr.set_port_number (++port);
    }
  return 0;
}