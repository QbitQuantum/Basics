void initVariables()
{
	// Riempie la lista dei fattori a partire da quanto descritto nei fattori dell'oggetto parameters
	// Per dubbi prova i vari esempi di test del modulo experiments
	for(int i=0;i<ROUNDS;i++)
	{
		srand(timer.getElapsedTimeInMicroSec());
		timer.sleep(1000);
		trial[i].init(parameters);
		cerr << "round" << endl;
		trial[i].print();
	}
	middlePos = (str2num<double>(parameters.find("TrainingDist"))+str2num<double>(parameters.find("CatchDist")))/2.0;
}