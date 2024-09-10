void C4Network2Client::CloseConns(const char *szMsg) {
  C4PacketConnRe Pkt(false, false, szMsg);
  C4Network2IOConnection *pConn;
  while (pConn = pMsgConn) {
    // send packet, close
    if (pConn->isOpen()) {
      pConn->Send(MkC4NetIOPacket(PID_ConnRe, Pkt));
      pConn->Close();
    }
    // remove
    RemoveConn(pConn);
  }
}