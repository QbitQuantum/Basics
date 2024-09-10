int main(int argc, char* argv[])
{	
#if !defined(_DEBUG) && defined(_WIN32)
	SetUnhandledExceptionFilter(CreateMiniDump);
#endif

	// The second argument on the command line should be the zone name.
	//OnlyInstallUnhandeldExceptionFilter(); // Part of stackwalker
	char zone[50];
	if(argc < 2)
	{
		printf("A list of Zones can be found in ZoneList.txt\n");
		printf("Enter zone: ");
		int n = scanf("%s", zone);

		if (n != 1)
			std::exit(-1);

		// Remove the // if it cause problems, This enables you to just type
		// inn the zone insted of navigate using comand prompt.
		//std::exit(-1);
	}
	else
	{
		sprintf(zone,"%s",argv[1]);
	}

	int8 logfileName[64], configfileName[64];
	sprintf(logfileName, "%s.log", zone);
	sprintf(configfileName, "%s.cfg", zone);

	LogManager::Init(G_LEVEL_NORMAL,logfileName,LEVEL_NORMAL,true,true);
	ConfigManager::Init(configfileName);

	// Start things up
	gZoneServer = new ZoneServer((int8*)(gConfig->read<std::string>("ZoneName")).c_str());

	// Main loop
	while(1)
	{
		if(AdminManager::Instance()->shutdownZone())
		{
			break;
		}
		else if (Anh_Utils::kbhit())
		{
			if(std::cin.get() == 'q')
			{
				break;
			}
		}

		gZoneServer->Process();
		gMessageFactory->Process(); //Garbage Collection

        boost::this_thread::sleep(boost::posix_time::milliseconds(1));

	}

	// Shut things down

	delete gZoneServer;
	gZoneServer = NULL;

	return 0;
}