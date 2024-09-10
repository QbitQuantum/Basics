 bool open()
  {
      ACE_SOCK_Connector connector;
      ACE_INET_Addr addr(80,"127.0.0.1");
      ACE_Time_Value timeout(5,0);
     if(connector.connect(peer,addr,&timeout) != 0)
      {
         cout<<"connecetd fail"<<endl;
         return false;
      }
      ACE_Reactor::instance()->register_handler(this,ACE_Event_Handler::READ_MASK);
      cout<<"connecetd "<<endl;
     return true;
  }