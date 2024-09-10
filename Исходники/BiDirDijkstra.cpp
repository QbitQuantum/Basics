void BiDirDijkstra::explore(int cur_node, double cur_cost, int dir, std::priority_queue<PDI, std::vector<PDI>, std::greater<PDI> > &que)
{
	int i;
	int con_edge = m_vecNodeVector[cur_node].Connected_Edges_Index.size();
	double edge_cost;
	for(i = 0; i < con_edge; i++)
	{
		int edge_index = m_vecNodeVector[cur_node].Connected_Edges_Index[i];
		GraphEdgeInfo edge = m_vecEdgeVector[edge_index];
		int new_node = m_vecNodeVector[cur_node].Connected_Nodes[i];
		int mult;
		
		if(edge.Direction == 0)
			mult = 1;
		else
			mult = dir;
		if(cur_node == edge.StartNode)
		{
			if(dir > 0)
				edge_cost = edge.Cost;
			else
				edge_cost = edge.ReverseCost;
			if(edge.Direction == 0 || edge_cost >= 0.0)
			{
				//edge_cost = edge.Cost * mult;
				
				if(cur_cost + edge_cost < getcost(new_node, dir))
				{
					setcost(new_node, dir, cur_cost + edge_cost);
					setparent(new_node, dir, cur_node, edge.EdgeID);
					que.push(std::make_pair(cur_cost + edge_cost, new_node));

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
			if(dir > 0)
				edge_cost = edge.ReverseCost;
			else
				edge_cost = edge.Cost;
			if(edge.Direction == 0 || edge_cost >= 0.0)
			{
				//edge_cost = edge.ReverseCost * mult;

				if(cur_cost + edge_cost < getcost(new_node, dir))
				{
					setcost(new_node, dir, cur_cost + edge_cost);
					setparent(new_node, dir, cur_node, edge.EdgeID);
					que.push(std::make_pair(cur_cost + edge_cost, new_node));

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