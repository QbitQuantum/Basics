void P2PServer::onStringMessage(const TcpConnectionPtr& conn,
                      const string& message,
                      Timestamp)
{
  char   type = message[0];
  int      id = message[1]; 
  string   ip = message.substr(2,4);
  int reqfile = message[6];
  //catalogue_->insertUser(ip, reqfile); 
    cout << endl 
       << "test" << catalogue_->hasNeighbor(ip) 
       << message 
       << endl;
  string ret;
  if(type == 'a')
  {
    catalogue_->insertUser(ip, reqfile);

    ret.append("b0");
    ret.append(processMessage(ip));
    cout << endl << ret << endl;
    codec_.send(conn, ret);
    conn->shutdown();
  }
  else if(type == 'c')
  {
    ret.append("d01111");
    ret.append(1, (char)100);
    cout << endl << "222test" << endl << ret;
    codec_.send(conn, ret);
  }
  else
  { 
    cout << "error 123" << endl;
  } 
}