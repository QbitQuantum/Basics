 void sendMyName(shared_ptr<NetSendConnection> connection) const {
     BinaryOutput bo;
     bo.writeString32(m_name);
     connection->send(CHANGE_NAME, bo);
 }