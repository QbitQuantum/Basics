Chromosome runGA(std::string target, int popSize, double mr, double cr)
{
	// implement genetic algorithm here
	// use a vector<Chromosome> for the population
	// I recommend using STL algorithms such as std::sort

	// remember, the GA is a loop until you find a chromosome
	// of fitness 0

	// on each iteration, you should be generating a new population
	// of twice the size of popSize, filling it with chromosomes
	// that have been mutated, crossed, and/or copied based on
	// the probabilities given by mr and cr
	// then sort it and keep only the best half as the population
	// for the next iteration
	// when you find a chromosome of fitness 0, you have finished and
	// you should return it

	std::vector<Chromosome> population;
	population = newVector(population, popSize, target.length());

	Chromosome solution(population[0]);
	int iteration = 0;
	do
	{
		std::vector<Chromosome> newPopulation;

		for (int i = 0; i<(popSize * 2); ++i)
		{
			int randomIndex = rand() % population.size();
			Chromosome aChromosome(population[randomIndex]);

			double randomPercentage = (rand() % 101) / 100.0;
			if (randomPercentage <= mr)
			{
				aChromosome = aChromosome.mutate();
			}

			randomPercentage = (rand() % 101) / 100.0;
			if (randomPercentage <= cr)
			{
				randomIndex = rand() % population.size();

				aChromosome = aChromosome.crossover(population[randomIndex]);
			}

			newPopulation.push_back(aChromosome);
		}

		auto lessThan = [&target](Chromosome& a, Chromosome& b)->bool { return a.fitness(target) < b.fitness(target); };
		std::sort(newPopulation.begin(), newPopulation.end(), lessThan);

		copyHalf(newPopulation, population);

		solution = population[0];

		std::cout << "Iteration number: " << iteration << std::endl;
		std::cout << "Solution: " << solution << std::endl;
		++iteration;

	} while (solution.fitness(target));
	return solution;
}