  void UncoupledAggregationFactory<LocalOrdinal, GlobalOrdinal, Node, LocalMatOps>::Build(Level &currentLevel) const {
    FactoryMonitor m(*this, "Build", currentLevel);

    ParameterList pL = GetParameterList();
    bDefinitionPhase_ = false;  // definition phase is finished, now all aggregation algorithm information is fixed

    // define aggregation algorithms
    RCP<const FactoryBase> graphFact = GetFactory("Graph");

    // TODO Can we keep different aggregation algorithms over more Build calls?
    algos_.clear();
    if (pL.get<std::string>("aggregation: mode") == "old") {
      if (pL.get<bool>("UseOnePtAggregationAlgorithm")             == true)   algos_.push_back(rcp(new OnePtAggregationAlgorithm             (graphFact)));
      if (pL.get<bool>("UsePreserveDirichletAggregationAlgorithm") == true)   algos_.push_back(rcp(new PreserveDirichletAggregationAlgorithm (graphFact)));
      if (pL.get<bool>("UseUncoupledAggregationAlgorithm")         == true)   algos_.push_back(rcp(new AggregationPhase1Algorithm            (graphFact)));
      if (pL.get<bool>("UseMaxLinkAggregationAlgorithm")           == true)   algos_.push_back(rcp(new MaxLinkAggregationAlgorithm           (graphFact)));
      if (pL.get<bool>("UseEmergencyAggregationAlgorithm")         == true)   algos_.push_back(rcp(new EmergencyAggregationAlgorithm         (graphFact)));
                                                                              algos_.push_back(rcp(new IsolatedNodeAggregationAlgorithm      (graphFact)));

    } else {
      if (pL.get<bool>("aggregation: preserve Dirichlet points")   == true)   algos_.push_back(rcp(new PreserveDirichletAggregationAlgorithm (graphFact)));
      if (pL.get<bool>("aggregation: enable phase 1" )             == true)   algos_.push_back(rcp(new AggregationPhase1Algorithm            (graphFact)));
      if (pL.get<bool>("aggregation: enable phase 2a")             == true)   algos_.push_back(rcp(new AggregationPhase2aAlgorithm           (graphFact)));
      if (pL.get<bool>("aggregation: enable phase 2b")             == true)   algos_.push_back(rcp(new AggregationPhase2bAlgorithm           (graphFact)));
      if (pL.get<bool>("aggregation: enable phase 3" )             == true)   algos_.push_back(rcp(new AggregationPhase3Algorithm            (graphFact)));
                                                                              algos_.push_back(rcp(new IsolatedNodeAggregationAlgorithm      (graphFact)));
    }

    std::string mapOnePtName = pL.get<std::string>("OnePt aggregate map name");
    RCP<const Map> OnePtMap;
    if (mapOnePtName.length()) {
      RCP<const FactoryBase> mapOnePtFact = GetFactory("OnePt aggregate map factory");
      OnePtMap = currentLevel.Get<RCP<const Map> >(mapOnePtName, mapOnePtFact.get());
    }

    RCP<const GraphBase> graph = Get< RCP<GraphBase> >(currentLevel, "Graph");

    // Build
    RCP<Aggregates> aggregates = rcp(new Aggregates(*graph));
    aggregates->setObjectLabel("UC");

    const LO numRows = graph->GetNodeNumVertices();

    // construct aggStat information
    std::vector<unsigned> aggStat(numRows, READY);

    ArrayRCP<const bool> dirichletBoundaryMap = graph->GetBoundaryNodeMap();
    if (dirichletBoundaryMap != Teuchos::null)
      for (LO i = 0; i < numRows; i++)
        if (dirichletBoundaryMap[i] == true)
          aggStat[i] = BOUNDARY;

    LO nDofsPerNode = Get<LO>(currentLevel, "DofsPerNode");
    GO indexBase = graph->GetDomainMap()->getIndexBase();
    if (OnePtMap != Teuchos::null) {
      for (LO i = 0; i < numRows; i++) {
        // reconstruct global row id (FIXME only works for contiguous maps)
        GO grid = (graph->GetDomainMap()->getGlobalElement(i)-indexBase) * nDofsPerNode + indexBase;

        for (LO kr = 0; kr < nDofsPerNode; kr++)
          if (OnePtMap->isNodeGlobalElement(grid + kr))
            aggStat[i] = ONEPT;
      }
    }


    const RCP<const Teuchos::Comm<int> > comm = graph->GetComm();
    GO numGlobalRows = 0;
    if (IsPrint(Statistics1))
      sumAll(comm, as<GO>(numRows), numGlobalRows);

    LO numNonAggregatedNodes = numRows;
    GO numGlobalAggregatedPrev = 0, numGlobalAggsPrev = 0;
    for (size_t a = 0; a < algos_.size(); a++) {
      std::string phase = algos_[a]->description();
      SubFactoryMonitor sfm(*this, "Algo \"" + phase + "\"", currentLevel);

      algos_[a]->BuildAggregates(pL, *graph, *aggregates, aggStat, numNonAggregatedNodes);

      if (IsPrint(Statistics1)) {

        GO numLocalAggregated = numRows - numNonAggregatedNodes, numGlobalAggregated = 0;
        GO numLocalAggs       = aggregates->GetNumAggregates(),  numGlobalAggs = 0;
        sumAll(comm, numLocalAggregated, numGlobalAggregated);
        sumAll(comm, numLocalAggs,       numGlobalAggs);

        double aggPercent = 100*as<double>(numGlobalAggregated)/as<double>(numGlobalRows);
        if (aggPercent > 99.99 && aggPercent < 100.00) {
          // Due to round off (for instance, for 140465733/140466897), we could
          // get 100.00% display even if there are some remaining nodes. This
          // is bad from the users point of view. It is much better to change
          // it to display 99.99%.
          aggPercent = 99.99;
        }
        GetOStream(Statistics1) << "  aggregated : " << (numGlobalAggregated - numGlobalAggregatedPrev) << " (phase), " << std::fixed
                                   << std::setprecision(2) << numGlobalAggregated << "/" << numGlobalRows << " [" << aggPercent << "%] (total)\n"
                                   << "  remaining  : " << numGlobalRows - numGlobalAggregated << "\n"
                                   << "  aggregates : " << numGlobalAggs-numGlobalAggsPrev << " (phase), " << numGlobalAggs << " (total)" << std::endl;
        numGlobalAggregatedPrev = numGlobalAggregated;
        numGlobalAggsPrev       = numGlobalAggs;
      }
    }

    TEUCHOS_TEST_FOR_EXCEPTION(numNonAggregatedNodes, Exceptions::RuntimeError, "MueLu::UncoupledAggregationFactory::Build: Leftover nodes found! Error!");

    aggregates->AggregatesCrossProcessors(false);

    Set(currentLevel, "Aggregates", aggregates);

    GetOStream(Statistics0) << aggregates->description() << std::endl;
  }