bool PointTracker::find_correspondences(const vector<Vec2f>& points, float f)
{
	if (init_phase) {
		// We do a simple freetrack-like sorting in the init phase...
		// sort points
		int point_d_order[PointModel::N_POINTS];
		point_model->get_d_order(points, point_d_order);

		// set correspondences
		for (int i=0; i<PointModel::N_POINTS; ++i)
		{
			p[point_model->d_order[i]] = points[point_d_order[i]];
		}
	}
	else {
		// ... otherwise we look at the distance to the projection of the expected model points 
		// project model points under current pose
		p_exp[0] = project(Vec3f(0,0,0), f);
		p_exp[1] = project(point_model->M01, f);
		p_exp[2] = project(point_model->M02, f);

		// set correspondences by minimum distance to projected model point
		bool point_taken[PointModel::N_POINTS];
		for (int i=0; i<PointModel::N_POINTS; ++i)
			point_taken[i] = false;

		float min_sdist = 0;
		int min_idx = 0;
		
		for (int i=0; i<PointModel::N_POINTS; ++i)
		{
			// find closest point to projected model point i
			for (int j=0; j<PointModel::N_POINTS; ++j)
			{
				Vec2f d = p_exp[i]-points[j];
				float sdist = d.dot(d);
				if (sdist < min_sdist || j==0) 
				{
					min_idx = j;
					min_sdist = sdist;
				}
			}
			// if one point is closest to more than one model point, abort
			if (point_taken[min_idx]) return false;
			point_taken[min_idx] = true;
			p[i] = points[min_idx];
		}
	}
	return true;
}