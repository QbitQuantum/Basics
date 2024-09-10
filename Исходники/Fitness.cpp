int Fitness::getStats(int currExperimentNumber, int levelNum, bool parentTest)
{
	if (experimentNumber != currExperimentNumber)//if the stored experiment number is not equal to the experiment number that can been passed in.
	{
		experimentNumber = currExperimentNumber;
		concat.str("");
		concat << "..\\..\\GenerationStats\\Experiment-" << experimentNumber;
		directoryName = concat.str();
		if (!CreateDirectoryA(directoryName.c_str(), NULL))
		{
			if (ERROR_PATH_NOT_FOUND == GetLastError())
			{
				cout << "Unable to Create Experiment Directory, Please Check Filepath - from spelunky_1_1 folder it should be ..\\..\\GenerationStats\\Experiment-X." << endl;
			}
			else
			{
				if (ERROR_ALREADY_EXISTS == GetLastError()) //if folder already exists.
				{
					bool done = 0;
					while (!done)
					{
						concat.str("");
						experimentNumber++;
						concat << "..\\..\\GenerationStats\\Experiment-" << experimentNumber;
						directoryName = concat.str();
						if (CreateDirectoryA(directoryName.c_str(), NULL))
						{
							done = 1;
						}
						else if (ERROR_PATH_NOT_FOUND == GetLastError())
						{
							cout << "Unable to Create Experiment Directory, Please Check Filepath - from spelunky_1_1 folder it should be ..\\..\\GenerationStats\\Experiment-X." << endl;
						}
					}
				}
			}
		}
	}

	if (!parentTest)
	{
		//Calculate standard deviation
		for (int i = 0; i < avgFitness.size(); i++)
		{
			populationAverage = populationAverage + avgFitness.at(i);
			if (avgFitness.at(i) > highestScore)
			{
				highestScore = avgFitness.at(i);
			}
		}
		populationAverage = populationAverage / avgFitness.size(); // This gives us the mean fitness score.

		for (int j = 0; j < avgFitness.size(); j++)
		{
			standardDeviation = standardDeviation + pow(avgFitness.at(j) - populationAverage, 2);
		}
		standardDeviation = standardDeviation / avgFitness.size(); //This gets us the average distance from the mean squared.
		standardDeviation = sqrt(standardDeviation); //This gives us the standard deviation


		//Send standard deviation information to file for import into Excel spreadsheet.

		concat.str("");
		concat << "..\\..\\GenerationStats\\Experiment-" << experimentNumber << "\\GenerationsData-Level-" << levelNum << ".txt";
		directoryName = concat.str();
		fileStream.open(directoryName.c_str(), ofstream::app);
		if (fileStream.is_open())
		{
			concat.str("");
			concat << populationAverage << "," << standardDeviation << "," << highestScore;
			fileStream << concat.str() << endl;
		}
		else
		{
			cout << "Unable to write Generation Statistics data to file." << endl;
		}

		fileStream.close();
		standardDeviation = 0;
		populationAverage = 0;
		highestScore = 0;
	}
	else
	{
		concat.str("");
		concat << "..\\..\\GenerationStats\\Experiment-" << experimentNumber << "\\ParentsData-Level-" << levelNum << ".txt";
		directoryName = concat.str();
		fileStream.open(directoryName.c_str(), ofstream::app);
		if (fileStream.is_open())
		{
			for (int k = 0; k < avgFitness.size(); k++)
			{
				concat.str("");
				concat << avgFitness.at(k);
				fileStream << concat.str() << endl;
			}
		}
		else
		{
			cout << "Unable to write Parent data to file." << endl;
		}
		fileStream.close();
	}

	return experimentNumber;
}