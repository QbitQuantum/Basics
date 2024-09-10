static void *
client (void *)
{
  char buf[100];
  size_t mes_len;
  ACE_OS::sleep (1);

  ACE_DEBUG ((LM_DEBUG,
              " (%P) Client: Starting...\n"));

  ACE_SOCK_Stream stream;
  ACE_SOCK_Connector connector;
  ACE_OS::sprintf (buf, "Client: the life was good!");

  mes_len = (int) htonl (ACE_OS::strlen (buf) + 1);

  if (connector.connect (stream,
                         ACE_INET_Addr (SERV_TCP_PORT,
                                        ACE_DEFAULT_SERVER_HOST)) == -1)
    ACE_ERROR ((LM_ERROR,
                "(%P) %p\n",
                "Socket open"));

  if (stream.send (4,
                   (void *) &mes_len,
                   sizeof (size_t),
                   (void *)buf,
                   ACE_OS::strlen (buf) + 1) == -1)

    ACE_ERROR ((LM_ERROR,
                "(%P) %p\n",
                "Socket send"));

  if (stream.close () == -1)
    ACE_ERROR ((LM_ERROR,
                "(%P) %p\n",
                "Socket close"));

  ACE_DEBUG ((LM_DEBUG,
              "(%P) Client: Message has been sent, about to exit...\n"));
  return 0;
}