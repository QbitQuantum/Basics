  int CloudBus::svc(void)
  {
    
    while (true) {
      if (connected_) {
	//
      } else {
	std::string connect_addr(relay_inet_addr_);
	if (connect_addr == "localhost") {
	  connect_addr = node_info_.address;
	}
	ACE_INET_Addr server(relay_port_,connect_addr.c_str());
	ACE_SOCK_Connector connector;

	if (connector.connect(this->peer(),server) == 0) {
	  ACE_TCHAR peer_name[MAXHOSTNAMELENGTH];
	  ACE_INET_Addr peer_addr;
	  if ((this->peer().get_remote_addr (peer_addr) == 0) && 
	      (peer_addr.addr_to_string (peer_name, MAXHOSTNAMELENGTH) == 0)) {

	    GDEBUG("CloudBus connected to relay at  %s\n", peer_name);
	    if (this->reactor ()->register_handler(this, ACE_Event_Handler::READ_MASK) != 0) {
	      GERROR("Failed to register read handler\n");
	      return -1;
	    }

	    mtx_.acquire();
	    connected_ = true;
	    mtx_.release();
	    if (!query_mode_) {
	      send_node_info();
	    }
	  } 
	}
      }
      //Sleep for 5 seconds
      ACE_Time_Value tv (5);
      ACE_OS::sleep (tv);	  	
    }
    return 0;
  }