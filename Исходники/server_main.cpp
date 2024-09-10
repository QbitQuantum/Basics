void Communication()
{
	try
  {
    // Create the socket
    ServerSocket server (port);
		int rounds = 16;
		string rStr = "";

    while ( true )
	  {
			//ServerSocket new_sock;
  	  server.accept (new_sock);
			stop = false;
			weFinish = false;
  	  try
      {
  	      while ( true )
          {
            std::string data;
						cout << "Waiting for command..." << endl;
  		      new_sock >> data;
            cout << "Received :: " << data << endl;
						if(data != "Stop")
						{
            	rounds = std::stoi(data);
							std::thread (ExecuteThreads_high, rounds).detach();
							std::thread (checkFinish).detach();
							cout << "Started Computing..." << endl;
						}
						else
						{
							cout << "Stopped... Check at other server for answer" << endl;
							stop = true;
							break;
						}
  		    }
  	  }
      catch ( SocketException& e) {
				//cout << e.description()<< endl;
			}
			cout << "------------ Completed Successfully ---------------\n";
  	}
  }
  catch ( SocketException& e )
  {
      cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }
}