TSPtour SimulatedAnnealing(TSPtour tour, TSPadjMatrix adjM)
{
	double maxTemp = 150;
	double temperature = maxTemp;
	double coolingRate = 0.999999;
	double minTemp = 1;
	int iteration = 0;
	int cycles = 10000000;
	int curDist = calcTourLen(tour, adjM);
	int lastDist = curDist;
	int bestDist = curDist;
	TSPtour tempTour;
	tempTour.length = tour.length;
	tempTour.tour = new int[tour.length];
	for (int j = 0; j < tour.length; j++)
	{
		tempTour.tour[j] = tour.tour[j];
	}
	closeCities closeBy = genCloseByCities(adjM);
	int improvements = 0;
	for (int i = 0; i < cycles; i++)
	{
		//pick cities to swap
		int city = rand() % adjM.length;
		int near;
		do{
			near = closeBy.closeByCities[city][rand() % closeBy.numCloseBy];
		} while (city == near);
		//std::cout << "City = " << city << " Near = " << near << std::endl;
		int cityIndex, nearIndex;
		//Find indexes
		//std::cout << "Loop";
		for (int j = 0; j < tempTour.length; j++)
		{
			if (tempTour.tour[j] == city){
				cityIndex = j;
				//std::cout << "City: " << j;
			}
			else if (tempTour.tour[j] == near){
				nearIndex = j;
				//std::cout << "Near: " << j;
			}
		}
		//std::cout << std::endl;
		//swap
		tempTour.tour[cityIndex] = near;
		tempTour.tour[nearIndex] = city;
		curDist = calcTourLen(tempTour, adjM);
		//Move is better accept it
		if (curDist < lastDist)
		{
			
			improvements++;
			lastDist = curDist;
			if (curDist < bestDist)
			{
				
				bestDist = curDist;
				for (int j = 0; j < tour.length; j++)
				{
					tour.tour[j] = tempTour.tour[j];
				}
			}
		}
		//Move is worse accept maybe
		else if (exp(-(curDist - lastDist) / temperature) > (((double)rand()) / RAND_MAX))
		{
			lastDist = curDist;
		}
		//Move not accepted reverse it
		else
		{
			tempTour.tour[cityIndex] = city;
			tempTour.tour[nearIndex] = near;
		}

		//Cycle housekeeping
		iteration++;
		if (temperature > minTemp)
			temperature *= coolingRate;
		else
			temperature = minTemp;
	}
	std::cout << temperature << std::endl;
	return tour;
}