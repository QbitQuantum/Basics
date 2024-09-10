void CGameClient::cb_close_port(void* kodiInstance, unsigned int port)
{
  CGameClient *gameClient = static_cast<CGameClient*>(kodiInstance);
  if (!gameClient)
    return;

  gameClient->ClosePort(port);
}