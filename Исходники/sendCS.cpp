int main (int argc, char** argv)
{
	if (setuid(0))
	{
		perror("setuid");
		return 1;
	}

	piHiPri(99); // Put process in real-time mode

	log("Demarrage du programme");
	pin = atoi(argv[1]);
	sender = atoi(argv[2]);
	if (strcmp(argv[3],"portal")==0) {
		interruptor = -1;
	} else {
		if (argv[3][0]=='a')
			group=42;
		else if (argv[3][0]=='b')
			group=138;
		else if (argv[3][0]=='c')
			group=162;
		else if (argv[3][0]=='d')
			group=168;
		else {
			group=-1;
			interruptor = atoi(argv[3]);
		}
		if (group != -1) {
			if (argv[3][1]=='1')
				interruptor=10;
			else if (argv[3][1]=='2')
				interruptor=34;
			else if (argv[3][1]=='3')
				interruptor=40;
		}
	}
	onoff = argv[4];
	pulse =(argc==6)? atoi(argv[5]) : 0;

	//Si on ne trouve pas la librairie wiringPI, on arrête l'execution
    if(wiringPiSetup() == -1)
    {
        log("Librairie Wiring PI introuvable, veuillez lier cette librairie...");
        return -1;
    }
	
	if (interruptor == -1) {
		log("Lancement en mode RCSwitch ...");
		RCSwitch mySwitch = RCSwitch();
		mySwitch.enableTransmit(pin);
		mySwitch.setProtocol(5);
		mySwitch.setRepeatTransmit(10);
		mySwitch.send(const_cast<char*>(onoff.c_str()));
		if (pulse > 0) {
			delay(pulse);
			mySwitch.send(const_cast<char*>(onoff.c_str()));
		}
	} else if (group != -1) {
		log("Lancement en mode Casto ...");
                RCSwitch mySwitch = RCSwitch();
                mySwitch.enableTransmit(pin);
                mySwitch.setProtocol(1);
                mySwitch.setRepeatTransmit(10);
		group = group << 15;
		interruptor = interruptor << 9;
		int separator = 42;
		separator = separator << 3;
		long localCode = group + interruptor + separator;
		if(onoff=="on"){
			localCode += 7;
		} else if (onoff=="off") {
			localCode += 4;
		} else
			log("Mode not implemented.");
                mySwitch.send(localCode,24);
	} else {
		log("Lancement en mode DIO ...");
		pinMode(pin, OUTPUT);
		log("Pin GPIO configure en sortie");
		itob(sender,26);
		itobInterruptor(interruptor,4);
		if(onoff=="on"){
			action(true);
		} else if (onoff=="off"){
			action(false);	 
		} else {
			action(true);
			delay(pulse);
			action(false);
		}
	}
	log("Fin du programme");    // execution terminée.

}