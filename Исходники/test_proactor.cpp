int
Sender::open (const ACE_TCHAR *host,
               u_short port)
{
  // Initialize stuff

  // Open input file (in OVERLAPPED mode)
  this->input_file_ =
    ACE_OS::open (file, GENERIC_READ | FILE_FLAG_OVERLAPPED);
  if (this->input_file_ == ACE_INVALID_HANDLE)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "ACE_OS::open"), -1);

  // Find file size
  this->file_size_ =
    ACE_OS::filesize (this->input_file_);

  // Connect to remote host
  ACE_INET_Addr address (port, host);
  ACE_SOCK_Connector connector;
  if (connector.connect (this->stream_,
                         address) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "ACE_SOCK_Connector::connect"),
                      -1);

  // Open ACE_Asynch_Write_Stream
  if (this->ws_.open (*this) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "ACE_Asynch_Write_Stream::open"),
                      -1);

  // Open ACE_Asynch_Read_File
  if (this->rf_.open (*this, this->input_file_) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "ACE_Asynch_Read_File::open"),
                      -1);

  // Start an asynchronous transmit file
  if (this->transmit_file () == -1)
    return -1;

  // Start an asynchronous read file
  if (this->initiate_read_file () == -1)
    return -1;

  return 0;
}