void NestedSolver::solve(Solution *unused,Solution *result)
{

//	Solution *coarseSolution;
//	Integer i;
//	for(i=0;i<m_depth;i++)
//	{
		


//	}
	

	Solution *initialGuess = m_factories->createSolution(m_coarseGrid);
	Solution *coarse_result;	// = m_factories.createSolution(m_coarseGrid);
	Integer lvl;
	Grid *grid = m_coarseGrid;
	Grid *tmpGrid = m_coarseGrid->factory();
	ConditionFactory *conditionFactory;
//	MultiGridIterationStepFactory *stepFactory = MultiGridIterationStepFactory::getInstance();


	initialGuess->setZero();
	for(lvl=1; lvl<=m_depth; lvl++)
	{
	
		GridDependentData *gridDependent = m_gridIndependent->createGridDependent(grid);

		if(lvl<m_depth)
		{
			coarse_result = m_factories->createSolution(grid);
			conditionFactory = m_coarseConditionFactory;
		}
		else
		{
			coarse_result = result;
			conditionFactory = m_fineConditionFactory;
		}				
		
	
		 BlackBoxSolver *solver = m_subFactory->createBlackBoxSolver(	
					conditionFactory,	//ConditionFactory *conditionFactory, 
					grid,			//Grid *grid,
					lvl			//Integer depth			
					); 

		
		solver->solve(	initialGuess,	//Solution *initialGuess,
				coarse_result	//Solution *result
				);

		NULL_DELETE(initialGuess);
		NULL_DELETE(solver);

		if(lvl<m_depth)
		{
			m_operations->interpolateGrid(grid,tmpGrid);		
			tmpGrid->copy(grid);

			initialGuess = m_factories->createSolution(grid);
			m_operations->interpolateSolution(coarse_result,initialGuess);
			
			NULL_DELETE(coarse_result);
		}
		
		NULL_DELETE(gridDependent);
	}

	NULL_DELETE(tmpGrid);


}