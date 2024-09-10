ACE_SOCK_Stream *
ACE_TSS_Connection::make_TSS_TYPE (void) const
{
  ACE_TRACE ("ACE_TSS_Connection::make_TSS_TYPE");

  ACE_SOCK_Connector connector;
  ACE_SOCK_Stream *stream = 0;

  ACE_NEW_RETURN (stream,
                  ACE_SOCK_Stream,
                  0);

  if (connector.connect (*stream, server_address_) == -1)
    {
      delete stream;
      errno = ECONNREFUSED;
      return 0;
    }

  ACE_DEBUG ((LM_DEBUG,  ACE_TEXT ("ACE_TSS_Connection new connection\n")));
  return stream;
}