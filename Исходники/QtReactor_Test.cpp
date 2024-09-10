int TCPConnectionHandler::sendBuffers ()
{
  int result = 0;

  if (buffers_)
    if (0 < (result = peer_.send_n (buffers_))) // remove sent blocks
      {
        totalSent_ += result;
        while (buffers_ &&
               static_cast< size_t > (result) >= buffers_->length ())
          {
            ACE_Message_Block *buffer = buffers_;
            result -= buffers_->length ();
            buffers_= buffers_->cont ();
            buffer->cont (0);
            buffer->release ();
          }

        if (buffers_) // some buffers were not sent, truncate data
          buffers_->rd_ptr (result);
      }

  return result;
}