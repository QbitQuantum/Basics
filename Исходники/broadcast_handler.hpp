 void command_error(connection_ptr connection,const std::string msg) {
     connection->send("{\"type\":\"error\",\"value\":\""+msg+"\"}");
 }