int
Sender::initiate_write_stream ()
{
  if (this->flg_cancel_ != 0)
    {
      return -1;
    }

  if (this->get_ref_cnt_w() != 0)
    {
      return 0; // todo: queue it
    }


  u_int blksize = this->config().s_blksize();
  u_int limit   = this->config().xfer_limit();
  u_int winsize = this->config().w_size();

  if (limit != 0 && this->total_snd_ >= limit)
    {
      this->shutdown_i ();
      return 0;
    }

  u_long delta = this->total_snd_- this->total_rcv_;
  if (delta > winsize)
     return 0;

  ACE_Message_Block *mb = 0;

  ACE_NEW_RETURN (mb,
                  ACE_Message_Block (blksize+1),
                  -1);

  mb->copy(complete_message);
  mb->copy("\0");
  mb->wr_ptr(mb->base() + blksize);
 

  if (this->stream_.write (*mb, mb->length ()) == -1)
    {
      mb->release ();
      this->cancel_i();
      return -1;
    }

  this->ref_cnt_w_++;
  this->total_w_++;
  return 0;
}