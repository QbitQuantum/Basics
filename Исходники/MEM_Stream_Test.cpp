int
run_client (u_short port,
            ACE_MEM_IO::Signal_Strategy strategy)
{
  int status = 0;
  ACE_MEM_Addr to_server (port);
  ACE_MEM_Connector connector;
  connector.preferred_strategy (strategy);
  ACE_MEM_Stream stream;

  //  connector.preferred_strategy (ACE_MEM_IO::MT);

  if (connector.connect (stream, to_server.get_remote_addr ()) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("Failed to connect to <%C> %p\n"),
                       to_server.get_host_name (),
                       ACE_TEXT ("connector.connect()")),
                      -1);

  ACE_TCHAR buf[MAXPATHLEN];

  for (size_t cntr = 0; cntr < NUMBER_OF_ITERATIONS; cntr ++)
    {
      ACE_OS::snprintf (buf, MAXPATHLEN,
                        ACE_TEXT ("Iteration ") ACE_SIZE_T_FORMAT_SPECIFIER,
                        cntr);

      ssize_t slen = (ACE_OS::strlen (buf) + 1) * sizeof (ACE_TCHAR);

      if (stream.send (buf, slen) < slen)
        {
          ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"),
                      ACE_TEXT ("In stream.send()")));
          status = -1;
          break;
        }

      if (stream.recv (buf, MAXPATHLEN) == -1)
        {
          ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"),
                      ACE_TEXT ("stream.recv()")));
          status = -1;
          break;
        }

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("run_client(), got echo %s\n"),
                  buf));
    }

  status = stream.close () == -1 ? -1 : status;
  return status;
}