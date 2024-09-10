template <class BARRIER> int
Worker_Task<BARRIER>::svc (void)
{
  // Note that the <ACE_Task::svc_run> method automatically adds us to
  // the Thread_Manager when the thread begins.

  // Keep looping, reading a message out of the queue, until we get a
  // message with a length == 0, which signals us to quit.

  for (int iter = 1; ;iter++)
    {
      ACE_Message_Block *mb = 0;

      int result = this->getq (mb);

      if (result == -1)
        {
          ACE_ERROR ((LM_ERROR,
                      "(%t) in iteration %d\n",
                      "error waiting for message in iteration",
                      iter));
          break;
        }

      size_t length = mb->length ();
      this->service (mb,iter);

      if (length == 0)
        {
          ACE_DEBUG ((LM_DEBUG,
                      "(%t) in iteration %d got quit, exit!\n",
                      iter));
                      mb->release ();
          break;
        }

      this->barrier_.wait ();
      this->output (mb);

      mb->release ();
    }

  // Note that the <ACE_Task::svc_run> method automatically removes us
  // from the Thread_Manager when the thread exits.

  return 0;
}