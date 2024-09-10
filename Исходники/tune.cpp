int main ()
{
	double freq;
	string readString;
	ofstream rawDat;
  	
	readTestCon();
	TestControl.initializePort();
	tuneUpv1(0);	
	tuneUpv1(1);
	tuneUpv1(2);

	rawDat.open ("elapsedTension.dat"); 
	TestControl.closePort();
	rawDat<<TestControl.getElapsedSteps(0)<<endl;
	rawDat<<TestControl.getElapsedSteps(1)<<endl;
	rawDat<<TestControl.getElapsedSteps(2)<<endl;
	rawDat.close();
	TestControl.closePort();
	
	
	return 0;
}