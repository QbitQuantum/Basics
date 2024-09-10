	/**
	 * @brief Announces *vertices* of a *graph* to the network, so that other peers
	 *        know that these *vertices* are hosted by this peer.
	 *
	 * The general workflow includes two steps:
	 *  1. Each peer, that hosts vertices of the *graph* announces its *vertices*
	 *     * Each peer will send its hosted vertices and update its vertices location
	 *     * The host peers will create a new context for *graph*
	 *  2. Vertices can now be located by locateVertex()
	 *  3. use Graphpeer to communicate between vertices
	 *
	 * @remark This is a collective Operation on which either all host peers
	 *         of the supergraph of *graph* have to take part or when *graph* has no
	 *         supergraph then all Communicatos from the globalContext (which should
	 *         be all peers in the network).
	 *
	 * @todo What happens if *vertices* is empty ?
	 * @todo What happens when there already exist an context for *graph* ?
	 * @todo What happens when not all *vertices* of a *graph* were announced ?
	 * @todo Reduce communication from 2 steps (allReduce + allGather) to one
	 *       step (allGatherVar), could reduce communication.
	 *
	 * @param[in] graph  Its vertices will be announced
	 * @param[in] vertices A set of vertices, that will be hosted by this peer
	 *
	 */
	void announce(Graph& graph, const std::vector<Vertex> vertices, const bool global=true){
	    // Get old context from graph
	    Context oldContext = getGraphContext(graph);

	    if(global)
		oldContext = cal.getGlobalContext();

	    if(!oldContext.valid()){
		if(graph.hasSuperGraph()){
		    //std::cout << "hasSuperGraph" << std::endl;
		    oldContext = getGraphContext(graph.superGraph);

		}
		else {
		    //std::cout << "global context" << std::endl;
		    oldContext = cal.getGlobalContext();

		}

	    }
	    else {
		//std::cout << "Has already context" << std::endl;
	    }

	    assert(oldContext.valid());

	    // Create new context for peers which host vertices
	    std::vector<unsigned> hasVertices(1, vertices.size());
	    std::vector<unsigned> recvHasVertices(oldContext.size(), 0);
	    cal.allGather(oldContext, hasVertices, recvHasVertices);

	    std::vector<VAddr> vAddrsWithVertices;

	    for(unsigned i = 0; i < recvHasVertices.size(); ++i){
		if(recvHasVertices[i] > 0){
		    vAddrsWithVertices.push_back(i);
		}
	    }

	    Context newContext = cal.createContext(vAddrsWithVertices, oldContext);
	    graphMap[graph.id] = newContext;
	    // std::cout << "context size: " << newContext.size() << std::endl;
	
	    // Each peer announces the vertices it hosts
	    if(newContext.valid()){

		// Bound graph to new context

	    
		// Retrieve maximum number of vertices per peer
		std::vector<unsigned> myVerticesCount(1,vertices.size());
		std::vector<unsigned> maxVerticesCount(1,  0);
		cal.allReduce(newContext, op::maximum<unsigned>(), myVerticesCount, maxVerticesCount);

		// Gather maxVerticesCount times vertex ids
		std::vector<std::vector<Vertex> > newVertexMaps (newContext.size(), std::vector<Vertex>());
		for(unsigned i = 0; i < maxVerticesCount[0]; ++i){
		    std::vector<int> vertexID(1, -1);
		    std::vector<int> recvData(newContext.size(), 0);

		    if(i < vertices.size()){
			vertexID[0] = graph.getLocalID(vertices.at(i));
		    }

		    cal.allGather(newContext, vertexID, recvData);
		
		   
		    for(unsigned vAddr = 0; vAddr < newVertexMaps.size(); ++vAddr){
			if(recvData[vAddr] != -1){
			    VertexID vertexID = (VertexID) recvData[vAddr];
			    Vertex v = graph.getVertices().at(vertexID);
			    vertexMap[graph.id][v.id] = vAddr;
			    newVertexMaps[vAddr].push_back(v);
		    
			}

		    }
      
		    for(unsigned vAddr = 0; vAddr < newVertexMaps.size(); ++vAddr){
			peerMap[graph.id][vAddr] = newVertexMaps[vAddr];

		    }

		}

	    }

	}