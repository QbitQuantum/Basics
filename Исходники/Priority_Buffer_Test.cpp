static void *
consumer (void *args)
{
  ACE_Message_Queue<ACE_MT_SYNCH> *msg_queue =
    reinterpret_cast<ACE_Message_Queue<ACE_MT_SYNCH> *> (args);

  u_long cur_priority = 27;
  ACE_UNUSED_ARG (cur_priority);
  // To suppress ghs warning about unused local variable
  // "cur_priority".

  int local_count = 0;

  // Keep looping, reading a message out of the queue, until we get a
  // message with a length == 0, which signals us to quit.
  for (char c = 'z'; ; c--)
    {
      ACE_Message_Block *mb = 0;

      int result = msg_queue->dequeue_head (mb);

      if (result == -1)
        break;

      local_count++;

      size_t length = mb->length ();

      if (length > 0)
        {
          // This isn't a "shutdown" message, so process it
          // "normally."
          ACE_TEST_ASSERT (c == *mb->rd_ptr ());
          ACE_TEST_ASSERT (mb->msg_priority () < cur_priority);
          cur_priority = mb->msg_priority ();
        }

      // Free up the buffer memory and the Message_Block. Note that
      // the destructor of Message Block will delete the the actual
      // buffer.
      mb->release ();

      if (length == 0)
        // This was a "shutdown" message, so break out of the loop.
        break;
    }

  ACE_TEST_ASSERT (local_count == message_count);
  return 0;
}