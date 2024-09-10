static void *
acceptor (void *args)
{
  ACE_UPIPE_Acceptor *acceptor = (ACE_UPIPE_Acceptor *) args;
  ACE_UPIPE_Stream s_stream;

  if (acceptor->accept (s_stream) == -1)
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) ACE_UPIPE_Acceptor.accept failed\n")));

  ACE_Message_Block *mb = 0;

  if (s_stream.recv (mb) == -1)
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) acceptor recv failed\n")));

  ACE_TEST_ASSERT (ACE_OS::strcmp (mb->rd_ptr (), "hello") == 0);

  mb->wr_ptr (mb->rd_ptr ());
  mb->copy ("thanks");

  if (s_stream.send (mb) == -1)
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) acceptor send failed\n")));

  char s_buf[BUFSIZ];
  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) acceptor sleeping on recv\n")));

  if (s_stream.recv (s_buf, sizeof (s_buf)) == -1)
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) acceptor recv failed\n")));
  else
    ACE_TEST_ASSERT (ACE_OS::strcmp (s_buf,
                                "This string is sent by connector as a buffer") == 0);

  const char svr_response[] = "this is the acceptor response!";
  ACE_OS::strcpy (s_buf, svr_response);

  if (s_stream.send (s_buf, sizeof (svr_response)) == -1)
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) acceptor send failed\n")));

  s_stream.close ();
  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) exiting thread\n")));
  return 0;
}