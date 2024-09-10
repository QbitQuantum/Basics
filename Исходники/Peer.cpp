int
Peer_Handler::await_events (void)
{
  ACE_Message_Block *mb = 0;

  ssize_t n = this->recv (mb);

  switch (n)
    {
    case 0:
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("gatewayd has closed down\n")),
                        -1);
      /* NOTREACHED */
    case -1:
      if (errno == EWOULDBLOCK)
        // A short-read, we'll come back and finish it up later on!
        return 0;
      else
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%p\n"),
                           ACE_TEXT ("recv")),
                          -1);
      /* NOTREACHED */
    default:
      {
        // We got a valid event, so let's process it now!  At the
        // moment, we just print out the event contents...

        Event *event = (Event *) mb->rd_ptr ();
        this->total_bytes_ += mb->length ();

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("route id = %d, cur len = %d, total len = %d\n"),
                    event->header_.connection_id_,
                    event->header_.len_,
                    this->total_bytes_));
        if (Options::instance ()->enabled (Options::VERBOSE))
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("data_ = %*s\n"),
                      event->header_.len_ - 2,
                      event->data_));
        mb->release ();
        return 0;
      }
    }
}