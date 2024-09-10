void DBGRequestor::requestBreakpoint(int bpno, int modno, const QString& remoteFilePath, int line, const QString& condition, int status, int skiphits)
{
  if(!m_socket) return;

  DBGRequestPack* requestPack = DBGRequestPackBuilder::buildBreakpoint(
                                  bpno, modno, remoteFilePath, line, condition, status, skiphits);
  requestPack->header()->setFlags(m_headerFlags);
  requestPack->send(m_socket);
  delete requestPack;
}