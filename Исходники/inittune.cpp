int main ()
{
	double freq;
	string readString;
	ofstream rawDat;
  	
	readTestCon();
	TestControl.initializePort();
	//tuneUpv2(0);	
	//tuneUpv2(1);
	tuneUpv2(2);
	/*
	rawDat.open ("elapsedTension.dat"); 
	TestControl.closePort();
	rawDat<<TestControl.getElapsedSteps(0)<<endl;
	rawDat<<TestControl.getElapsedSteps(1)<<endl;
	rawDat<<TestControl.getElapsedSteps(2)<<endl;
	rawDat.close();*//*
	for(int i=0; i<10; i++)
	{
		TestControl.sampleString(0);
		cout<<TestControl.getFreq(stringFrequencies[0])<<endl;
	}*/
	TestControl.closePort();
	
	
	return 0;
}