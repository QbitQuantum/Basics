int
Receiver::on_data_received(ACE_Message_Block & mb,
                           const ACE_INET_Addr & remote)
{
  int nbytes = mb.length ();

  if (nbytes == 0)
    {
      mb.release();
      return 0;
    }

  if (this->io_count_r_ == 0)
    this->initiate_read();

  if (this->initiate_write (mb, remote) != 0)
    return -1;

  return 0;
}