Vector<Vector2> PolygonPathFinder::find_path(const Vector2 &p_from, const Vector2 &p_to) {

	Vector<Vector2> path;

	Vector2 from = p_from;
	Vector2 to = p_to;
	Edge ignore_from_edge(-1, -1);
	Edge ignore_to_edge(-1, -1);

	if (!_is_point_inside(from)) {

		float closest_dist = 1e20;
		Vector2 closest_point;

		for (Set<Edge>::Element *E = edges.front(); E; E = E->next()) {

			const Edge &e = E->get();
			Vector2 seg[2] = {
				points[e.points[0]].pos,
				points[e.points[1]].pos
			};

			Vector2 closest = Geometry::get_closest_point_to_segment_2d(from, seg);
			float d = from.distance_squared_to(closest);

			if (d < closest_dist) {
				ignore_from_edge = E->get();
				closest_dist = d;
				closest_point = closest;
			}
		}

		from = closest_point;
	};

	if (!_is_point_inside(to)) {
		float closest_dist = 1e20;
		Vector2 closest_point;

		for (Set<Edge>::Element *E = edges.front(); E; E = E->next()) {

			const Edge &e = E->get();
			Vector2 seg[2] = {
				points[e.points[0]].pos,
				points[e.points[1]].pos
			};

			Vector2 closest = Geometry::get_closest_point_to_segment_2d(to, seg);
			float d = to.distance_squared_to(closest);

			if (d < closest_dist) {
				ignore_to_edge = E->get();
				closest_dist = d;
				closest_point = closest;
			}
		}

		to = closest_point;
	};

	//test direct connection
	{

		bool can_see_eachother = true;

		for (Set<Edge>::Element *E = edges.front(); E; E = E->next()) {

			const Edge &e = E->get();
			if (e.points[0] == ignore_from_edge.points[0] && e.points[1] == ignore_from_edge.points[1])
				continue;
			if (e.points[0] == ignore_to_edge.points[0] && e.points[1] == ignore_to_edge.points[1])
				continue;

			Vector2 a = points[e.points[0]].pos;
			Vector2 b = points[e.points[1]].pos;

			if (Geometry::segment_intersects_segment_2d(a, b, from, to, NULL)) {
				can_see_eachother = false;
				break;
			}
		}

		if (can_see_eachother) {

			path.push_back(from);
			path.push_back(to);
			return path;
		}
	}

	//add to graph

	int aidx = points.size() - 2;
	int bidx = points.size() - 1;
	points[aidx].pos = from;
	points[bidx].pos = to;
	points[aidx].distance = 0;
	points[bidx].distance = 0;
	points[aidx].prev = -1;
	points[bidx].prev = -1;
	points[aidx].penalty = 0;
	points[bidx].penalty = 0;

	for (int i = 0; i < points.size() - 2; i++) {

		bool valid_a = true;
		bool valid_b = true;
		points[i].prev = -1;
		points[i].distance = 0;

		if (!_is_point_inside(from * 0.5 + points[i].pos * 0.5)) {
			valid_a = false;
		}

		if (!_is_point_inside(to * 0.5 + points[i].pos * 0.5)) {
			valid_b = false;
		}

		for (Set<Edge>::Element *E = edges.front(); E; E = E->next()) {

			const Edge &e = E->get();

			if (e.points[0] == i || e.points[1] == i)
				continue;

			Vector2 a = points[e.points[0]].pos;
			Vector2 b = points[e.points[1]].pos;

			if (valid_a) {

				if (e.points[0] != ignore_from_edge.points[1] &&
						e.points[1] != ignore_from_edge.points[1] &&
						e.points[0] != ignore_from_edge.points[0] &&
						e.points[1] != ignore_from_edge.points[0]) {

					if (Geometry::segment_intersects_segment_2d(a, b, from, points[i].pos, NULL)) {
						valid_a = false;
					}
				}
			}

			if (valid_b) {

				if (e.points[0] != ignore_to_edge.points[1] &&
						e.points[1] != ignore_to_edge.points[1] &&
						e.points[0] != ignore_to_edge.points[0] &&
						e.points[1] != ignore_to_edge.points[0]) {

					if (Geometry::segment_intersects_segment_2d(a, b, to, points[i].pos, NULL)) {
						valid_b = false;
					}
				}
			}

			if (!valid_a && !valid_b)
				break;
		}

		if (valid_a) {
			points[i].connections.insert(aidx);
			points[aidx].connections.insert(i);
		}

		if (valid_b) {
			points[i].connections.insert(bidx);
			points[bidx].connections.insert(i);
		}
	}
	//solve graph

	Set<int> open_list;

	points[aidx].distance = 0;
	points[aidx].prev = aidx;
	for (Set<int>::Element *E = points[aidx].connections.front(); E; E = E->next()) {

		open_list.insert(E->get());
		points[E->get()].distance = from.distance_to(points[E->get()].pos);
		points[E->get()].prev = aidx;
	}

	bool found_route = false;

	while (true) {

		if (open_list.size() == 0) {
			printf("open list empty\n");
			break;
		}
		//check open list

		int least_cost_point = -1;
		float least_cost = 1e30;

		//this could be faster (cache previous results)
		for (Set<int>::Element *E = open_list.front(); E; E = E->next()) {

			const Point &p = points[E->get()];
			float cost = p.distance;
			cost += p.pos.distance_to(to);
			cost += p.penalty;

			if (cost < least_cost) {

				least_cost_point = E->get();
				least_cost = cost;
			}
		}

		Point &np = points[least_cost_point];
		//open the neighbours for search

		for (Set<int>::Element *E = np.connections.front(); E; E = E->next()) {

			Point &p = points[E->get()];
			float distance = np.pos.distance_to(p.pos) + np.distance;

			if (p.prev != -1) {
				//oh this was visited already, can we win the cost?

				if (p.distance > distance) {

					p.prev = least_cost_point; //reasign previous
					p.distance = distance;
				}
			} else {
				//add to open neighbours

				p.prev = least_cost_point;
				p.distance = distance;
				open_list.insert(E->get());

				if (E->get() == bidx) {
					//oh my reached end! stop algorithm
					found_route = true;
					break;
				}
			}
		}

		if (found_route)
			break;

		open_list.erase(least_cost_point);
	}

	if (found_route) {
		int at = bidx;
		path.push_back(points[at].pos);
		do {
			at = points[at].prev;
			path.push_back(points[at].pos);
		} while (at != aidx);

		path.invert();
	}

	for (int i = 0; i < points.size() - 2; i++) {

		points[i].connections.erase(aidx);
		points[i].connections.erase(bidx);
		points[i].prev = -1;
		points[i].distance = 0;
	}

	points[aidx].connections.clear();
	points[aidx].prev = -1;
	points[aidx].distance = 0;
	points[bidx].connections.clear();
	points[bidx].prev = -1;
	points[bidx].distance = 0;

	return path;
}