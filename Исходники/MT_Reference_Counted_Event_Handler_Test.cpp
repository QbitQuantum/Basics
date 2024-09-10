int
Pipe::open (void)
{
  ACE_INET_Addr my_addr;
  ACE_SOCK_Acceptor acceptor;
  ACE_SOCK_Connector connector;
  ACE_SOCK_Stream reader;
  ACE_SOCK_Stream writer;
  int result = 0;

  // Bind listener to any port and then find out what the port was.
  if (acceptor.open (ACE_Addr::sap_any) == -1
      || acceptor.get_local_addr (my_addr) == -1)
    result = -1;
  else
    {
      int af = my_addr.get_type ();
      const ACE_TCHAR *local = ACE_LOCALHOST;
#if defined (ACE_HAS_IPV6)
      if (af == AF_INET6)
        local = ACE_IPV6_LOCALHOST;
#endif /* ACE_HAS_IPV6 */
      ACE_INET_Addr sv_addr (my_addr.get_port_number (),
                             local,
                             af);

      // Establish a connection within the same process.
      if (connector.connect (writer, sv_addr) == -1)
        result = -1;
      else if (acceptor.accept (reader) == -1)
        {
          writer.close ();
          result = -1;
        }
    }

  // Close down the acceptor endpoint since we don't need it anymore.
  acceptor.close ();
  if (result == -1)
    return -1;

  this->handles_[0] = reader.get_handle ();
  this->handles_[1] = writer.get_handle ();

  return 0;
}