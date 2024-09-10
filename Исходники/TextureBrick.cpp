	// compute polygon list of edge plane intersections
	//
	// This is never called externally and could be private.
	//
	// The representation returned is not efficient, but it appears a
	// typical rendering only contains about 1k triangles.
	void TextureBrick::compute_polygons(Ray& view,
		double tmin, double tmax, double dt,
		vector<float>& vertex, vector<uint32_t>& index,
		vector<uint32_t>& size)
	{
		if (dt <= 0.0)
			return;

		Vector vv[12], tt[12]; // temp storage for vertices and texcoords

		uint32_t degree = 0;

		// find up and right vectors
		Vector vdir = view.direction();
		view_vector_ = vdir;
		Vector up;
		Vector right;
		switch (MinIndex(fabs(vdir.x()),
			fabs(vdir.y()),
			fabs(vdir.z())))
		{
		case 0:
			up.x(0.0); up.y(-vdir.z()); up.z(vdir.y());
			break;
		case 1:
			up.x(-vdir.z()); up.y(0.0); up.z(vdir.x());
			break;
		case 2:
			up.x(-vdir.y()); up.y(vdir.x()); up.z(0.0);
			break;
		}
		up.normalize();
		right = Cross(vdir, up);
		bool order = TextureRenderer::get_update_order();
		size_t vert_count = 0;
		for (double t = order ? tmin : tmax;
		order ? (t < tmax) : (t > tmin);
			t += order ? dt : -dt)
		{
			// we compute polys back to front
			// find intersections
			degree = 0;
			for (size_t j = 0; j < 12; j++)
			{
				double u;

				FLIVR::Vector vec = -view.direction();
				FLIVR::Point pnt = view.parameter(t);
				bool intersects = edge_[j].planeIntersectParameter
					(vec, pnt, u);
				if (intersects && u >= 0.0 && u <= 1.0)
				{
					Point p;
					p = edge_[j].parameter(u);
					vv[degree] = (Vector)p;
					p = tex_edge_[j].parameter(u);
					tt[degree] = (Vector)p;
					degree++;
				}
			}

			if (degree < 3 || degree >6) continue;
			bool sorted = degree > 3;
			uint32_t idx[6];
			if (sorted) {
				// compute centroids
				Vector vc(0.0, 0.0, 0.0), tc(0.0, 0.0, 0.0);
				for (int j = 0; j < degree; j++)
				{
					vc += vv[j]; tc += tt[j];
				}
				vc /= (double)degree; tc /= (double)degree;

				// sort vertices
				double pa[6];
				for (uint32_t i = 0; i < degree; i++)
				{
					double vx = Dot(vv[i] - vc, right);
					double vy = Dot(vv[i] - vc, up);

					// compute pseudo-angle
					pa[i] = vy / (fabs(vx) + fabs(vy));
					if (vx < 0.0) pa[i] = 2.0 - pa[i];
					else if (vy < 0.0) pa[i] = 4.0 + pa[i];
					// init idx
					idx[i] = i;
				}
				Sort(pa, idx, degree);
			}
			// save all of the indices
			for (uint32_t j = 1; j < degree - 1; j++) {
				index.push_back(vert_count);
				index.push_back(vert_count + j);
				index.push_back(vert_count + j + 1);
			}
			// save all of the verts
			for (uint32_t j = 0; j < degree; j++)
			{
				vertex.push_back((sorted ? vv[idx[j]] : vv[j]).x());
				vertex.push_back((sorted ? vv[idx[j]] : vv[j]).y());
				vertex.push_back((sorted ? vv[idx[j]] : vv[j]).z());
				vertex.push_back((sorted ? tt[idx[j]] : tt[j]).x());
				vertex.push_back((sorted ? tt[idx[j]] : tt[j]).y());
				vertex.push_back((sorted ? tt[idx[j]] : tt[j]).z());
				vert_count++;
			}

			size.push_back(degree);
		}
	}