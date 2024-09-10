int
Thread_Pool::svc (void)
{
  // Keep looping, reading a message out of the queue, until we get a
  // message with a length == 0, which signals us to quit.

  for (int count = 1; ; count++)
    {
      ACE_Message_Block *mb = 0;

      int result = this->getq (mb);

      ACE_TEST_ASSERT (result != -1 || errno == ESHUTDOWN);

      if (result == -1 && errno == ESHUTDOWN)
        {
          // The queue has been deactivated, so let's bail out.
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("(%t) in iteration %d, queue len = %d, ")
                      ACE_TEXT ("queue deactivated, exiting\n"),
                      count,
                      this->msg_queue ()->message_count ()));

          break;
        }

      size_t length = mb->length ();

      if (length > 0)
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) in iteration %d, queue len = %d, ")
                    ACE_TEXT ("length = %d, text = \"%*s\"\n"),
                    count,
                    this->msg_queue ()->message_count (),
                    length,
                    length - 1,
                    mb->rd_ptr ()));

      // We're responsible for deallocating this.
      mb->release ();

      if (length == 0)
        {
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("(%t) in iteration %d, queue len = %d, ")
                      ACE_TEXT ("got \"empty\" message, exiting\n"),
                      count,
                      this->msg_queue ()->message_count ()));
          break;
        }
    }

  // Note that the <ACE_Task::svc_run> method automatically removes us
  // from the <ACE_Thread_Manager> when the thread exits.
  return 0;
}