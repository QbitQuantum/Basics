//void BiDirAStar::explore(int cur_node, double cur_cost, int dir, std::priority_queue<PDI, std::vector<PDI>, std::greater<PDI> > &que)
void BiDirAStar::explore(int cur_node, double cur_cost, int dir, MinHeap &que)
{
	size_t i;
	// Number of connected edges
	auto con_edge = m_vecNodeVector[cur_node].Connected_Edges_Index.size();
	double edge_cost;
	for(i = 0; i < con_edge; i++)
	{
		auto edge_index = m_vecNodeVector[cur_node].Connected_Edges_Index[i];
		// Get the edge from the edge list.
		GraphEdgeInfo edge = m_vecEdgeVector[edge_index];
		// Get the connected node
		int new_node = m_vecNodeVector[cur_node].Connected_Nodes[i];
#if 0  // mult is set but not used
		int mult;
		
		if(edge.Direction == 0)
			mult = 1;
		else
			mult = dir;
#endif
		if(cur_node == edge.StartNode)
		{
			// Current node is the startnode of the edge. For forward search it should use forward cost, otherwise it should use the reverse cost,
			// i.e. if the reverse direction is valid then this node may be visited from the end node.
			if(dir > 0)
				edge_cost = edge.Cost;
			else
				edge_cost = edge.ReverseCost;
			// Check if the direction is valid for exploration
			if(edge.Direction == 0 || edge_cost >= 0.0)
			{
				//edge_cost = edge.Cost * mult;
				// Check if the current edge gives better result
				if(cur_cost + edge_cost < getcost(new_node, dir))
				{
					// explore the node, and push it in the queue. the value in the queue will also contain the heuristic cost
					setcost(new_node, dir, cur_cost + edge_cost);
					setparent(new_node, dir, cur_node, edge.EdgeID);
					que.push(std::make_pair(cur_cost + edge_cost + gethcost(new_node, dir), new_node));

					// Update the minimum cost found so far.
					if(getcost(new_node, dir) + getcost(new_node, dir * -1) < m_MinCost)
					{
						m_MinCost = getcost(new_node, dir) + getcost(new_node, dir * -1);
						m_MidNode = new_node;
					}
				}
			}
		}
		else
		{
			// Current node is the endnode of the edge. For forward search it should use reverse cost, otherwise it should use the forward cost,
			// i.e. if the forward direction is valid then this node may be visited from the start node.
			if(dir > 0)
				edge_cost = edge.ReverseCost;
			else
				edge_cost = edge.Cost;
			// Check if the direction is valid for exploration
			if(edge.Direction == 0 || edge_cost >= 0.0)
			{
				//edge_cost = edge.ReverseCost * mult;
				
				// Check if the current edge gives better result
				if(cur_cost + edge_cost < getcost(new_node, dir))
				{
					// explore the node, and push it in the queue. the value in the queue will also contain the heuristic cost
					setcost(new_node, dir, cur_cost + edge_cost);
					setparent(new_node, dir, cur_node, edge.EdgeID);
					que.push(std::make_pair(cur_cost + edge_cost + gethcost(new_node, dir), new_node));
					// Update the minimum cost found so far.
					if(getcost(new_node, dir) + getcost(new_node, dir * -1) < m_MinCost)
					{
						m_MinCost = getcost(new_node, dir) + getcost(new_node, dir * -1);
						m_MidNode = new_node;
					}
				}
			}
		}
	}
}