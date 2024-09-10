int Sender::open (const ACE_TCHAR *host, u_short port)
{
  // Initialize stuff
  // Connect to remote host
  ACE_INET_Addr address (port, host);
  ACE_SOCK_Connector connector;

  if (connector.connect (this->stream_,
                         address) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%p\n",
                         "ACE_SOCK_Connector::connect"),
                        -1);
    }

  // Open ACE_Asynch_Write_Stream
  if (this->ws_.open (*this) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "ACE_Asynch_Write_Stream::open"),
                      -1);

  // Open ACE_Asynch_Read_Stream
  if (this->rs_.open (*this) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "ACE_Asynch_Read_File::open"),
                      -1);

  // Start an asynchronous transmit file
  if ( this->initiate_write_stream () == -1)
    return -1;

  if ( duplex != 0 )
    {
      // Start an asynchronous read file
      if (this->initiate_read_stream () == -1)
        return -1;
    }

  return 0;
}