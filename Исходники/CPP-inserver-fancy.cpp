int
Handler_Factory::create_handler (ACE_SOCK_Acceptor &acceptor,
                                 Handler * (*handler_factory) (ACE_HANDLE),
                                 const char *handler_type)
{
  ACE_SOCK_Stream new_stream;

  if (acceptor.accept (new_stream) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "accept"),
                       -1);

  Handler *handler;

  ACE_ALLOCATOR_RETURN (handler,
                        (*handler_factory) (new_stream.get_handle ()),
                        -1);

  ACE_DEBUG ((LM_DEBUG,
              "(%P|%t) spawning %s handler\n",
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