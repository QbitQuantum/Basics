int
ACE::HTBP::ID_Requestor::connect_to_server (ACE_SOCK_Stream *cli_stream)
{
  if (port_ == 0 || host_.length() == 0)
    {
      int host_start = url_.find (ACE_TEXT("http://")) + 7;
      int port_sep = 0;
      int sep = 0;
      if (host_start == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT("(%P|%t) ACE::HTBP::ID_Requestor::")
                           ACE_TEXT("connect_to_server: ")
                           ACE_TEXT("invalid URL: \"%s\"\n"),
                           url_.c_str()),
                          -1);
      port_sep = url_.find (ACE_TEXT(":"),(size_t)host_start);
      sep = url_.find (ACE_TEXT("/"),(size_t)host_start);
      if (sep == -1 || sep == host_start +1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT("(%P|%t) ACE::HTBP::ID_Requestor::")
                           ACE_TEXT("connect_to_server: ")
                           ACE_TEXT("invalid URL: \"%s\"\n"),
                           url_.c_str()),
                          -1);
      if (port_sep == -1)
        {
          port_sep = sep;
          port_ = 80; // should be a default?
        }
      host_ = url_.substr(host_start,port_sep - host_start);
    }

  ACE_INET_Addr remote_addr (static_cast<u_short> (port_), host_.c_str());
  ACE_SOCK_Connector con;
  if (con.connect (*cli_stream,
                   remote_addr) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT("(%P|%t) ACE::HTBP::ID_Requestor::")
                       ACE_TEXT("connect_to_server: ")
                       ACE_TEXT("%p\n"),
                       ACE_TEXT("socket connect")),
                      -1);
  return 0;
}