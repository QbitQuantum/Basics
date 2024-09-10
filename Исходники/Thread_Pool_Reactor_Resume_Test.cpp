static ACE_THR_FUNC_RETURN
worker (void *)
{
  ACE_OS::sleep (3);
  const ACE_TCHAR *msg = ACE_TEXT ("Message from Connection worker");
  ACE_TCHAR buf [BUFSIZ];
  buf[0] = static_cast<ACE_TCHAR> ((ACE_OS::strlen (msg) + 1));
  ACE_OS::strcpy (&buf[1], msg);

  ACE_INET_Addr addr (rendezvous);

  ACE_DEBUG((LM_DEBUG,
             "(%t) Spawning %d client threads...\n",
             cli_thrno));
  int grp = ACE_Thread_Manager::instance ()->spawn_n (cli_thrno,
                                                      &cli_worker,
                                                      buf);
  ACE_TEST_ASSERT (grp != -1);

  ACE_Thread_Manager::instance ()->wait_grp (grp);

  ACE_DEBUG ((LM_DEBUG,
              "(%t) Client threads done; shutting down...\n"));
  ACE_SOCK_Stream stream;
  ACE_SOCK_Connector connect;

  if (connect.connect (stream, addr) == -1)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%t) %p Error while connecting\n"),
                ACE_TEXT ("connect")));

  const ACE_TCHAR *sbuf = ACE_TEXT ("\011shutdown");

  ACE_DEBUG ((LM_DEBUG,
              "shutdown stream handle = %x\n",
              stream.get_handle ()));

  if (stream.send_n (sbuf, (ACE_OS::strlen (sbuf) + 1) * sizeof (ACE_TCHAR)) == -1)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%t) %p\n"),
                ACE_TEXT ("send_n")));

  ACE_DEBUG ((LM_DEBUG,
              "Sent message of length  = %d\n",
              ACE_OS::strlen (sbuf)));
  stream.close ();

  return 0;
}