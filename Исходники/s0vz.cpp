int cfile() {
	int i = 0;
	Config cfg;

	//config_setting_t *setting;

	//config_init(&cfg);

	//int chdir(const char *path);

	//chdir ("/etc");
	//char configfile[200];
	std::stringstream configfile;
	#ifdef ENTWICKLUNG
	//sprintf(configfile, "%s%s", DAEMON_NAME, ".cfg");

	configfile << "./s0vz" << ".cfg";
	#else
	//sprintf(configfile, "%s%s%s", "/etc/", DAEMON_NAME, ".cfg");
	configfile << "/etc/" << DAEMON_NAME << ".cfg";
	#endif

	try
	{
		cfg.readFile(configfile.str().c_str());
	}
	catch(const FileIOException &fioex)
	{
		std::cerr << "I/O error while reading file." << std::endl;
		daemonShutdown();
		return(EXIT_FAILURE);
	}
	catch(const ParseException &pex)
	{
	    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
		return(EXIT_FAILURE);
	}

	try
	{
		if (cfg.lookupValue("Datafolder",Datafolder))
		{
			char *tmp = (char*) malloc(strlen(Datafolder)+1);
			memcpy(tmp,Datafolder,strlen(Datafolder)+1);
			Datafolder = tmp;
			syslog(LOG_INFO, "Datafolder:%s", Datafolder);
		}
	}
	catch(const SettingNotFoundException &nfex)
	{
		cerr << "No Datafolder setting in configuration file." << endl;
	}

	try
	{
		if (cfg.lookupValue("Messstelle",Messstellenname))
		{
			char *tmp = (char*) malloc(strlen(Messstellenname)+1);
			memcpy(tmp,Messstellenname,strlen(Messstellenname)+1);
			Messstellenname = tmp;
			syslog(LOG_INFO, "Messstelle:%s", Datafolder);
		}
	}
	catch(const SettingNotFoundException &nfex)
	{
		cerr << "No Messstelle setting in configuration file." << endl;
	}

	try
	{
		cfg.lookupValue("Mittelwertzeit", Mittelwertzeit);
		syslog(LOG_INFO, "Mittelwertzeit:%d", Mittelwertzeit);
	}
	catch(const SettingNotFoundException &nfex)
	{
		cerr << "No Mittelwertzeit setting in configuration file." << endl;
	}

	try
	{
		cfg.lookupValue("TempraturIntervall",tempraturIntervall);
		syslog(LOG_INFO, "TemperaturInterval:%d", tempraturIntervall);
	}
	catch(const SettingNotFoundException &nfex)
	{
		cerr << "No TempraturIntervall setting in configuration file." << endl;
	}

	try
	{
		cfg.lookupValue("LogLevel", LogLevel);
		syslog(LOG_INFO, "LogLevel:%d", LogLevel);
	}
	catch(const SettingNotFoundException &nfex)
	{
		LogLevel = 4;
		cerr << "No LogLevel setting in configuration file." << endl;
	}

	stringstream name;
	for (i = 0; i < inputs; i++) {
		name.str("");
		name << "GPIO" << i;
		try
		{
			cfg.lookupValue(name.str(),Impulswerte[i]);
			syslog( LOG_INFO, "%s = %d", name.str().c_str(), Impulswerte[i]);
		}
		catch(const SettingNotFoundException &nfex)
		{
			cerr << "No " << name.str() << " setting in configuration file." << endl << std::flush;
		}
	}

	tempSensors = 0;
	for (i = 0; i < 100; i++) {
		name.str("");
		name << "W1Dev" << i;
		try
		{
			if (cfg.lookupValue(name.str(),W1Sensor[i]))
			{
				//cout << "Sensor ID: " << W1Sensor[i] << endl << std::flush;
				char *tmp = (char*) malloc(strlen(W1Sensor[i])+1);
				memcpy(tmp,W1Sensor[i],strlen(W1Sensor[i])+1);
				W1Sensor[i] = tmp;

				syslog( LOG_INFO, "%s = %s", name.str().c_str(), W1Sensor[i]);
				tempSensors++;

			}
		}
		catch(const SettingNotFoundException &nfex)
		{
			cerr << "No " << name.str() << " setting in configuration file." << endl << std::flush;
		}
	}

	try
	{
		if (cfg.lookupValue("EnOceanDevice",EnOceanDevice))
		{
			char *tmp = (char*) malloc(strlen(EnOceanDevice)+1);
			memcpy(tmp,EnOceanDevice,strlen(EnOceanDevice)+1);
			EnOceanDevice = tmp;
			syslog(LOG_INFO, "EnOceanDevice:%s", EnOceanDevice);
		}
	}
	catch(const SettingNotFoundException &nfex)
	{
		cerr << "No EnOceanDevice setting in configuration file." << endl;
	}


	enOceanNumberSensors = 0;
	stringstream name2;
		for (i = 0; i < 100; i++) {
			name.str("");
			name2.str("");
			name << "EnOceanSensor" << i;
			name2 << "EnOceanAria" << i;
			try
			{
				if (cfg.lookupValue(name.str(),EnOceanSensor[i]) &&
					cfg.lookupValue(name2.str(),EnOceanTemperaturbereich[i]))
				{
					char *tmp = (char*) malloc(strlen(EnOceanSensor[i])+1);
					memcpy(tmp,EnOceanSensor[i],strlen(EnOceanSensor[i])+1);
					EnOceanSensor[i] = tmp;
					tmp = (char*) malloc(strlen(EnOceanTemperaturbereich[i])+1);
					memcpy(tmp,EnOceanTemperaturbereich[i],strlen(EnOceanTemperaturbereich[i])+1);
					EnOceanTemperaturbereich[i] = tmp;

					//cout << "Sensor ID: " << W1Sensor[i] << endl << std::flush;
					syslog( LOG_INFO, "%s = %s aria %s", name.str().c_str(), EnOceanSensor[i],
														EnOceanTemperaturbereich[i]);
					enOceanNumberSensors++;
				}
			}
			catch(const SettingNotFoundException &nfex)
			{
				cerr << "No " << name.str() << " setting in configuration file." << endl << std::flush;
			}
		}

	return 0;
}