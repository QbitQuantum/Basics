  void CoupledAggregationFactory<LocalOrdinal, GlobalOrdinal, Node, LocalMatOps>::Build(Level &currentLevel) const
  {
    FactoryMonitor m(*this, "Build", currentLevel);

    RCP<Aggregates> aggregates;
    {
      //TODO check for reuse of aggregates here

      // Level Get
      RCP<const GraphBase> graph = Get< RCP<GraphBase> >(currentLevel, "Graph");

      // Build
      aggregates = rcp(new Aggregates(*graph));
      aggregates->setObjectLabel("UC");

      algo1_.CoarsenUncoupled(*graph, *aggregates);
      algo2_.AggregateLeftovers(*graph, *aggregates);

    }

    aggregates->AggregatesCrossProcessors(true);

    // Level Set
    Set(currentLevel, "Aggregates", aggregates);

    if (IsPrint(Statistics0)) {
      aggregates->describe(GetOStream(Statistics0, 0), getVerbLevel());
    }

  }