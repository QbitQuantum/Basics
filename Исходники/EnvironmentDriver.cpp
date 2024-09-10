    void EnvironmentDriver::InitSockets(int num_agents, int num_displays)
    {
      if(!mListenSocket->Listen(mOptions.GetArgInt("port")))
	exit(1);
      
      std::string buffer;
      while(num_agents > 0 || num_displays > 0)
	{
	  std::cerr << "Waiting for " << num_agents << " agent(s) and " << num_displays << " display(s) to connect..." << std::endl;
	  Socket * client = mListenSocket->Accept();
	  if(!client)
	    {
	      continue;
	    }
	  if(!client->Send("IDENT") || !client->Recv(buffer))
	    {
	      delete client;
	      continue;
	    }
	  if(buffer == "AGENT" && num_agents > 0)
	    {
	      mAgentSockets.push_back(client);
	      num_agents--;
	    }
	  else if(buffer == "DISPLAY" && num_displays > 0)
	    {
	      mDisplaySockets.push_back(client);
	      num_displays--;
	    }
	  else
	    {
	      delete client;
	    }
	}
      std::cerr << "All agents and displays connected" << std::endl;
    }