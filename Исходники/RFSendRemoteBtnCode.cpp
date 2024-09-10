/* ---------------------------------------------------------------- */
int main(int argc, char *argv[]) 
{  
    parseCommandLineArgs(argc, argv);
	
	ifstream jsonFile;
	string rfJsonFilePath = "./radioFrequenceSignalConfig.json";

	int repeat				= 10;	
	int protocol			= 1;	
	int pin					= 0;
	double pulseLength 		= 0;
	long signalBitNumber	= 0;

   	int decimalcode			= 0;
   	int nbbit				= 24;
   	
   	string remote	 		= "";
   	bool isManchesterCoded	= false;
   	string binarycode		= "";	
    	
	std::map<std::string,std::string>::iterator it;

	it = commandArgs.find("lev");
	if( commandArgs.find("lev") != commandArgs.end()) loglevel=atoi(it->second.c_str());

	if( commandArgs.find("listremotes") == commandArgs.end() && commandArgs.find("getremotebuttons") == commandArgs.end() )
		displayCommandLineArgs();
	
	it = commandArgs.find("jsonconf");
	if(it != commandArgs.end())		rfJsonFilePath=commandArgs["jsonconf"].c_str();
	// chargement de la conf (fichier json contenant toutes les infos des télécommandes radiofréquence)
	jsonFile.open(rfJsonFilePath.c_str());		
	bool parsedResult = jsonReader.parse(jsonFile, jsonRoot, false);
	jsonFile.close();
	if(!parsedResult) // Report failures and their locations in the document.
	{
		string str = "Echec d'analyse du fichier " + rfJsonFilePath + " : \n" + jsonReader.getFormatedErrorMessages() + "\n";
		trace(3,str.c_str());		
		return 1;
	}

	it = commandArgs.find("listremotes");
	if( commandArgs.find("listremotes") != commandArgs.end()) {diplayRemotes(); return 0;}

	it = commandArgs.find("repeat");
	if(it != commandArgs.end())		repeat=atoi(commandArgs["repeat"].c_str());
	
	it = commandArgs.find("remote");
	if(it != commandArgs.end())		remote=commandArgs["remote"];
	else
	{
		trace(3,"Parameter remote must be set (-remote=<value>) with one of the following values");
		diplayRemotes();
		return 1;
	}

    // Parse the firt parameter to this command as an integer
    if (wiringPiSetup () == -1) return 1;
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(pin);    
    mySwitch.setRepeatTransmit(repeat);
    mySwitch.setProtocol(protocol);
    
    //-------- Getting protocol signal information from json document ---------//
    Json::Value remoteNode = jsonRoot[remote];    
    if (remoteNode.isNull())
    {
		trace(3,"Unknown remote");
		diplayRemotes();
		return 2;
	}
    
    Json::Value protocolNode 		= remoteNode["protocol"];
    if (protocolNode.isNull() || !protocolNode.isInt())
    {
		string str = INVALIDE_REMOTE_PROP + remote + " 'protocol' is not set or is not an integer";
		trace(3, str.c_str());
		return 3;
	}
    else  {protocol 		= protocolNode.asInt();}
    
    Json::Value pulseLengthNode 	= remoteNode["pulseLength"];
    if (pulseLengthNode.isNull()) 	
    {
		string str = INVALIDE_REMOTE_PROP + remote + " 'pulseLength' is not set or is not an integer";
		trace(3, str.c_str());
		return 4;
	}
    else 							pulseLength 	= pulseLengthNode.asInt();
    
    Json::Value signalBitNumberNode = remoteNode["SignalBitNumber"];
    if (signalBitNumberNode.isNull()) 	{}
    else 							signalBitNumber = signalBitNumberNode.asInt();

    Json::Value signalsNode = remoteNode["signals"];
    if (signalsNode.isNull()) 		
    {
		string str = INVALIDE_REMOTE_PROP + remote + " 'signals' is not or not correctly set";
		trace(3, str.c_str());
		return 5;
	}
    else 							
    {
		Value::Members membersOfSignals = signalsNode.getMemberNames();		
		it = commandArgs.find("getremotebuttons");
		if( commandArgs.find("getremotebuttons") != commandArgs.end() )		
			{diplayButtonsForRemote(membersOfSignals); return 0;}
		
		it = commandArgs.find("btn");
		if(it == commandArgs.end())	
		{
			trace(3, "Parameter 'btn' must be set (-btn=<value>) with one of the following values");
			diplayButtonsForRemote(membersOfSignals);
			return 6;
		}
		else
		{
			string btnName = commandArgs["btn"];
			jsonSignal = signalsNode[btnName];
			if (jsonSignal.isNull())									
			{
				string str = INVALIDE_REMOTE_PROP + remote + " button:" + btnName + " Signal code is not set";
				trace(3, str.c_str());
				return 7;
			}
			else if (!jsonSignal.isArray() && (!jsonSignal.isInt())) 	
			{
				string str = INVALIDE_REMOTE_PROP + remote + " button:" + btnName + " Signal code is neither an array nor an integer";
				trace(3, str.c_str());
				return 8;
			}
		}
	}


	// Assertion sur signalBitNumberNode!=0 ou jsonSignal.isArray()
	if (signalBitNumber == 0 && !jsonSignal.isArray() )
	{
		trace(3, "Propeties of remote are invalid : either 'signalBitNumberNode' must be set or each button signal must be an array of bit values (0,1) ");
		return 9;
	}

	//------------------------ Getting protocole info for this remote -----------------//
	string protocole = "protocole" + patch::to_string(protocol);
	Json::Value protocoleInfoNode = jsonRoot[protocole];
	if (protocoleInfoNode.isNull())
	{
		string str = INVALIDE_REMOTE_PROP + remote + " : remote protocol '" + protocole	+ "' doesn't exist in declared protocols ";
		trace(3, str.c_str());
		return 10;
	}

	
	Json::Value  presendSignalCodeTransformationNode = remoteNode["PresendSignalCodeTransformation"];
	if (!presendSignalCodeTransformationNode.isNull())
	{
		string presendSignalCodeTransformationValue = presendSignalCodeTransformationNode.asString();
		if (presendSignalCodeTransformationValue.find("MANCHESTER") != string::npos)
		{isManchesterCoded = true;}
	}
	else
	{
		Json::Value  protocol_presendSignalCodeTransformationNode 	= protocoleInfoNode["PresendSignalCodeTransformation"];
		if (!protocol_presendSignalCodeTransformationNode.isNull() && protocol_presendSignalCodeTransformationNode.asString().find("MANCHESTER") != string::npos)
		{isManchesterCoded = true;}
	}

	//------------------ Getting Start lock HIGH-->LOW pulses ---------//
	Json::Value  startlock_highlowNode 	= remoteNode["startlock_highlow"];
	if (!startlock_highlowNode.isNull()) 	// startlock_highlow est précisé dans les info du button de la remote
	{
		if (!startlock_highlowNode.isArray() || startlock_highlowNode.size() != 2)
		{
			string str = INVALIDE_REMOTE_PROP + remote + "' : startlock_highlow is not an array or is not well set";
			trace(3, str.c_str());
			return 10;
		}
		else
		{
			startlock_highlow[0] = startlock_highlowNode[0].asInt();
			startlock_highlow[1] = startlock_highlowNode[1].asInt();
		}
	}
	else  									// Retrouver le noeud protocole et en déduire startlock_highlow
	{		
		Json::Value startlock_highlowNode =  protocoleInfoNode["startlock_low_NbPulseLength"];
		if (startlock_highlowNode.isNull()) 	
		{
			string str = INVALIDE_REMOTE_PROP + remote + "' : startlock_highlow array is neither set in btn, nor in protocol";
			trace(3, str.c_str());
			return 11;
		}
		else if (startlock_highlowNode.isDouble())
		{
			startlock_highlow[0] = pulseLength;
			startlock_highlow[1] = startlock_highlowNode.asDouble() * pulseLength;
		}
		else // must be an integer
		{
			string str = INVALIDE_REMOTE_PROP + remote + "' : startlock_highlow must be an integer";
			trace(3, str.c_str());
			return 12;
		}
	}

	//------------------ Getting End lock HIGH-->LOW pulses ---------//
	Json::Value  endlock_highlowNode 	= remoteNode["endlock_highlow"];
	if (!endlock_highlowNode.isNull())
	{
		if (!endlock_highlowNode.isArray() || endlock_highlowNode.size() != 2)
		{
			string str = INVALIDE_REMOTE_PROP + remote + "' : endlock_highlow is not an array or is not well set";
			trace(3, str.c_str());
			return 13;
		}
		else
		{
			endlock_highlow[0] = endlock_highlowNode[0].asInt();
			endlock_highlow[1] = endlock_highlowNode[1].asInt();
		}
	}
	else  									// Retrouver le noeud protocole et en déduire endlock_highlow
	{		
		Json::Value endlock_highlowNode =  protocoleInfoNode["endlock_low_NbPulseLength"];
		if (endlock_highlowNode.isNull()) 	
		{
			string str = INVALIDE_REMOTE_PROP + remote + "' : endlock_highlow array is neither set in btn, nor in protocol";
			trace(3, str.c_str());
			return 14;
		}
		else if (endlock_highlowNode.isDouble())
		{
			endlock_highlow[0] = pulseLength;
			endlock_highlow[1] = endlock_highlowNode.asDouble() * pulseLength;
		}
		else // must be an integer
		{
			string str = INVALIDE_REMOTE_PROP + remote + "' : endlock_highlow must be an integer";
			trace(3, str.c_str());
			return 15;
		}
	}	

	//------------------ Getting zeroEncodingInNbPulse HIGH-->LOW pulses ---------//
	Json::Value  protocol_zeroEncodingInNbPulseNode = protocoleInfoNode["ZeroEncoding_highlow_NbPulseLength"];
	Json::Value  zeroEncodingInNbPulseNode 			= remoteNode["ZeroEncodingInNbPulse"];
	if (!zeroEncodingInNbPulseNode.isNull() && zeroEncodingInNbPulseNode.isArray())
	{
		zeroEncoding_highlow[0] = zeroEncodingInNbPulseNode[0].asDouble();
		zeroEncoding_highlow[1] = zeroEncodingInNbPulseNode[1].asDouble();
	}
	else if (!protocol_zeroEncodingInNbPulseNode.isNull() && protocol_zeroEncodingInNbPulseNode.isArray())
	{
		zeroEncoding_highlow[0] = protocol_zeroEncodingInNbPulseNode[0].asDouble() * pulseLength;
		zeroEncoding_highlow[1] = protocol_zeroEncodingInNbPulseNode[1].asDouble() * pulseLength;
	}
	else
	{
		string str = INVALIDE_REMOTE_PROP + remote + " : 'zeroEncoding_highlow' parameter must be an array and must be set either in 'remote node' or in 'protocol' node";
		trace(3, str.c_str());
		return 16;
	}
	
	//------------------ Getting oneEncodingInNbPulse HIGH-->LOW pulses ---------//
	Json::Value  protocol_oneEncodingInNbPulseNode 	= protocoleInfoNode["OneEncoding_highlow_NbPulseLength"];
	Json::Value  oneEncodingInNbPulseNode 			= remoteNode["OneEncodingInNbPulse"];
	if (!oneEncodingInNbPulseNode.isNull() && oneEncodingInNbPulseNode.isArray())
	{
		oneEncoding_highlow[0] = oneEncodingInNbPulseNode[0].asDouble();
		oneEncoding_highlow[1] = oneEncodingInNbPulseNode[1].asDouble();
	}
	else if (!protocol_oneEncodingInNbPulseNode.isNull() && protocol_oneEncodingInNbPulseNode.isArray())
	{
		oneEncoding_highlow[0] = protocol_oneEncodingInNbPulseNode[0].asDouble() * pulseLength;
		oneEncoding_highlow[1] = protocol_oneEncodingInNbPulseNode[1].asDouble() * pulseLength;
	}
	else
	{
		string str = INVALIDE_REMOTE_PROP + remote + " : 'oneEncoding_highlow' parameter must be an array and must be set in 'remote node' or in 'protocol' node";
		trace(3, str.c_str());
		return 17;
	}

	//---------------------------------------------- Traitement d'envoi du signal --------------------------------------------------//
	if (jsonSignal.isArray())
	{
		remotecodestring = "";
		for(unsigned int index=0; index<jsonSignal.size(); ++index)  
			remotecodestring.append(jsonSignal[index].asString());	
		strcpy(remotecode,remotecodestring.c_str());
	}
	else // c'est un entier
	{
		decimalcode = jsonSignal.asInt();
		strcpy(remotecode,dec2binWzerofill(decimalcode,signalBitNumber));
	}

	if (isManchesterCoded) // Codage manchester si nécessaire
	{
		string binarycode = "";
    	for(int i=0;i<strlen(remotecode);i++)
    	{
    		if (remotecode[i]=='0')	    		binarycode.append("01");
	    	else if (remotecode[i]=='1')		binarycode.append("10");
	    	else 
	    	{
				string str = " Invalid manchester coded signal : ";  str += remotecode;
	    		trace(3, str.c_str());
	    		return 18;
	    	}
    	}
    	strcpy(remotecode,binarycode.c_str());
	}

	// positionner les paramètres de mySwitch : pulseLength, protocole, etc ...
	mySwitch.setRepeatTransmit(repeat);
	mySwitch.setPulseLength(pulseLength);
	mySwitch.setProtocol(protocol);
	mySwitch.setSendZeroEncodingInNbPulse(zeroEncoding_highlow[0]/pulseLength, zeroEncoding_highlow[1]/pulseLength);
	mySwitch.setSendOneEncodingInNbPulse(oneEncoding_highlow[0]/pulseLength, oneEncoding_highlow[1]/pulseLength);

	mySwitch.setSendStartLockHighLowInNbPulse(startlock_highlow[0]/pulseLength, startlock_highlow[1]/pulseLength);
	mySwitch.setSendEndLockHighLowInNbPulse(endlock_highlow[0]/pulseLength, endlock_highlow[1]/pulseLength);

	cout << "> Sending raw code = '"<< remotecode << "' > " << endl;
	if (loglevel <= 1)
	{
		cout << "  Number of bit    = " << strlen(remotecode) << endl;
		cout << "  Manchester       = " << isManchesterCoded << endl;
		cout << "  Protocole        = " << protocol	<< endl;
		cout << "  ZeroEncoding     = " << zeroEncoding_highlow[0] 	<< "," << zeroEncoding_highlow[1] 	<< endl;
		cout << "  OneEncoding      = " << oneEncoding_highlow[0] 	<< "," << oneEncoding_highlow[1] 	<< endl;
		cout << "  StartLock        = " << startlock_highlow[0] 	<< "," << startlock_highlow[1] 		<< endl;
		cout << "  EndLock          = " << endlock_highlow[0] 		<< "," << endlock_highlow[1] 		<< endl;
		cout << "  Repeat           = " << repeat 		<< endl;
	}
	if (loglevel <= 0)
		cout << mySwitch.computeAndDisplaySignalToSend(remotecode);
	
	
	mySwitch.send(remotecode);
 	cout << "< Sent <" << endl;
	   
	return 0;
}