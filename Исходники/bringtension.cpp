int main (int argc,char *argv[])
{
	

	double tension;
	readTestCon();

	TestControl.initializePort();
	if(argc == 1)
	{
		

	}
	else
	{
		int inputString = atoi(argv[1]);
				
		tension=TestControl.sampleTens(inputString);
		cout<<"Desired Tension: "<<stringTensions[inputString]<<endl;
		while(tension < (stringTensions[inputString]-2)  && tension < 98 )
		{	
			tension=TestControl.sampleTens(inputString);		
			cout<<tension<<endl;
			if(tension < stringTensions[inputString])
				TestControl.motorStep(inputString, 250, 0);
			tension=TestControl.sampleTens(inputString);		
			cout<<tension<<endl;
		}


	}

	TestControl.closePort();
	
	
	
	
	return 0;
}