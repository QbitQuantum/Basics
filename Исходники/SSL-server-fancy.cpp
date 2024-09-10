int
Handler_Factory::create_handler (
  ACE_SSL_SOCK_Acceptor &acceptor,
  Handler * (*handler_factory) (ACE_SSL_SOCK_Stream* ),
  const char *handler_type)
{
  ACE_SSL_SOCK_Stream* new_stream;

  ACE_NEW_RETURN (new_stream, ACE_SSL_SOCK_Stream, -1);

  if (acceptor.accept (*new_stream) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%p\n"),
                       ACE_TEXT ("accept")),
                       -1);

  Handler *handler;

  ACE_ALLOCATOR_RETURN (handler,
                        (*handler_factory) (new_stream),
                        -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%P|%t) spawning %s handler\n"),
              handler_type));

  if (handler->open () == -1)
    return -1;

#if defined (ACE_MT_SAFE)
  // Spawn a new thread and run the new connection in that thread of
  // control using the <server> function as the entry point.
  return handler->activate ();
#else
  handler->svc ();
  handler->close (0);
  return 0;
#endif /* ACE_HAS_THREADS */
}