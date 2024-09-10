int main()
{

	double Expiry=1;
	//double Low,Up; 
	double Spot=100; 
	double Vol=0.15; 
	double r=0.05; 
	unsigned long NumberOfPaths=100000;
    double Strike[1];
	Strike[0]=50;
	Strike[1]=200;
    std::string name;

    cout << "\npay-off name\n";
    cin >> name;

 //   cout << "Enter strike 1\n";
 //   cin >> Strike[0];
 //  
	//cout << "Enter strike 2 (for double barrier for example)\n";
	//cin >> Strike[1];


// create an option of type name with give strike(s) from the factory
    PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(name,Strike); 
	//now convert this payoffptr to a VanillaOption to plug in to SimpleMonteCarlo6
	VanillaOption theOption(*PayOffPtr, Expiry);

    if (PayOffPtr != NULL)
    {
		//  double Spot=100;

	    //cout << "\nspot\n";
		//   cin >> Spot;

        cout << "\n PayOff with Spot " << Spot  << " is "<< PayOffPtr->operator ()(Spot) << "\n"; 
		cout << "\n PayOff with Spot " << Spot  << " is "<< (*PayOffPtr)(Spot) << "\n";    // these two are the same.

		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);

		StatisticsMean gatherer;
		ConvergenceTable gathererTwo(gatherer);

		RandomParkMiller generator(1);
		//RandomMersTwister generator(1);
		AntiThetic GenTwo(generator);

		//using the MC routine in SimpleMC8 - the first argument is of type VanillaOption so we have
		// converted PayOffPtr genearated by the factory to theOption - which is of type VanillaOption
		// (VanillaOption contains the expirty time as extra information)
		SimpleMonteCarlo6(theOption,
                                      Spot, 
                                      VolParam,
                                      rParam,
                                      NumberOfPaths,
                                      gathererTwo,
									  generator); // no Antithetic
                                      //GenTwo); // Antithetic

		vector<vector<double> > results =gathererTwo.GetResultsSoFar();

		cout <<"\nFor the " << name << " price the results are \n";
		for (unsigned long i=0; i < results.size(); i++)
		{
			for (unsigned long j=0; j < results[i].size(); j++)
				cout << results[i][j] << " ";

				cout << "\n";
		}

        delete PayOffPtr;
    }
    
    double tmp;
    cin >> tmp;
    return 0;
}