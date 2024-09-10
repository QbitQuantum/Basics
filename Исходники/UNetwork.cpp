bool			Network::createSocket(std::string proto, int &type)
{
  struct protoent       *pe;
  ClientInfo		*current;

  if (_connected.find(0) != _connected.end())
    return (false);
  if (!(current = (new ClientInfo(_len))))
    return (false);
  if (!(pe = getprotobyname(proto.c_str())))
    return (false);
  if ((current->get_socket() = socket(_family, type, pe->p_proto)) == -1)
    {
      delete current;
      return (false);
    }
  _connected[++_id] = current; //stockage de la socket
  return (true);
}