int main()
{
	ACE_OS::printf("\nHello from YARP!\n\n");

	char path[255];
	sprintf(path,"%s/%s", GetYarpRoot(), ConfigFilePath);

	// read positions from file
	_parseFile(path, posList, home);
	
	YARPArm arm;

	if (arm.initialize(path, "arm.ini") == YARP_OK)
		printf("Init was OK");
	else
	{
		printf("Init was NOT OK");
		exit(-1);
	}

	arm.activatePID();
	
	// go to home
	ACE_OS::printf("\nGoing home...\n");
 	setPositions(arm, home);
	YARPTime::DelayInSeconds(3.0);

	myList::iterator it,end;
	it = posList.begin();
	end = posList.end();
	while(it!=end)
	{
		setPositions(arm, (*it));
		it++;

		YARPTime::DelayInSeconds(3.0);
	}

	ACE_OS::printf("\nGoing back home");
 	setPositions(arm, home);
	YARPTime::DelayInSeconds(3.0);
	
	ACE_OS::printf("\ndone!\n");
	arm.uninitialize();
	
	return 0;
}