void PathInfo::point_to_random_further(MTwist& mt, int sx, int sy) {
	PathingNode* fixed_node = get(sx, sy);

	int minx = squish(sx - 1, 0, width()), miny = squish(sy - 1, 0, height());
	int maxx = squish(sx + 1, 0, width()), maxy = squish(sy + 1, 0, height());

	int dx = 0, dy = 0;
	int compare_distance = fixed_node->distance;
	bool set = false;

	if (!fixed_node->marked) {
		for (int yy = miny; yy <= maxy; yy++) {
			for (int xx = minx; xx <= maxx; xx++) {
				if (sx == xx && sy == yy)
					continue;
				PathingNode* p = get(xx, yy);
				if (p->solid)
					continue;
				int dist = p->distance;
				if (dist >= compare_distance && (!set || mt.rand(2))) {
					dx = xx - sx, dy = yy - sy;
					set = true;
				}
			}
		}
	}
	fixed_node->dx = dx;
	fixed_node->dy = dy;
//	if (dx == 0 && dy == 0) {
//		fixed_node->distance = HUGE_DISTANCE;
//	} else {
//		fixed_node->distance = min_distance + (abs(dx) == abs(dy) ? 140 : 100);
//	}
}