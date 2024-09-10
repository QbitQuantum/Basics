SolutionSet *MOCHC::execute() {
	
  int populationSize;
  int iterations;
  int maxEvaluations;
  int convergenceValue;
  int minimumDistance;
  int evaluations;

  double preservedPopulation;
  double initialConvergenceCount;
  bool condition = false;
  SolutionSet *solutionSet, *offSpringPopulation, *newPopulation; 

  Comparator * crowdingComparator = new CrowdingComparator();

  SolutionSet * population;
  SolutionSet * offspringPopulation;
  SolutionSet * unionSolution;

  Operator * cataclysmicMutation;
  Operator * crossover;
  Operator * parentSelection;


  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");
  convergenceValue = *(int *) getInputParameter("convergenceValue");
  initialConvergenceCount = *(double *)getInputParameter("initialConvergenceCount");
  preservedPopulation = *(double *)getInputParameter("preservedPopulation");
  

  //Read the operators
  cataclysmicMutation = operators_["mutation"];
  crossover	      = operators_["crossover"];
  parentSelection     = operators_["parentSelection"];
  
  iterations  = 0;
  evaluations = 0;

  // calculating the maximum problem sizes .... 
  Solution * sol = new Solution(problem_);
  int size = 0;
  for (int var = 0; var < problem_->getNumberOfVariables(); var++) {
	Binary *binaryVar;
        binaryVar  = (Binary *)sol->getDecisionVariables()[var];
	size += binaryVar->getNumberOfBits();
  } 
  minimumDistance = (int) std::floor(initialConvergenceCount*size);

  // Create the initial solutionSet
  Solution * newSolution;
  population = new SolutionSet(populationSize);
  for (int i = 0; i < populationSize; i++) {
    newSolution = new Solution(problem_);
    problem_->evaluate(newSolution);
    problem_->evaluateConstraints(newSolution);
    evaluations++;
    population->add(newSolution);
  } //for


  while (!condition) {
	offSpringPopulation = new SolutionSet(populationSize);
 	Solution **parents = new Solution*[2];
	
	for (int i = 0; i < population->size()/2; i++) {
  		parents[0] = (Solution *) (parentSelection->execute(population));
		parents[1] = (Solution *) (parentSelection->execute(population));

		if (hammingDistance(*parents[0],*parents[1])>= minimumDistance) {
		   Solution ** offSpring = (Solution **) (crossover->execute(parents));
		   problem_->evaluate(offSpring[0]);
		   problem_->evaluateConstraints(offSpring[0]);
	           problem_->evaluate(offSpring[1]);
		   problem_->evaluateConstraints(offSpring[1]);
		   evaluations+=2;
		   offSpringPopulation->add(offSpring[0]);
		   offSpringPopulation->add(offSpring[1]);
		}		
	}  
	SolutionSet *join = population->join(offSpringPopulation);
 	delete offSpringPopulation;

	newPopulation = rankingAndCrowdingSelection(join,populationSize);
	delete join;
        if (equals(*population,*newPopulation)) {
		minimumDistance--;
	}   

	if (minimumDistance <= -convergenceValue) {
		minimumDistance = (int) (1.0/size * (1-1.0/size) * size);
		int preserve = (int) std::floor(preservedPopulation*populationSize);
		newPopulation->clear(); //do the new in c++ really hurts me(juanjo)
		population->sort(crowdingComparator);
		for (int i = 0; i < preserve; i++) {
			newPopulation->add(new Solution(population->get(i)));
		}
		for (int i = preserve; i < populationSize; i++) {
			Solution * solution = new Solution(population->get(i));
			cataclysmicMutation->execute(solution);
			problem_->evaluate(solution);
			problem_->evaluateConstraints(solution);	
			newPopulation->add(solution);
		}
		
	}

	iterations++;
	delete population;
	population = newPopulation;
	if (evaluations >= maxEvaluations) {
		condition = true;		
	}
  }

  return population;

}