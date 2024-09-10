	// Implement echo
	virtual bool handler(std::shared_ptr<IComms> comms)
	{
std::cerr << "<TEST> handler - START" << std::endl;

		while (comms->isOpen())
		{
			TimeUtils::msSleep(200) ;
			if (!comms->isOpen())
				break ;

			std::string rx ;
			std::cerr << "<TEST> handler - Receive..." << std::endl;
			if (!comms->receive(rx))
				break ;

			// echo back
			if (!rx.empty())
			{
				std::cerr << "<TEST> handler - Echo" << std::endl;
				comms->send(rx) ;
			}
		}

std::cerr << "<TEST> handler - END" << std::endl;
		return false ;
	}