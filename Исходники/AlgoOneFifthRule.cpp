/*!
 *  \brief Configure evolver for (1+1)-ES with one fifth rule algorithm.
 *  \param ioEvolver Evolver modified by setting the algorithm.
 *  \param ioSystem Evolutionary system.
 *
 */
void ES::AlgoOneFifthRule::configure(Evolver& ioEvolver, System& ioSystem)
{
	Beagle_StackTraceBeginM();

	// Get reference to the factory
	const Factory& lFactory = ioSystem.getFactory();

	// Get name and allocator of used operators
	std::string lEvalOpName = lFactory.getConceptTypeName("EvaluationOp");
	EvaluationOp::Alloc::Handle lEvalOpAlloc =
	    castHandleT<EvaluationOp::Alloc>(lFactory.getAllocator(lEvalOpName));
	std::string lSelectOpName = "SelectRandomOp";
	EC::SelectionOp::Alloc::Handle lSelectOpAlloc =
	    castHandleT<EC::SelectionOp::Alloc>(lFactory.getAllocator(lSelectOpName));
	std::string lInitOpName = lFactory.getConceptTypeName("InitializationOp");
	EC::InitializationOp::Alloc::Handle lInitOpAlloc =
	    castHandleT<EC::InitializationOp::Alloc>(lFactory.getAllocator(lInitOpName));
	std::string lAdaptOpName = "ES-AdaptOneFifthRuleOp";
	ES::AdaptOneFifthRuleOp::Alloc::Handle lAdaptOpAlloc =
	    castHandleT<ES::AdaptOneFifthRuleOp::Alloc>(lFactory.getAllocator(lAdaptOpName));
	std::string lMutOpName = "FltVec-MutationGaussianOp";
	EC::MutationOp::Alloc::Handle lMutOpAlloc =
	    castHandleT<EC::MutationOp::Alloc>(lFactory.getAllocator(lMutOpName));
	std::string lMigOpName = lFactory.getConceptTypeName("MigrationOp");
	EC::MigrationOp::Alloc::Handle lMigOpAlloc =
	    castHandleT<EC::MigrationOp::Alloc>(lFactory.getAllocator(lMigOpName));
	std::string lStatsCalcOpName = lFactory.getConceptTypeName("StatsCalculateOp");
	EC::StatsCalculateOp::Alloc::Handle lStatsCalcOpAlloc =
	    castHandleT<EC::StatsCalculateOp::Alloc>(lFactory.getAllocator(lStatsCalcOpName));
	std::string lTermOpName = lFactory.getConceptTypeName("TerminationOp");
	EC::TerminationOp::Alloc::Handle lTermOpAlloc =
	    castHandleT<EC::TerminationOp::Alloc>(lFactory.getAllocator(lTermOpName));
	std::string lMsWriteOpName = "MilestoneWriteOp";
	EC::MilestoneWriteOp::Alloc::Handle lMsWriteOpAlloc =
	    castHandleT<EC::MilestoneWriteOp::Alloc>(lFactory.getAllocator(lMsWriteOpName));
	std::string lMPLOpName = "EC-MuPlusLambdaOp";
	EC::MuPlusLambdaOp::Alloc::Handle lMPLOpAlloc =
	    castHandleT<EC::MuPlusLambdaOp::Alloc>(lFactory.getAllocator(lMPLOpName));

	// Clear bootstrap and mainloop sets
	ioEvolver.getBootStrapSet().clear();
	ioEvolver.getMainLoopSet().clear();

	// Set the boostrap operator set
	EC::InitializationOp::Handle lInitOpBS = castHandleT<EC::InitializationOp>(lInitOpAlloc->allocate());
	lInitOpBS->setName(lInitOpName);
	ioEvolver.getBootStrapSet().push_back(lInitOpBS);
	EvaluationOp::Handle lEvalOpBS = castHandleT<EvaluationOp>(lEvalOpAlloc->allocate());
	lEvalOpBS->setName(lEvalOpName);
	ioEvolver.getBootStrapSet().push_back(lEvalOpBS);
	EC::StatsCalculateOp::Handle lStatsCalcOpBS = castHandleT<EC::StatsCalculateOp>(lStatsCalcOpAlloc->allocate());
	lStatsCalcOpBS->setName(lStatsCalcOpName);
	ioEvolver.getBootStrapSet().push_back(lStatsCalcOpBS);
	EC::TerminationOp::Handle lTermOpBS = castHandleT<EC::TerminationOp>(lTermOpAlloc->allocate());
	lTermOpBS->setName(lTermOpName);
	ioEvolver.getBootStrapSet().push_back(lTermOpBS);
	EC::MilestoneWriteOp::Handle lMsWriteOpBS = castHandleT<EC::MilestoneWriteOp>(lMsWriteOpAlloc->allocate());
	lMsWriteOpBS->setName(lMsWriteOpName);
	ioEvolver.getBootStrapSet().push_back(lMsWriteOpBS);

	// Set the mainloop operator set
	EC::MuPlusLambdaOp::Handle lMPLOp = castHandleT<EC::MuPlusLambdaOp>(lMPLOpAlloc->allocate());
	lMPLOp->setName(lMPLOpName);

	// Set breeder tree
	BreederNode::Handle lAdaptNode = new BreederNode;
	lMPLOp->setRootNode(lAdaptNode);
	lAdaptNode->setBreederOp(castHandleT<ES::AdaptOneFifthRuleOp>(lAdaptOpAlloc->allocate()));
	lAdaptNode->getBreederOp()->setName(lAdaptOpName);
	BreederNode::Handle lEvalNode = new BreederNode;
	lAdaptNode->setFirstChild(lEvalNode);
	lEvalNode->setBreederOp(castHandleT<EvaluationOp>(lEvalOpAlloc->allocate()));
	lEvalNode->getBreederOp()->setName(lEvalOpName);
	BreederNode::Handle lMutNode = new BreederNode;
	lEvalNode->setFirstChild(lMutNode);
	lMutNode->setBreederOp(castHandleT<EC::MutationOp>(lMutOpAlloc->allocate()));
	lMutNode->getBreederOp()->setName(lMutOpName);
	BreederNode::Handle lSelectMutNode = new BreederNode;
	lMutNode->setFirstChild(lSelectMutNode);
	lSelectMutNode->setBreederOp(castHandleT<EC::SelectionOp>(lSelectOpAlloc->allocate()));
	lSelectMutNode->getBreederOp()->setName(lSelectOpName);

	// Set remaining operators of mainloop
	EC::MigrationOp::Handle lMigOpML = castHandleT<EC::MigrationOp>(lMigOpAlloc->allocate());
	lMigOpML->setName(lMigOpName);
	ioEvolver.getMainLoopSet().push_back(lMigOpML);
	EC::StatsCalculateOp::Handle lStatsCalcOpML =
	    castHandleT<EC::StatsCalculateOp>(lStatsCalcOpAlloc->allocate());
	lStatsCalcOpML->setName(lStatsCalcOpName);
	ioEvolver.getMainLoopSet().push_back(lStatsCalcOpML);
	EC::TerminationOp::Handle lTermOpML = castHandleT<EC::TerminationOp>(lTermOpAlloc->allocate());
	lTermOpML->setName(lTermOpName);
	ioEvolver.getMainLoopSet().push_back(lTermOpML);
	EC::MilestoneWriteOp::Handle lMsWriteOpML =
	    castHandleT<EC::MilestoneWriteOp>(lMsWriteOpAlloc->allocate());
	lMsWriteOpML->setName(lMsWriteOpName);
	ioEvolver.getMainLoopSet().push_back(lMsWriteOpML);

	Beagle_StackTraceEndM();
}