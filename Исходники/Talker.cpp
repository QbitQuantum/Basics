// New stuff added to the message queue.  Try to dequeue a message.
int
Peer_Handler::handle_output (ACE_HANDLE)
{
  ACE_Message_Block *mb = 0;

  ACE_Time_Value tv (ACE_Time_Value::zero);

  // Forward the message to the remote peer receiver.
  if (this->getq (mb, &tv) != -1)
    {
      if (this->wr_stream_.write (*mb,
                                  mb->length ()) == -1)
        ACE_ERROR_RETURN ((LM_ERROR, "%p Write initiate.\n", "Peer_Handler"), -1);
    }
  return 0;
}