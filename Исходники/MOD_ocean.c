static DerivedMesh *doOcean(ModifierData *md, Object *ob,
                            DerivedMesh *derivedData,
                            int UNUSED(useRenderParams))
{
	OceanModifierData *omd = (OceanModifierData *) md;

	DerivedMesh *dm = NULL;
	OceanResult ocr;

	MVert *mverts;

	int cfra;
	int i, j;

	/* use cached & inverted value for speed
	 * expanded this would read...
	 *
	 * (axis / (omd->size * omd->spatial_size)) + 0.5f) */
#define OCEAN_CO(_size_co_inv, _v) ((_v * _size_co_inv) + 0.5f)

	const float size_co_inv = 1.0f / (omd->size * omd->spatial_size);

	/* can happen in when size is small, avoid bad array lookups later and quit now */
	if (!finite(size_co_inv)) {
		return derivedData;
	}

	/* update modifier */
	if (omd->refresh & MOD_OCEAN_REFRESH_ADD) {
		omd->ocean = BKE_ocean_add();
	}
	if (omd->refresh & MOD_OCEAN_REFRESH_RESET) {
		init_ocean_modifier(omd);
	}
	if (omd->refresh & MOD_OCEAN_REFRESH_CLEAR_CACHE) {
		clear_cache_data(omd);
	}
	omd->refresh = 0;

	/* do ocean simulation */
	if (omd->cached == true) {
		if (!omd->oceancache) {
			init_cache_data(ob, omd);
		}
		BKE_ocean_simulate_cache(omd->oceancache, md->scene->r.cfra);
	}
	else {
		simulate_ocean_modifier(omd);
	}

	if (omd->geometry_mode == MOD_OCEAN_GEOM_GENERATE) {
		dm = generate_ocean_geometry(omd);
		DM_ensure_normals(dm);
	}
	else if (omd->geometry_mode == MOD_OCEAN_GEOM_DISPLACE) {
		dm = CDDM_copy(derivedData);
	}

	cfra = md->scene->r.cfra;
	CLAMP(cfra, omd->bakestart, omd->bakeend);
	cfra -= omd->bakestart; /* shift to 0 based */

	mverts = dm->getVertArray(dm);

	/* add vcols before displacement - allows lookup based on position */

	if (omd->flag & MOD_OCEAN_GENERATE_FOAM) {
		if (CustomData_number_of_layers(&dm->loopData, CD_MLOOPCOL) < MAX_MCOL) {
			const int num_polys = dm->getNumPolys(dm);
			const int num_loops = dm->getNumLoops(dm);
			MLoop *mloops = dm->getLoopArray(dm);
			MLoopCol *mloopcols = CustomData_add_layer_named(
			                          &dm->loopData, CD_MLOOPCOL, CD_CALLOC, NULL, num_loops, omd->foamlayername);

			if (mloopcols) { /* unlikely to fail */
				MPoly *mpolys = dm->getPolyArray(dm);
				MPoly *mp;

				for (i = 0, mp = mpolys; i < num_polys; i++, mp++) {
					MLoop *ml = &mloops[mp->loopstart];
					MLoopCol *mlcol = &mloopcols[mp->loopstart];

					for (j = mp->totloop; j--; ml++, mlcol++) {
						const float *vco = mverts[ml->v].co;
						const float u = OCEAN_CO(size_co_inv, vco[0]);
						const float v = OCEAN_CO(size_co_inv, vco[1]);
						float foam;

						if (omd->oceancache && omd->cached == true) {
							BKE_ocean_cache_eval_uv(omd->oceancache, &ocr, cfra, u, v);
							foam = ocr.foam;
							CLAMP(foam, 0.0f, 1.0f);
						}
						else {
							BKE_ocean_eval_uv(omd->ocean, &ocr, u, v);
							foam = BKE_ocean_jminus_to_foam(ocr.Jminus, omd->foam_coverage);
						}

						mlcol->r = mlcol->g = mlcol->b = (char)(foam * 255);
						/* This needs to be set (render engine uses) */
						mlcol->a = 255;
					}
				}
			}
		}
	}


	/* displace the geometry */

	/* Note: tried to parallelized that one and previous foam loop, but gives 20% slower results... odd. */
	{
		const int num_verts = dm->getNumVerts(dm);

		for (i = 0; i < num_verts; i++) {
			float *vco = mverts[i].co;
			const float u = OCEAN_CO(size_co_inv, vco[0]);
			const float v = OCEAN_CO(size_co_inv, vco[1]);

			if (omd->oceancache && omd->cached == true) {
				BKE_ocean_cache_eval_uv(omd->oceancache, &ocr, cfra, u, v);
			}
			else {
				BKE_ocean_eval_uv(omd->ocean, &ocr, u, v);
			}

			vco[2] += ocr.disp[1];

			if (omd->chop_amount > 0.0f) {
				vco[0] += ocr.disp[0];
				vco[1] += ocr.disp[2];
			}
		}
	}

#undef OCEAN_CO

	return dm;
}