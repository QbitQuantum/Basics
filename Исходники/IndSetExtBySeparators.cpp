set<MinimalSeparator> IndSetExtBySeparators::extendToMaxIndependentSet(
		const set<MinimalSeparator>& minSeps) {

	queue<SubGraph> Q;

	// create a copy of minSeps
	set<MinimalSeparator> maximalSet = minSeps;

	SubGraph sg = SubGraph(graph);
	if (maximalSet.empty()) {
		Q.push(sg);
	} else {
		Q = decompose(sg, minSeps);
	}

	vector<NodeSet> cComponents;

	while (!Q.empty()) {
		SubGraph& c = Q.front();

		vector<Node> unconnectedNodes = getUnconnectedNodes(c);

		if (unconnectedNodes[0] >= 0) { // <=> not clique

			NodeSet minSepInC = findMinSep(unconnectedNodes, c);

			c.addClique(minSepInC); // saturate

			// c components when removing minSepInC group
			cComponents = c.getComponents(minSepInC);

			for (NodeSet& cComponent : cComponents) {
				NodeSet cComponentNeighbors = c.getNeighbors(cComponent);

				// mapping of the node indices in the component c to the node
				// indices in the main graph
				vector<int>& cNodeMapInMainGraph = c.getNodeMapToMainGraph();

				includeNodesToMaximalSet(cNodeMapInMainGraph, maximalSet,
						cComponentNeighbors, minSepInC);

				// subComp nodes merged with its neighbors
				NodeSet cComponentNeighborsMerged = mergeComponentAndNeighbors(
						cComponent, cComponentNeighbors);

				// create a sub graph out of c component and subCompMerged nodes
				SubGraph cComponentSubGraph = SubGraph(c,
						cComponentNeighborsMerged);
				Q.push(cComponentSubGraph);

			}

		}

		Q.pop();
	}

	return maximalSet;
}