void TesselateSplinePatch(u8 *&dest, int &count, const SplinePatch &spatch, u32 origVertType) {
	const float third = 1.0f / 3.0f;

	if (g_Config.bLowQualitySplineBezier) {
		// Fast and easy way - just draw the control points, generate some very basic normal vector substitutes.
		// Very inaccurate but okay for Loco Roco. Maybe should keep it as an option because it's fast.

		const int tile_min_u = (spatch.type_u & START_OPEN) ? 0 : 1;
		const int tile_min_v = (spatch.type_v & START_OPEN) ? 0 : 1;
		const int tile_max_u = (spatch.type_u & END_OPEN) ? spatch.count_u - 1 : spatch.count_u - 2;
		const int tile_max_v = (spatch.type_v & END_OPEN) ? spatch.count_v - 1 : spatch.count_v - 2;

		for (int tile_v = tile_min_v; tile_v < tile_max_v; ++tile_v) {
			for (int tile_u = tile_min_u; tile_u < tile_max_u; ++tile_u) {
				int point_index = tile_u + tile_v * spatch.count_u;

				SimpleVertex v0 = *spatch.points[point_index];
				SimpleVertex v1 = *spatch.points[point_index+1];
				SimpleVertex v2 = *spatch.points[point_index+spatch.count_u];
				SimpleVertex v3 = *spatch.points[point_index+spatch.count_u+1];

				// Generate UV. TODO: Do this even if UV specified in control points?
				if ((origVertType & GE_VTYPE_TC_MASK) == 0) {
					float u = tile_u * third;
					float v = tile_v * third;
					v0.uv[0] = u;
					v0.uv[1] = v;
					v1.uv[0] = u + third;
					v1.uv[1] = v;
					v2.uv[0] = u;
					v2.uv[1] = v + third;
					v3.uv[0] = u + third;
					v3.uv[1] = v + third;
				}

				// Generate normal if lighting is enabled (otherwise there's no point).
				// This is a really poor quality algorithm, we get facet normals.
				if (gstate.isLightingEnabled()) {
					Vec3f norm = Cross(v1.pos - v0.pos, v2.pos - v0.pos);
					norm.Normalize();
					if (gstate.patchfacing & 1)
						norm *= -1.0f;
					v0.nrm = norm;
					v1.nrm = norm;
					v2.nrm = norm;
					v3.nrm = norm;
				}

				CopyQuad(dest, &v0, &v1, &v2, &v3);
				count += 6;
			}
		}
	} else {
		// Full correct tessellation of spline patches.
		// Does not yet generate normals and is atrociously slow (see spline_s...)

		// First, generate knot vectors.
		int n = spatch.count_u - 1;
		int m = spatch.count_v - 1;

		float *knot_u = new float[n + 5];
		float *knot_v = new float[m + 5];
		spline_knot(n, spatch.type_u, knot_u);
		spline_knot(m, spatch.type_v, knot_v);

		int patch_div_s = gstate.getPatchDivisionU();
		int patch_div_t = gstate.getPatchDivisionV();

		// Increase tesselation based on the size. Should be approximately right?
		// JPCSP is wrong at least because their method results in square loco roco.
		patch_div_s = (spatch.count_u - 3) * patch_div_s / 3;
		patch_div_t = (spatch.count_v - 3) * patch_div_t / 3;
		if (patch_div_s == 0) patch_div_s = 1;
		if (patch_div_t == 0) patch_div_t = 1;

		// TODO: Remove this cap when spline_s has been optimized. 
		if (patch_div_s > 64) patch_div_s = 64;
		if (patch_div_t > 64) patch_div_t = 64;

		// First compute all the vertices and put them in an array
		SimpleVertex *vertices = new SimpleVertex[(patch_div_s + 1) * (patch_div_t + 1)];

		float tu_width = 1.0f + (spatch.count_u - 4) * 1.0f/3.0f;
		float tv_height = 1.0f + (spatch.count_v - 4) * 1.0f/3.0f;

		bool computeNormals = gstate.isLightingEnabled();
		for (int tile_v = 0; tile_v < patch_div_t + 1; tile_v++) {
			float v = ((float)tile_v * (float)(m - 2) / (float)(patch_div_t + 0.00001f));  // epsilon to prevent division by 0 in spline_s
			for (int tile_u = 0; tile_u < patch_div_s + 1; tile_u++) {
				float u = ((float)tile_u * (float)(n - 2) / (float)(patch_div_s + 0.00001f));

				SimpleVertex *vert = &vertices[tile_v * (patch_div_s + 1) + tile_u];
				vert->pos.SetZero();
				if (origVertType & GE_VTYPE_NRM_MASK) {
					vert->nrm.SetZero();
				} else {
					vert->nrm.SetZero();
					vert->nrm.z = 1.0f;
				}
				if (origVertType & GE_VTYPE_COL_MASK) {
					memset(vert->color, 0, 4);
				} else {
					memcpy(vert->color, spatch.points[0]->color, 4);
				}
				if (origVertType & GE_VTYPE_TC_MASK) {
					vert->uv[0] = 0.0f;
					vert->uv[1] = 0.0f;
				} else {
					vert->uv[0] = tu_width * ((float)tile_u / (float)patch_div_s);
					vert->uv[1] = tv_height * ((float)tile_v / (float)patch_div_t);
				}

				// Collect influences from surrounding control points.
				float u_weights[4];
				float v_weights[4];
				
				int iu = (int)u;
				int iv = (int)v;
				spline_n_4(iu, u, knot_u, u_weights);
				spline_n_4(iv, v, knot_v, v_weights);

				for (int ii = 0; ii < 4; ++ii) {
					for (int jj = 0; jj < 4; ++jj) {
						float u_spline = u_weights[ii];
						float v_spline = v_weights[jj];
						float f = u_spline * v_spline;
						
						if (f > 0.0f) {
							SimpleVertex *a = spatch.points[spatch.count_u * (iv + jj) + (iu + ii)];
							vert->pos += a->pos * f;
							if (origVertType & GE_VTYPE_TC_MASK) {
								vert->uv[0] += a->uv[0] * f;
								vert->uv[1] += a->uv[1] * f;
							}
							if (origVertType & GE_VTYPE_COL_MASK) {
								vert->color[0] += a->color[0] * f;
								vert->color[1] += a->color[1] * f;
								vert->color[2] += a->color[2] * f;
								vert->color[3] += a->color[3] * f;
							}
							if (origVertType & GE_VTYPE_NRM_MASK) {
								vert->nrm += a->nrm * f;
							}
						}
					}
				}
				if (origVertType & GE_VTYPE_NRM_MASK) {
					vert->nrm.Normalize();
				}
			}
		}

		delete [] knot_u;
		delete [] knot_v;

		// Hacky normal generation through central difference.
		if (gstate.isLightingEnabled() && (origVertType & GE_VTYPE_NRM_MASK) == 0) {
			for (int v = 0; v < patch_div_t + 1; v++) {
				for (int u = 0; u < patch_div_s + 1; u++) {
					int l = std::max(0, u - 1);
					int t = std::max(0, v - 1);
					int r = std::min(patch_div_s, u + 1);
					int b = std::min(patch_div_t, v + 1);

					const Vec3f &right = vertices[v * (patch_div_s + 1) + r].pos - vertices[v * (patch_div_s + 1) + l].pos;
					const Vec3f &down = vertices[b * (patch_div_s + 1) + u].pos - vertices[t * (patch_div_s + 1) + u].pos;

					vertices[v * (patch_div_s + 1) + u].nrm = Cross(right, down).Normalized();
					if (gstate.patchfacing & 1) {
						vertices[v * (patch_div_s + 1) + u].nrm *= -1.0f;
					}
				}
			}
		}

		// Tesselate. TODO: Use indices so we only need to emit 4 vertices per pair of triangles instead of six.
		for (int tile_v = 0; tile_v < patch_div_t; ++tile_v) {
			for (int tile_u = 0; tile_u < patch_div_s; ++tile_u) {
				float u = ((float)tile_u / (float)patch_div_s);
				float v = ((float)tile_v / (float)patch_div_t);

				SimpleVertex *v0 = &vertices[tile_v * (patch_div_s + 1) + tile_u];
				SimpleVertex *v1 = &vertices[tile_v * (patch_div_s + 1) + tile_u + 1];
				SimpleVertex *v2 = &vertices[(tile_v + 1) * (patch_div_s + 1) + tile_u];
				SimpleVertex *v3 = &vertices[(tile_v + 1) * (patch_div_s + 1) + tile_u + 1];

				CopyQuad(dest, v0, v1, v2, v3);
				count += 6;
			}
		}

		delete [] vertices;
	}
}