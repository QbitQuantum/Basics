Vector<Vector2> Navigation2D::get_simple_path(const Vector2 &p_start, const Vector2 &p_end, bool p_optimize) {

	Polygon *begin_poly = NULL;
	Polygon *end_poly = NULL;
	Vector2 begin_point;
	Vector2 end_point;
	float begin_d = 1e20;
	float end_d = 1e20;

	//look for point inside triangle

	for (Map<int, NavMesh>::Element *E = navpoly_map.front(); E; E = E->next()) {

		if (!E->get().linked)
			continue;
		for (List<Polygon>::Element *F = E->get().polygons.front(); F; F = F->next()) {

			Polygon &p = F->get();
			if (begin_d || end_d) {
				for (int i = 2; i < p.edges.size(); i++) {

					if (begin_d > 0) {

						if (Geometry::is_point_in_triangle(p_start, _get_vertex(p.edges[0].point), _get_vertex(p.edges[i - 1].point), _get_vertex(p.edges[i].point))) {

							begin_poly = &p;
							begin_point = p_start;
							begin_d = 0;
							if (end_d == 0)
								break;
						}
					}

					if (end_d > 0) {

						if (Geometry::is_point_in_triangle(p_end, _get_vertex(p.edges[0].point), _get_vertex(p.edges[i - 1].point), _get_vertex(p.edges[i].point))) {

							end_poly = &p;
							end_point = p_end;
							end_d = 0;
							if (begin_d == 0)
								break;
						}
					}
				}
			}

			p.prev_edge = -1;
		}
	}

	//start or end not inside triangle.. look for closest segment :|
	if (begin_d || end_d) {
		for (Map<int, NavMesh>::Element *E = navpoly_map.front(); E; E = E->next()) {

			if (!E->get().linked)
				continue;
			for (List<Polygon>::Element *F = E->get().polygons.front(); F; F = F->next()) {

				Polygon &p = F->get();
				int es = p.edges.size();
				for (int i = 0; i < es; i++) {

					Vector2 edge[2] = {
						_get_vertex(p.edges[i].point),
						_get_vertex(p.edges[(i + 1) % es].point)
					};

					if (begin_d > 0) {
						Vector2 spoint = Geometry::get_closest_point_to_segment_2d(p_start, edge);
						float d = spoint.distance_to(p_start);
						if (d < begin_d) {
							begin_poly = &p;
							begin_point = spoint;
							begin_d = d;
						}
					}

					if (end_d > 0) {
						Vector2 spoint = Geometry::get_closest_point_to_segment_2d(p_end, edge);
						float d = spoint.distance_to(p_end);
						if (d < end_d) {
							end_poly = &p;
							end_point = spoint;
							end_d = d;
						}
					}
				}
			}
		}
	}

	if (!begin_poly || !end_poly) {

		return Vector<Vector2>(); //no path
	}

	if (begin_poly == end_poly) {

		Vector<Vector2> path;
		path.resize(2);
		path[0] = begin_point;
		path[1] = end_point;
		//print_line("Direct Path");
		return path;
	}

	bool found_route = false;

	List<Polygon *> open_list;

	begin_poly->entry = p_start;

	for (int i = 0; i < begin_poly->edges.size(); i++) {

		if (begin_poly->edges[i].C) {

			begin_poly->edges[i].C->prev_edge = begin_poly->edges[i].C_edge;
#ifdef USE_ENTRY_POINT
			Vector2 edge[2] = {
				_get_vertex(begin_poly->edges[i].point),
				_get_vertex(begin_poly->edges[(i + 1) % begin_poly->edges.size()].point)
			};

			Vector2 entry = Geometry::get_closest_point_to_segment_2d(begin_poly->entry, edge);
			begin_poly->edges[i].C->distance = begin_poly->entry.distance_to(entry);
			begin_poly->edges[i].C->entry = entry;
#else
			begin_poly->edges[i].C->distance = begin_poly->center.distance_to(begin_poly->edges[i].C->center);
#endif
			open_list.push_back(begin_poly->edges[i].C);

			if (begin_poly->edges[i].C == end_poly) {
				found_route = true;
			}
		}
	}

	while (!found_route) {

		if (open_list.size() == 0) {
			//print_line("NOU OPEN LIST");
			break;
		}
		//check open list

		List<Polygon *>::Element *least_cost_poly = NULL;
		float least_cost = 1e30;

		//this could be faster (cache previous results)
		for (List<Polygon *>::Element *E = open_list.front(); E; E = E->next()) {

			Polygon *p = E->get();

			float cost = p->distance;
			cost += p->center.distance_to(end_point);

			if (cost < least_cost) {

				least_cost_poly = E;
				least_cost = cost;
			}
		}

		Polygon *p = least_cost_poly->get();
		//open the neighbours for search
		int es = p->edges.size();

		for (int i = 0; i < es; i++) {

			Polygon::Edge &e = p->edges[i];

			if (!e.C)
				continue;

#ifdef USE_ENTRY_POINT
			Vector2 edge[2] = {
				_get_vertex(p->edges[i].point),
				_get_vertex(p->edges[(i + 1) % es].point)
			};

			Vector2 edge_entry = Geometry::get_closest_point_to_segment_2d(p->entry, edge);
			float distance = p->entry.distance_to(edge_entry) + p->distance;

#else

			float distance = p->center.distance_to(e.C->center) + p->distance;

#endif

			if (e.C->prev_edge != -1) {
				//oh this was visited already, can we win the cost?

				if (e.C->distance > distance) {

					e.C->prev_edge = e.C_edge;
					e.C->distance = distance;
#ifdef USE_ENTRY_POINT
					e.C->entry = edge_entry;
#endif
				}
			} else {
				//add to open neighbours

				e.C->prev_edge = e.C_edge;
				e.C->distance = distance;
#ifdef USE_ENTRY_POINT
				e.C->entry = edge_entry;
#endif

				open_list.push_back(e.C);

				if (e.C == end_poly) {
					//oh my reached end! stop algorithm
					found_route = true;
					break;
				}
			}
		}

		if (found_route)
			break;

		open_list.erase(least_cost_poly);
	}
#if 0
debug path
	{
		       Polygon *p=end_poly;
		       int idx=0;

		       while(true) {
			   int prev = p->prev_edge;
			   int prev_n = (p->prev_edge+1)%p->edges.size();
			   Vector2 point = (_get_vertex(p->edges[prev].point) + _get_vertex(p->edges[prev_n].point))*0.5;
			   String points;
			   for(int i=0;i<p->edges.size();i++) {
				   if (i>0)
					   points+=", ";
				   points+=_get_vertex(p->edges[i].point);
			   }
			   //print_line("poly "+itos(idx++)+" - "+points);
			   p = p->edges[prev].C;
			   if (p==begin_poly)
			       break;
		       }
		   }
#endif
	if (found_route) {

		Vector<Vector2> path;

		if (p_optimize) {
			//string pulling

			Vector2 apex_point = end_point;
			Vector2 portal_left = apex_point;
			Vector2 portal_right = apex_point;
			Polygon *left_poly = end_poly;
			Polygon *right_poly = end_poly;
			Polygon *p = end_poly;
			path.push_back(end_point);

			while (p) {

				Vector2 left;
				Vector2 right;

//#define CLOCK_TANGENT(m_a,m_b,m_c) ( ((m_a)-(m_c)).cross((m_a)-(m_b)) )
#define CLOCK_TANGENT(m_a, m_b, m_c) ((((m_a).x - (m_c).x) * ((m_b).y - (m_c).y) - ((m_b).x - (m_c).x) * ((m_a).y - (m_c).y)))

				if (p == begin_poly) {
					left = begin_point;
					right = begin_point;
				} else {
					int prev = p->prev_edge;
					int prev_n = (p->prev_edge + 1) % p->edges.size();
					left = _get_vertex(p->edges[prev].point);
					right = _get_vertex(p->edges[prev_n].point);

					if (p->clockwise) {
						SWAP(left, right);
					}
					/*if (CLOCK_TANGENT(apex_point,left,(left+right)*0.5) < 0){
						SWAP(left,right);
					}*/
				}

				bool skip = false;

				/*
				print_line("-----\nAPEX: "+(apex_point-end_point));
				print_line("LEFT:");
				print_line("\tPortal: "+(portal_left-end_point));
				print_line("\tPoint: "+(left-end_point));
				print_line("\tLeft Tangent: "+rtos(CLOCK_TANGENT(apex_point,portal_left,left)));
				print_line("\tLeft Distance: "+rtos(portal_left.distance_squared_to(apex_point)));
				print_line("\tLeft Test: "+rtos(CLOCK_TANGENT(apex_point,left,portal_right)));
				print_line("RIGHT:");
				print_line("\tPortal: "+(portal_right-end_point));
				print_line("\tPoint: "+(right-end_point));
				print_line("\tRight Tangent: "+rtos(CLOCK_TANGENT(apex_point,portal_right,right)));
				print_line("\tRight Distance: "+rtos(portal_right.distance_squared_to(apex_point)));
				print_line("\tRight Test: "+rtos(CLOCK_TANGENT(apex_point,right,portal_left)));
				*/

				if (CLOCK_TANGENT(apex_point, portal_left, left) >= 0) {
					//process
					if (portal_left.distance_squared_to(apex_point) < CMP_EPSILON || CLOCK_TANGENT(apex_point, left, portal_right) > 0) {
						left_poly = p;
						portal_left = left;
						//print_line("***ADVANCE LEFT");
					} else {

						apex_point = portal_right;
						p = right_poly;
						left_poly = p;
						portal_left = apex_point;
						portal_right = apex_point;
						if (path[path.size() - 1].distance_to(apex_point) > CMP_EPSILON)
							path.push_back(apex_point);
						skip = true;
						//print_line("addpoint left");
						//print_line("***CLIP LEFT");
					}
				}

				if (!skip && CLOCK_TANGENT(apex_point, portal_right, right) <= 0) {
					//process
					if (portal_right.distance_squared_to(apex_point) < CMP_EPSILON || CLOCK_TANGENT(apex_point, right, portal_left) < 0) {
						right_poly = p;
						portal_right = right;
						//print_line("***ADVANCE RIGHT");
					} else {

						apex_point = portal_left;
						p = left_poly;
						right_poly = p;
						portal_right = apex_point;
						portal_left = apex_point;
						if (path[path.size() - 1].distance_to(apex_point) > CMP_EPSILON)
							path.push_back(apex_point);
						//print_line("addpoint right");
						//print_line("***CLIP RIGHT");
					}
				}

				if (p != begin_poly)
					p = p->edges[p->prev_edge].C;
				else
					p = NULL;
			}

			if (path[path.size() - 1].distance_to(begin_point) > CMP_EPSILON)
				path.push_back(begin_point);

			path.invert();

		} else {
			//midpoints
			Polygon *p = end_poly;

			path.push_back(end_point);
			while (true) {
				int prev = p->prev_edge;
				int prev_n = (p->prev_edge + 1) % p->edges.size();
				Vector2 point = (_get_vertex(p->edges[prev].point) + _get_vertex(p->edges[prev_n].point)) * 0.5;
				path.push_back(point);
				p = p->edges[prev].C;
				if (p == begin_poly)
					break;
			}

			if (path[path.size() - 1].distance_to(begin_point) > CMP_EPSILON)
				path.push_back(begin_point);

			path.invert();
		}

		return path;
	}

	return Vector<Vector2>();
}