int main (int argc,char *argv[])
{
	
	int inputString = atoi(argv[1]);
	readTestCon();	
	TestControl.initializePort();
	sleep(2);
	TestControl.sampleString(inputString);
	cout<<"Frequency:"<<TestControl.getFreq(stringFrequencies[inputString])<<endl;
	TestControl.closePort();
	
	
	
	
	return 0;
}