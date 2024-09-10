 void send_stats_update(connection_ptr connection) {
     if (m_msg_stats.empty()) {
         return;
     }
     // example: `ack:e3458d0aceff8b70a3e5c0afec632881=38;e3458d0aceff8b70a3e5c0afec632881=42;`
     std::stringstream msg;
     msg << "ack:";
     
     std::map<std::string,size_t>::iterator it;
     
     for (it = m_msg_stats.begin(); it != m_msg_stats.end(); it++) {
         msg << (*it).first << "=" << (*it).second << ";";
     }
     
     std::cout << "sending " << msg.str() << std::endl;
     connection->send(msg.str());
     
     m_msg_stats.clear();
 }