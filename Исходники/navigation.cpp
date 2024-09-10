Vector<Vector3> Navigation::get_simple_path(const Vector3& p_start, const Vector3& p_end) {


	Polygon *begin_poly=NULL;
	Polygon *end_poly=NULL;
	Vector3 begin_point;
	Vector3 end_point;
	float begin_d=1e20;
	float end_d=1e20;


	for (Map<int,NavMesh>::Element*E=navmesh_map.front();E;E=E->next()) {

		if (!E->get().linked)
			continue;
		for(List<Polygon>::Element *F=E->get().polygons.front();F;F=F->next()) {

			Polygon &p=F->get();
			for(int i=2;i<p.edges.size();i++) {

				Face3 f(_get_vertex(p.edges[0].point),_get_vertex(p.edges[i-1].point),_get_vertex(p.edges[i].point));
				Vector3 spoint = f.get_closest_point_to(p_start);
				float dpoint = spoint.distance_to(p_start);
				if (dpoint<begin_d) {
					begin_d=dpoint;
					begin_poly=&p;
					begin_point=spoint;
				}

				spoint = f.get_closest_point_to(p_end);
				dpoint = spoint.distance_to(p_end);
				if (dpoint<end_d) {
					end_d=dpoint;
					end_poly=&p;
					end_point=spoint;
				}
			}

			p.prev_edge=-1;
		}
	}

	if (!begin_poly || !end_poly) {

		//print_line("No Path Path");
		return Vector<Vector3>(); //no path
	}

	if (begin_poly==end_poly) {

		Vector<Vector3> path;
		path.resize(2);
		path[0]=begin_point;
		path[1]=end_point;
		//print_line("Direct Path");
		return path;
	}


	bool found_route=false;

	List<Polygon*> open_list;

	for(int i=0;i<begin_poly->edges.size();i++) {

		if (begin_poly->edges[i].C) {

			begin_poly->edges[i].C->prev_edge=begin_poly->edges[i].C_edge;
			begin_poly->edges[i].C->distance=begin_poly->center.distance_to(begin_poly->edges[i].C->center);
			open_list.push_back(begin_poly->edges[i].C);

			if (begin_poly->edges[i].C==end_poly) {
				found_route=true;
			}
		}
	}


	while(!found_route) {

		if (open_list.size()==0) {
		//	print_line("NOU OPEN LIST");
			break;
		}
		//check open list

		List<Polygon*>::Element *least_cost_poly=NULL;
		float least_cost=1e30;

		//this could be faster (cache previous results)
		for (List<Polygon*>::Element *E=open_list.front();E;E=E->next()) {

			Polygon *p=E->get();


			float cost=p->distance;
			cost+=p->center.distance_to(end_point);

			if (cost<least_cost) {

				least_cost_poly=E;
				least_cost=cost;
			}
		}


		Polygon *p=least_cost_poly->get();
		//open the neighbours for search

		for(int i=0;i<p->edges.size();i++) {


			Polygon::Edge &e=p->edges[i];

			if (!e.C)
				continue;

			float distance = p->center.distance_to(e.C->center) + p->distance;

			if (e.C->prev_edge!=-1) {
				//oh this was visited already, can we win the cost?

				if (e.C->distance>distance) {

					e.C->prev_edge=e.C_edge;
					e.C->distance=distance;
				}
			} else {
				//add to open neighbours

				e.C->prev_edge=e.C_edge;
				e.C->distance=distance;
				open_list.push_back(e.C);

				if (e.C==end_poly) {
					//oh my reached end! stop algorithm
					found_route=true;
					break;

				}

			}
		}

		if (found_route)
			break;

		open_list.erase(least_cost_poly);
	}

	if (found_route) {

		//use midpoints for now
		Polygon *p=end_poly;
		Vector<Vector3> path;
		path.push_back(end_point);
		while(true) {
			int prev = p->prev_edge;
			int prev_n = (p->prev_edge+1)%p->edges.size();
			Vector3 point = (_get_vertex(p->edges[prev].point) + _get_vertex(p->edges[prev_n].point))*0.5;
			path.push_back(point);
			p = p->edges[prev].C;
			if (p==begin_poly)
				break;
		}

		path.push_back(begin_point);


		path.invert();;

		return path;
	}


	return Vector<Vector3>();

}