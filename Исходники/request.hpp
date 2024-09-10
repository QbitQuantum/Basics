 void on_open(connection_ptr con) {
     std::stringstream o;
     
     o << "{"
       << "\"type\":\"test_welcome\","
       << "\"version\":\"" << m_ua << "\","
       << "\"ident\":\"" << m_ident << "\","
       << "\"num_workers\":" << m_num_workers 
       << "}";
     
     con->send(o.str());
 }