extern "C" RENDERDOC_API TargetControl *RENDERDOC_CC RENDERDOC_CreateTargetControl(
    const char *host, uint32_t ident, const char *clientName, bool32 forceConnection)
{
  string s = "localhost";
  if(host != NULL && host[0] != '\0')
    s = host;

  bool android = false;

  if(host != NULL && !strncmp(host, "adb:", 4))
  {
    android = true;
    s = "127.0.0.1";

    // could parse out an (optional) device name from host+4 here.
  }

  Network::Socket *sock = Network::CreateClientSocket(s.c_str(), ident & 0xffff, 750);

  if(sock == NULL)
    return NULL;

  bool localhost = !android && (Network::GetIPOctet(sock->GetRemoteIP(), 0) == 127);

  TargetControl *remote = new TargetControl(sock, clientName, forceConnection != 0, localhost);

  if(remote->Connected())
    return remote;

  delete remote;
  return NULL;
}