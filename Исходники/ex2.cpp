static void *
consumer (void *)
{
  ACE_UPIPE_Stream c_stream;

  // Set the high water mark to size to achieve optimum performance.

  int wm = size * iterations;

  if (c_stream.control (ACE_IO_Cntl_Msg::SET_HWM,
                        &wm) == -1)
    ACE_DEBUG ((LM_DEBUG,
                "set HWM failed\n"));

  ACE_UPIPE_Addr serv_addr (ACE_TEXT("pattern"));

  // accept will wait up to 4 seconds
  ACE_UPIPE_Acceptor acc (serv_addr);

  ACE_DEBUG ((LM_DEBUG,
              "(%t) consumer spawning the supplier thread\n"));

  // Spawn the supplier thread.
  if (ACE_Thread_Manager::instance ()->spawn (ACE_THR_FUNC (supplier),
                                              (void *) 0,
                                              THR_NEW_LWP | THR_DETACHED) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "spawn"),
                      0);

  ACE_DEBUG ((LM_DEBUG,
              "(%t) consumer starting accept\n"));

  if (acc.accept (c_stream) == -1)
    ACE_ERROR ((LM_ERROR,
                "(%t) %p\n",
                "ACE_UPIPE_Acceptor.accept failed"));

  // Time measurement.
  time_t currsec;
  ACE_OS::time (&currsec);
  time_t start = (time_t) currsec;

  int received_messages = 0;

  for (ACE_Message_Block *mb = 0;
       c_stream.recv (mb) != -1 && mb->size () != 0;
       mb->release ())
    received_messages++;

  ACE_OS::time (&currsec);
  time_t secs = (time_t) currsec - start;

  ACE_DEBUG ((LM_DEBUG,
              "(%t) Transferred %d blocks of size %d\n"
              "The program ran %d seconds\n",
              received_messages, size, secs));
  c_stream.close ();
  return 0;
}