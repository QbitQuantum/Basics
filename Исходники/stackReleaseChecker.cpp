int main(int argc, char *argv[])
{
    Oam oam;
	string systemUser = "******";
	string installParentModuleHostName;
	string password;
	string debug_flag = "1";
 	string systemName = "all";
	bool VERBOSE = false;

	Config* sysConfig = Config::makeConfig("./systems/CalpontSystems.xml");

   for( int i = 1; i < argc; i++ )
   {
      if( string("-h") == argv[i] ) {
			cout << endl;
			cout << "'stackReleaseChecker' retrieves and prints the release installed on a stack." << endl;
			cout << endl;
			cout << "The list of systems are located in './systems/CalpontSystems.xml" << endl;
			cout << endl;
   			cout << "Usage: stackReleaseChecker [-h][-s system][-v]" << endl;
			cout << "			-s system-name or leave blank for all systems" << endl;
			cout << "			-v verbose will give the version numbers" << endl;
			exit (0);
		}
      	else if( string("-s") == argv[i] ) {
			i++;
			if ( argc == i ) {
				cout << "ERROR: missing system argument" << endl;
				exit(-1);
			}
			systemName = argv[i];
		}
		else if( string("-v") == argv[i] )
			VERBOSE = true;
   }

	int systemCount;
	try {
		systemCount = strtol(sysConfig->getConfig("NetworkConfig", "SystemCount").c_str(), 0, 0);
		if ( systemCount == 0 ) {
			cout << "ERROR: SystemCount in ./systems/CalpontSystems.xml equal to 0" << endl;
			exit(-1);
		}
	}
	catch(...)
	{
		cout << "ERROR: Problem getting SystemCount from ./systems/CalpontSystems.xml" << endl;
		exit(-1);
	}

	bool FOUND = false;
	for ( int i = 1 ; i < systemCount+1 ; i++)
	{
		string SystemName = "SystemName" + oam.itoa(i);
		string oamParentModule = "OAMParentModule" + oam.itoa(i);
		string SystemPassword = "******" + oam.itoa(i);
		string SystemUser = "******" + oam.itoa(i);

		string tempSystem;
		try {
			tempSystem = sysConfig->getConfig("NetworkConfig", SystemName );
		}
		catch(...)
		{
			cout << "ERROR: Problem getting SystemName from ./systems/CalpontSystems.xml" << endl;
			exit(-1);
		}

		if ( tempSystem == systemName || systemName == "all") {
			try {
				installParentModuleHostName = sysConfig->getConfig("NetworkConfig", oamParentModule );
				password = sysConfig->getConfig("NetworkConfig", SystemPassword );
				systemUser = sysConfig->getConfig("NetworkConfig", SystemUser );
				FOUND = true;
			}
			catch(...)
			{
				cout << "ERROR: Problem getting SystemName from ./systems/CalpontSystems.xml" << endl;
				exit(-1);
			}

			if ( tempSystem == "unassigned")
				continue;

			//get if root or no-root user install
			string installDir = "/usr/local";
			if ( systemUser != "root" )
				installDir = "/home/" + systemUser;

			installDir = installDir + "/Calpont";

			string cmd;
			if (!VERBOSE)
				cmd = "./remote_command.sh " + installParentModuleHostName + " " + systemUser + " " + password + " 'cat " + installDir + "/releasenum' 'release=' cat: 10 " + debug_flag;
			else
				cmd = "./remote_command.sh " + installParentModuleHostName + " " + systemUser + " " + password + " '" + installDir + "/bin/calpontConsole getcalpontsoftware' 'tools' Error 10 " + debug_flag;

			cout << "***** Calpont InfiniDB Package Release Information for stack '" << tempSystem << "' *****" << endl << endl;

			system(cmd.c_str());

			cout << endl;

			cout << "***** Status of stack '" << tempSystem << "' *****" << endl << endl;

			cmd = "./remote_command.sh " + installParentModuleHostName + " " + systemUser + " " + password + " '" + installDir + "/bin/calpontConsole getsystems' dummy Error 10 " + debug_flag;

			system(cmd.c_str());

			cout << endl << endl;
		}
	}

	if ( !FOUND ) {
		cout << "ERROR: System Name '" + systemName + "' not in ./systems/CalpontSystems.xml" << endl;
		exit(-1);
	}
}