/* ---------------------------------------------------------------- */
int main(int argc, char *argv[]) 
{  
    parseCommandLineArgs(argc, argv);
	displayCommandLineArgs();
	
	ifstream jsonFile;
	string rfJsonFilePath = "./radioFrequenceSignalConfig.json";
	jsonFile.open(rfJsonFilePath.c_str());
		
	//bool parsedSuccess = reader.parse(json_example, root, false);
	bool parsedResult = jsonReader.parse(jsonFile, jsonRoot, false);
	jsonFile.close();
	
	if(!parsedResult) // Report failures and their locations in the document.
	{
		cout<<"Echec d'analyse du fichier " << rfJsonFilePath << " : " << endl << jsonReader.getFormatedErrorMessages() << endl;
		return 1;
	}
	
	int repeat						= 10;	
	int protocol					= 1;	
	int pin							= 0;	

   	int decimalcode			= 0;
   	int nbbit						= 24;
   	
   	string manchbin 			= "";
   	string binarycode		= "";	
    	
    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
	
	std::map<std::string,std::string>::iterator it;
	it = commandArgs.find("repeat");
	if(it != commandArgs.end())		repeat=atoi(commandArgs["repeat"].c_str());
	
	it = commandArgs.find("protocol");
	if(it != commandArgs.end())		protocol=atoi(commandArgs["protocol"].c_str());
	
	it = commandArgs.find("pin");
	if(it != commandArgs.end())		pin=atoi(commandArgs["pin"].c_str());
	
	it = commandArgs.find("dec");
	if(it != commandArgs.end())		decimalcode=atoi(commandArgs["dec"].c_str());

	it = commandArgs.find("nbbit");
	if(it != commandArgs.end())		nbbit=atoi(commandArgs["nbbit"].c_str());
	
	it = commandArgs.find("bin");
	if(it != commandArgs.end())		binarycode=commandArgs["bin"];

	it = commandArgs.find("manchbin");
	if(it != commandArgs.end())		manchbin=commandArgs["manchbin"];
	
	// Assertion arguments bien positionnés
	int isSet = 0;
	if (decimalcode !=0) 			isSet++;
	if (binarycode.length() !=0)  	isSet++;
	if (manchbin.length() !=0) 		isSet++;
	if (isSet != 1)
	{
		cout << " One and only one of the following argument must be set : dec (with nbbit), bin,  manchbin" << endl;
		return 2;
	}
	// Assertion si décimal code set, alors nbbit doit l'etre
	if (decimalcode !=0 && nbbit==0)
	{
		cout << " dec is set without nbbit ; nbbit must be set too ..." << endl;
		return 3;
	}
	
	// Assertion protocol
	if (protocol < 1 || protocol > 3)
	{
		cout << " protocol must set between 1 and 3" << endl;
		return 4;
	}
	
    // Parse the firt parameter to this command as an integer
    if (wiringPiSetup () == -1) return 1;
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(pin);    
    mySwitch.setRepeatTransmit(repeat);
    mySwitch.setProtocol(protocol);
    
    // Get protocol signal from json document
    //jsonRoot[];
    
    
    
    if (decimalcode != 0)
    {
		cout << "sending decimal code='" << decimalcode << "'  ...";
   	 	mySwitch.send(decimalcode, nbbit);
   	 	cout << " sent" << endl;
    }
    else if (binarycode.length() != 0)
    {
		cout << "sending binary code " << binarycode << "...";
    	mySwitch.send((char*)binarycode.c_str());
   	 	cout << " sent" << endl;
    }
    else // manchesterCode
    {
    	binarycode = "";
    	const char * manchesterCode = manchbin.c_str();
    	for(int i=0;i<manchbin.length();i++)
    	{
    		if (manchesterCode[i]=='0')	    		binarycode.append("01");
	    	else if (manchesterCode[i]=='1')		binarycode.append("10");
	    	else 
	    	{
	    		cout << " Invalid manchester coded signal : " << manchbin << endl;
	    		return 4;
	    	}
    	}
		cout << "sending manchester binary code=" << manchbin << " true code is=" << binarycode << "...";
    	mySwitch.send((char*)binarycode.c_str());
   	 	cout << " sent" << endl;
    }
	return 0;
}