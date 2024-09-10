static int
run_client (void)
{
  ACE_MEM_Connector connector;
  ACE_MEM_Stream stream;
  ACE_MEM_Addr server_addr (ACE_DEFAULT_SERVER_PORT);

  if (connector.connect (stream, server_addr.get_remote_addr ()) == -1)
    ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "connect"), -1);

  char buf [MAXPATHLEN];
  while (fgets (buf, MAXPATHLEN, stdin) >0)
    {
      stream.send (buf, ACE_OS::strlen (buf)+1);
      stream.recv (buf, MAXPATHLEN);
      ACE_DEBUG ((LM_DEBUG, "Echo: %s\n", buf));
    }

  return 0;
}