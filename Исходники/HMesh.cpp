void HMesh::removeHeckBertShit(size_t amount)
{
	map<double, pair<int, Edge*> > shortest_edges;
	for(int i = 0; i < vertices_.size(); i++)
	{
		for(Edge* edgy : vertices_[i]->in_edges)
		{
			Vertex* v1 = edgy->start;
			Vertex* v2 = edgy->end;
			Vertex v_neu = (*v1 + *v2) * 0.5;
			Vertex v_b1 = v_neu - *v1;
			Vector3f ev_b1 = Vector3f(v_b1.x, v_b1.y, v_b1.z);
		    double heck_meck = 0;
		    for(int i = 0;i < v1->out_edges.size();i++)
		    {
				Face* plane = v1->out_edges[i]->face;
				if(plane != NULL)
				{
					Vertex s1 = (*plane->startEdge_->end - *plane->startEdge_->start);
					Vertex s2 = (*plane->startEdge_->next->end - *plane->startEdge_->start);
					Vector3f stv1 = Vector3f(s1.x, s1.y, s1.z);
					Vector3f stv2 = Vector3f(s2.x, s2.y, s2.z);
					Vector3f normal = stv1.cross(stv2);
					heck_meck += pow((normal.dot(ev_b1)), 2);
				} 
			}
			Vertex v_b2 = v_neu - *v2;
			Vector3f ev_b2 = Vector3f(v_b2.x, v_b2.y, v_b2.z);
		    for(int i = 0;i < v2->out_edges.size();i++)
		    {
				Face* plane = v2->out_edges[i]->face;
				if(plane != NULL)
				{
					Vertex s1 = (*plane->startEdge_->end - *plane->startEdge_->start);
					Vertex s2 = (*plane->startEdge_->next->end - *plane->startEdge_->start);
					Vector3f stv1 = Vector3f(s1.x, s1.y, s1.z);
					Vector3f stv2 = Vector3f(s2.x, s2.y, s2.z);
					Vector3f normal = stv1.cross(stv2);
					heck_meck += pow((normal.dot(ev_b2)), 2);
				} 
			}
			shortest_edges.insert(pair<double, pair<int, Edge*> >(heck_meck, pair<int, Edge*>(i,edgy)));
		}
	}
	collapseEdge(shortest_edges.begin()->second.second);
	int i = shortest_edges.begin()->second.first;
	auto elem = find(vertices_[i]->in_edges.begin(), vertices_[i]->in_edges.end(), shortest_edges.begin()->second.second) ;
	if(elem != vertices_[i]->in_edges.end())
	{
		vertices_[i]->in_edges.erase(elem);
	}
	elem = find(vertices_[i]->out_edges.begin(), vertices_[i]->out_edges.end(), shortest_edges.begin()->second.second) ;
	if(elem != vertices_[i]->out_edges.end())
	{  
		vertices_[i]->out_edges.erase(elem);
	}
}