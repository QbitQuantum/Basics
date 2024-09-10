void SipMsgReceiver::RecvRecordControlHandler(const SipMsgParser &parser, 
                                              const QString &from) {
  RecordControlMsg msg;
  msg.requester_uri = parser.GetURI();
  msg.target_vuri = parser.GetVirtualURI();
  msg.tx_uri = parser.GetTxURI();
  msg.requester_ip = parser.GetSenderIP();
  msg.transaction_id = parser.GetTransactionId();
  msg.type = parser.GetType().toInt();
  msg.port = parser.GetPort();
  emit NotifyRecvRecordControlSignal(msg, from);
}