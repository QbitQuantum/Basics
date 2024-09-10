int main ()
{
	stringFrequencies[0]=246.94;
	stringTensions[0]=15;
	TestControl.initializePort();
	sleep(2);
	
	tuneUpv2(0);
	
	TestControl.closePort();
	
	
	//TestControl.resetPosition("0");
	
	return 0;
}