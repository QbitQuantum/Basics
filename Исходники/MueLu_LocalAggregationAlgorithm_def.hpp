  void LocalAggregationAlgorithm<LocalOrdinal, GlobalOrdinal, Node, LocalMatOps>::CoarsenUncoupled(GraphBase const & graph, Aggregates & aggregates) const {
    Monitor m(*this, "Coarsen Uncoupled");

    std::string orderingType;
    switch(ordering_) {
      case NATURAL:
        orderingType="Natural";
        break;
      case RANDOM:
        orderingType="Random";
        break;
      case GRAPH:
        orderingType="Graph";
        break;
      default:
        break;
    }
    GetOStream(Runtime1) << "Ordering:                  " << orderingType << std::endl;
    GetOStream(Runtime1) << "Min nodes per aggregate:   " << minNodesPerAggregate_ << std::endl;
    GetOStream(Runtime1) << "Max nbrs already selected: " << maxNeighAlreadySelected_ << std::endl;

    /* Create Aggregation object */
    my_size_t nAggregates = 0;

    /* ============================================================= */
    /* aggStat indicates whether this node has been aggreated, and   */
    /* vertex2AggId stores the aggregate number where this node has  */
    /* been aggregated into.                                         */
    /* ============================================================= */

    Teuchos::ArrayRCP<NodeState> aggStat;
    const my_size_t nRows = graph.GetNodeNumVertices();
    if (nRows > 0) aggStat = Teuchos::arcp<NodeState>(nRows);
    for ( my_size_t i = 0; i < nRows; ++i ) aggStat[i] = READY;

    /* ============================================================= */
    /* Phase 1  :                                                    */
    /*    for all nodes, form a new aggregate with its neighbors     */
    /*    if the number of its neighbors having been aggregated does */
    /*    not exceed a given threshold                               */
    /*    (GetMaxNeighAlreadySelected() = 0 ===> Vanek's scheme) */
    /* ============================================================= */

    /* some general variable declarations */
    Teuchos::ArrayRCP<LO> randomVector;
    RCP<MueLu::LinkedList> nodeList; /* list storing the next node to pick as a root point for ordering_ == GRAPH */
    MueLu_SuperNode  *aggHead=NULL, *aggCurrent=NULL, *supernode=NULL;
    /**/

    if ( ordering_ == RANDOM )       /* random ordering */
      {
        //TODO: could be stored in a class that respect interface of LinkedList

        randomVector = Teuchos::arcp<LO>(nRows); //size_t or int ?-> to be propagated
        for (my_size_t i = 0; i < nRows; ++i) randomVector[i] = i;
        RandomReorder(randomVector);
      }
    else if ( ordering_ == GRAPH )  /* graph ordering */
      {
        nodeList = rcp(new MueLu::LinkedList());
        nodeList->Add(0);
      }

    /* main loop */
    {
      LO iNode  = 0;
      LO iNode2 = 0;

      Teuchos::ArrayRCP<LO> vertex2AggId = aggregates.GetVertex2AggId()->getDataNonConst(0); // output only: contents ignored

      while (iNode2 < nRows)
        {

          /*------------------------------------------------------ */
          /* pick the next node to aggregate                       */
          /*------------------------------------------------------ */

          if      ( ordering_ == NATURAL ) iNode = iNode2++;
          else if ( ordering_ == RANDOM )  iNode = randomVector[iNode2++];
          else if ( ordering_ == GRAPH )
            {
              if ( nodeList->IsEmpty() )
                {
                  for ( int jNode = 0; jNode < nRows; ++jNode )
                    {
                      if ( aggStat[jNode] == READY )
                        {
                          nodeList->Add(jNode); //TODO optim: not necessary to create a node. Can just set iNode value and skip the end
                          break;
                        }
                    }
                }
              if ( nodeList->IsEmpty() ) break; /* end of the while loop */ //TODO: coding style :(

              iNode = nodeList->Pop();
            }
          else {
            throw(Exceptions::RuntimeError("CoarsenUncoupled: bad aggregation ordering option"));
          }

          /*------------------------------------------------------ */
          /* consider further only if the node is in READY mode    */
          /*------------------------------------------------------ */

          if ( aggStat[iNode] == READY )
            {
              // neighOfINode is the neighbor node list of node 'iNode'.
              Teuchos::ArrayView<const LO> neighOfINode = graph.getNeighborVertices(iNode);
              typename Teuchos::ArrayView<const LO>::size_type length = neighOfINode.size();

              supernode = new MueLu_SuperNode;
              try {
                supernode->list = Teuchos::arcp<int>(length+1);
              } catch (std::bad_alloc&) {
                TEUCHOS_TEST_FOR_EXCEPTION(true, Exceptions::RuntimeError, "MueLu::LocalAggregationAlgorithm::CoarsenUncoupled(): Error: couldn't allocate memory for supernode! length=" + Teuchos::toString(length));
              }

              supernode->maxLength = length;
              supernode->length = 1;
              supernode->list[0] = iNode;

              int selectFlag = 1;
              {
                /*--------------------------------------------------- */
                /* count the no. of neighbors having been aggregated  */
                /*--------------------------------------------------- */

                int count = 0;
                for (typename Teuchos::ArrayView<const LO>::const_iterator it = neighOfINode.begin(); it != neighOfINode.end(); ++it)
                  {
                    int index = *it;
                    if ( index < nRows )
                      {
                        if ( aggStat[index] == READY ||
                             aggStat[index] == NOTSEL )
                          supernode->list[supernode->length++] = index;
                        else count++;

                      }
                  }

                /*--------------------------------------------------- */
                /* if there are too many neighbors aggregated or the  */
                /* number of nodes in the new aggregate is too few,   */
                /* don't do this one                                  */
                /*--------------------------------------------------- */

                if ( count > GetMaxNeighAlreadySelected() ) selectFlag = 0;
              }

              // Note: the supernode length is actually 1 more than the
              //       number of nodes in the candidate aggregate. The
              //       root is counted twice. I'm not sure if this is
              //       a bug or a feature ... so I'll leave it and change
              //       < to <= in the if just below.

              if (selectFlag != 1 ||
                  supernode->length <= GetMinNodesPerAggregate())
                {
                  aggStat[iNode] = NOTSEL;
                  delete supernode;
                  if ( ordering_ == GRAPH ) /* if graph ordering */
                    {
                      for (typename Teuchos::ArrayView<const LO>::const_iterator it = neighOfINode.begin(); it != neighOfINode.end(); ++it)
                        {
                          int index = *it;
                          if  ( index < nRows && aggStat[index] == READY )
                            {
                              nodeList->Add(index);
                            }
                        }
                    }
                }
              else
                {
                  aggregates.SetIsRoot(iNode);
                  for ( int j = 0; j < supernode->length; ++j )
                    {
                      int jNode = supernode->list[j];
                      aggStat[jNode] = SELECTED;
                      vertex2AggId[jNode] = nAggregates;
                      if ( ordering_ == GRAPH ) /* if graph ordering */
                        {

                          Teuchos::ArrayView<const LO> neighOfJNode = graph.getNeighborVertices(jNode);

                          for (typename Teuchos::ArrayView<const LO>::const_iterator it = neighOfJNode.begin(); it != neighOfJNode.end(); ++it)
                            {
                              int index = *it;
                              if ( index < nRows && aggStat[index] == READY )
                                {
                                  nodeList->Add(index);
                                }
                            }
                        }
                    }
                  supernode->next = NULL;
                  supernode->index = nAggregates;
                  if ( nAggregates == 0 )
                    {
                      aggHead = supernode;
                      aggCurrent = supernode;
                    }
                  else
                    {
                      aggCurrent->next = supernode;
                      aggCurrent = supernode;
                    }
                  nAggregates++;
                  // unused aggCntArray[nAggregates] = supernode->length;
                }
            }
        } // end of 'for'

      // views on distributed vectors are freed here.

    } // end of 'main loop'

    nodeList = Teuchos::null;

    /* Update aggregate object */
    aggregates.SetNumAggregates(nAggregates);

    /* Verbose */
    {
      const RCP<const Teuchos::Comm<int> > & comm = graph.GetComm();

      if (IsPrint(Warnings0)) {
        GO localReady=0, globalReady;

        // Compute 'localReady'
        for ( my_size_t i = 0; i < nRows; ++i )
          if (aggStat[i] == READY) localReady++;

        // Compute 'globalReady'
        sumAll(comm, localReady, globalReady);

        if(globalReady > 0)
          GetOStream(Warnings0) << "Warning: " << globalReady << " READY nodes left" << std::endl;
      }

      if (IsPrint(Statistics1)) {
        // Compute 'localSelected'
        LO localSelected=0;
        for ( my_size_t i = 0; i < nRows; ++i )
          if ( aggStat[i] == SELECTED ) localSelected++;

        // Compute 'globalSelected'
        GO globalSelected; sumAll(comm, (GO)localSelected, globalSelected);

        // Compute 'globalNRows'
        GO globalNRows; sumAll(comm, (GO)nRows, globalNRows);

        GetOStream(Statistics1) << "Nodes aggregated = " << globalSelected << " (" << globalNRows << ")" << std::endl;
      }

      if (IsPrint(Statistics1)) {
        GO nAggregatesGlobal; sumAll(comm, (GO)nAggregates, nAggregatesGlobal);
        GetOStream(Statistics1) << "Total aggregates = " << nAggregatesGlobal << std::endl;
      }

    } // verbose

      /* ------------------------------------------------------------- */
      /* clean up                                                      */
      /* ------------------------------------------------------------- */

    aggCurrent = aggHead;
    while ( aggCurrent != NULL )
      {
        supernode = aggCurrent;
        aggCurrent = aggCurrent->next;
        delete supernode;
      }

  } // CoarsenUncoupled