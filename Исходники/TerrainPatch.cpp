bool
TerrainPatch::BuildDetailLevel(int level)
{
	int i, j;

	int detail_size = 1 << level;
	int ds1 = detail_size+1;

	if (detail_size > PATCH_SIZE)
	return false;

	Model* model   = new(__FILE__,__LINE__) Model;
	detail_levels[level] = model;

	model->SetLuminous(luminous);
	model->SetDynamic(true);

	const int   NUM_STRIPS        = 4;
	const int   NUM_INDICES_TRI   = 3;
	const int   NUM_INDICES_QUAD  = 6;

	int nverts     = ds1*ds1 + ds1*2*NUM_STRIPS;
	int npolys     = detail_size*detail_size*2;
	int strip_len  = detail_size;
	int total      = npolys + strip_len*NUM_STRIPS;

	if (water) {
		nverts      = ds1*ds1;
		strip_len   = 0;
		total       = npolys;
	}

	Surface*    s     = new(__FILE__,__LINE__) Surface;
	VertexSet*  vset  = 0;

	if (s) {
		s->SetName("default");
		s->CreateVerts(nverts);
		s->CreatePolys(total);
		s->AddIndices(npolys*NUM_INDICES_TRI + strip_len*NUM_STRIPS*NUM_INDICES_QUAD);

		vset = s->GetVertexSet();
		if (!water)
		vset->CreateAdditionalTexCoords();

		ZeroMemory(vset->loc,      nverts * sizeof(Vec3));
		ZeroMemory(vset->diffuse,  nverts * sizeof(DWORD));
		ZeroMemory(vset->specular, nverts * sizeof(DWORD));
		ZeroMemory(vset->tu,       nverts * sizeof(float));
		ZeroMemory(vset->tv,       nverts * sizeof(float));
		if (!water) {
			ZeroMemory(vset->tu1,      nverts * sizeof(float));
			ZeroMemory(vset->tv1,      nverts * sizeof(float));
		}
		ZeroMemory(vset->rw,       nverts * sizeof(float));

		// initialize vertices
		Vec3*  pVert   = vset->loc;
		float* pTu     = vset->tu;
		float* pTv     = vset->tv;
		float* pTu1    = vset->tu1;
		float* pTv1    = vset->tv1;
		DWORD* pSpec   = vset->specular;

		int    dscale  = (PATCH_SIZE-1)/detail_size;
		double dt      = 0.0625 / (ds1-1); // terrain texture scale
		double dtt     = 2.0000 / (ds1-1); // tile texture scale
		double tu0     = (double) rect.x / rect.w / 16.0 + 1.0/16.0;
		double tv0     = (double) rect.y / rect.h / 16.0;

		// surface verts
		for (i = 0; i < ds1; i++) {
			for (j = 0; j < ds1; j++) {
				*pVert   = Vec3((float) (j* scale * dscale - (HALF_PATCH_SIZE*scale)),
				(float) (heights[i*dscale*PATCH_SIZE + j*dscale]),
				(float) (i* scale * dscale - (HALF_PATCH_SIZE*scale)));

				if (level >= 2) {
					*pTu++   = (float) (-j*dtt);
					*pTv++   = (float) ( i*dtt);

					if (level >= 4 && !water) {
						*pTu1++  = (float) (-j*dtt*3);
						*pTv1++  = (float) ( i*dtt*3);
					}

					*pSpec++ = BlendValue(pVert->y);
				}

				else {
					*pTu++   = (float) (tu0 - j*dt);
					*pTv++   = (float) (tv0 + i*dt);
				}

				pVert++;
			}
		}

		if (!water) {
			// strip 1 & 2 verts
			for (i = 0; i < ds1; i += detail_size) {
				for (j = 0; j < ds1; j++) {
					Vec3 vl  = Vec3((float) (j* scale * dscale - (HALF_PATCH_SIZE*scale)),
					(float) (heights[i*dscale*PATCH_SIZE + j*dscale]),
					(float) (i* scale * dscale - (HALF_PATCH_SIZE*scale)));

					*pVert++ = vl;

					DWORD blend = 0;

					if (level >= 2) {
						blend = BlendValue(vl.y);

						*pSpec++ = blend;
						*pTu++   = (float) (-j*dtt);
						*pTv++   = (float) ( i*dtt);
					}

					else {
						*pTu++   = (float) (tu0 - j*dt);
						*pTv++   = (float) (tv0 + i*dt);
					}

					vl.y     = -5000.0f;

					*pVert++ = vl;

					if (level >= 2) {
						*pSpec++ = blend;
						*pTu++   = (float) (-j*dtt);
						*pTv++   = (float) ( i*dtt);
					}

					else {
						*pTu++   = (float) (tu0 - j*dt);
						*pTv++   = (float) (tv0 + i*dt);
					}
				}
			}

			// strip 3 & 4 verts
			for (j = 0; j < ds1; j += detail_size) {
				for (i = 0; i < ds1; i++) {
					Vec3 vl  = Vec3((float) (j* scale * dscale - (HALF_PATCH_SIZE*scale)),
					(float) (heights[i*dscale*PATCH_SIZE + j*dscale]),
					(float) (i* scale * dscale - (HALF_PATCH_SIZE*scale)));

					*pVert++ = vl;

					DWORD blend = 0;

					if (level >= 2) {
						blend = BlendValue(vl.y);

						*pSpec++ = blend;
						*pTu++   = (float) (-j*dtt);
						*pTv++   = (float) ( i*dtt);
					}

					else {
						*pTu++   = (float) (tu0 - j*dt);
						*pTv++   = (float) (tv0 + i*dt);
					}

					vl.y     = -5000.0f;

					*pVert++ = vl;

					if (level >= 2) {
						*pSpec++ = blend;
						*pTu++   = (float) (-j*dtt);
						*pTv++   = (float) ( i*dtt);
					}

					else {
						*pTu++   = (float) (tu0 - j*dt);
						*pTv++   = (float) (tv0 + i*dt);
					}
				}
			}
		}

		Material* m = materials.first();

		// initialize the polys
		for (i = 0; i < npolys; i++) {
			Poly* p        = s->GetPolys() + i;
			p->nverts      = 3;
			p->vertex_set  = vset;
			p->visible     = 1;
			p->sortval     = 0;
			p->material    = m;

			if (level >= 2 && !water) {
				p->material = materials.at(1);
				p->sortval  = 1;
			}
		}

		for (i = npolys; i < total; i++) {
			Poly* p        = s->GetPolys() + i;
			p->nverts      = 4;
			p->vertex_set  = vset;
			p->visible     = 1;
			p->sortval     = 0;
			p->material    = m;
		}

		int index = 0;

		// build main patch polys:
		for (i = 0; i < detail_size; i++) {
			for (j = 0; j < detail_size; j++) {
				int v[4] = {
					(ds1 * (i  ) + (j  )),
					(ds1 * (i  ) + (j+1)),
					(ds1 * (i+1) + (j  )),
					(ds1 * (i+1) + (j+1)) };

				bisect(vset, v);

				// first triangle
				Poly* p = s->GetPolys() + index++;
				p->verts[0]   = v[0];
				p->verts[1]   = v[1];
				p->verts[2]   = v[3];

				if (level >= 2 && !water) {
					int layer = CalcLayer(p) + 1;
					p->material = materials.at(layer);
					p->sortval  = layer;
				}

				// second triangle
				p = s->GetPolys() + index++;
				p->verts[0]   = v[0];
				p->verts[1]   = v[3];
				p->verts[2]   = v[2];

				if (level >= 2 && !water) {
					int layer = CalcLayer(p) + 1;
					p->material = materials.at(layer);
					p->sortval  = layer;
				}
			}
		}

		// build vertical edge strip polys:

		if (!water) {
			for (i = 0; i < NUM_STRIPS; i++) {
				Poly* p = s->GetPolys() + npolys + i*strip_len;
				int   base_index = ds1*ds1 + ds1*2*i;

				for (j = 0; j < strip_len; j++) {
					int v       = base_index + j * 2;
					p->nverts   = 4;

					if (i == 1 || i == 2) {
						p->verts[0] = v;
						p->verts[1] = v+2;
						p->verts[2] = v+3;
						p->verts[3] = v+1;
					}

					else {
						p->verts[0] = v;
						p->verts[1] = v+1;
						p->verts[2] = v+3;
						p->verts[3] = v+2;
					}

					if (level >= 2) {
						int layer = CalcLayer(p) + 1;
						p->material = materials.at(layer);
						p->sortval  = layer;
					}

					p++;
				}
			}
		}

		// update the poly planes:
		for (i = 0; i < total; i++) {
			Poly*   p      = s->GetPolys() + i;
			Plane&  plane  = p->plane;
			WORD*   v      = p->verts;

			plane = Plane(vset->loc[v[0]] + loc,
			vset->loc[v[1]] + loc,
			vset->loc[v[2]] + loc);
		}

		s->Normalize();

		// create continguous segments for each material:
		// sort the polys by material index:
		qsort((void*) s->GetPolys(), s->NumPolys(), sizeof(Poly), mcomp);

		// then assign them to cohesive segments:
		Segment* segment = 0;
		Poly*    spolys  = s->GetPolys();

		for (int n = 0; n < s->NumPolys(); n++) {
			if (segment && segment->material == spolys[n].material) {
				segment->npolys++;
			}
			else {
				segment = 0;
			}

			if (!segment) {
				segment = new(__FILE__,__LINE__) Segment;

				segment->npolys   = 1;
				segment->polys    = &spolys[n];
				segment->material = segment->polys->material;
				segment->model    = model;

				s->GetSegments().append(segment);
			}
		}

		Solid::EnableCollision(false);
		model->AddSurface(s);
		Solid::EnableCollision(true);

		// copy vertex normals:
		const Vec3B* tnorms = terrain->Normals();

		for (i = 0; i < ds1; i++) {
			for (j = 0; j < ds1; j++) {

				if (water) {
					vset->nrm[i*ds1+j] = Point(0,1,0);
				}

				// blend adjacent normals:
				else if (dscale > 1) {
					Point normal;

					// but don't blend more than 16 normals per vertex:
					int step = 1;
					if (dscale > 4)
					step = dscale / 4;

					for (int dy = -dscale/2; dy < dscale/2; dy += step) {
						for (int dx = -dscale/2; dx < dscale/2; dx += step) {
							int ix = rect.x + (ds1-1-j)*dscale + dx;
							int iy = rect.y + i*dscale + dy;

							if (ix < 0)                ix = 0;
							if (ix > terrain_width-1)  ix = terrain_width-1;
							if (iy < 0)                iy = 0;
							if (iy > terrain_width-1)  iy = terrain_width-1;

							Vec3B vbn = tnorms[iy*terrain_width + ix];
							normal += Point((128-vbn.x)/127.0, (vbn.z-128)/127.0, (vbn.y-128)/127.0);
						}
					}

					normal.Normalize();
					vset->nrm[i*ds1+j] = normal;
				}

				// just copy the one normal:
				else {
					Vec3B vbn    = tnorms[(rect.y + i*dscale)*terrain_width + (rect.x + (ds1-1-j) * dscale)];
					Point normal = Point((128-vbn.x)/127.0, (vbn.z-128)/127.0, (vbn.y-128)/127.0);
					vset->nrm[i*ds1+j] = normal;
				}
			}
		}

		if (!water) {
			pVert = &vset->nrm[ds1*ds1];

			// strip 1 & 2 verts
			for (i = 0; i < ds1; i += detail_size) {
				for (j = 0; j < ds1; j++) {
					Vec3 vn  = vset->nrm[i*ds1 + j];

					*pVert++ = vn;
					*pVert++ = vn;
				}
			}

			// strip 3 & 4 verts
			for (j = 0; j < ds1; j += detail_size) {
				for (i = 0; i < ds1; i++) {
					Vec3 vn  = vset->nrm[i*ds1 + j];

					*pVert++ = vn;
					*pVert++ = vn;
				}
			}
		}
	}

	if (level > max_detail)
	max_detail = level;

	return true;
}