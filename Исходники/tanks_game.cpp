	bool collision_check(angular * tank1) {
		std::vector<Vector> tmp_points = tank1->abs_points();
		for (int i = 0; i < (int)tmp_points.size(); ++i)
			if (getpixel(bg_collision, tmp_points[i].x, tmp_points[i].y) == makecol(0,255,0) ||
				getpixel(bld_collision, tmp_points[i].x, tmp_points[i].y) == makecol(0,255,0)) {
				tank1->last_collision = i;
				return true;
			}
		return false;
	}