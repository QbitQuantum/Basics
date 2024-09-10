HaloRen *RE_inithalo_particle(Render *re, ObjectRen *obr, DerivedMesh *dm, Material *ma,
                              const float vec[3], const float vec1[3],
                              const float *orco, const float *uvco, float hasize, float vectsize, int seed, const float pa_co[3])
{
	HaloRen *har;
	MTex *mtex;
	float tin, tr, tg, tb, ta;
	float xn, yn, zn, texvec[3], hoco[4], hoco1[4], in[3], tex[3], out[3];
	int i, hasrgb;

	if (hasize==0.0f) return NULL;

	projectverto(vec, re->winmat, hoco);
	if (hoco[3]==0.0f) return NULL;
	if (vec1) {
		projectverto(vec1, re->winmat, hoco1);
		if (hoco1[3]==0.0f) return NULL;
	}

	har= RE_findOrAddHalo(obr, obr->tothalo++);
	copy_v3_v3(har->co, vec);
	har->hasize= hasize;

	/* actual projectvert is done in function project_renderdata() because of parts/border/pano */
	/* we do it here for sorting of halos */
	zn= hoco[3];
	har->xs= 0.5f*re->winx*(hoco[0]/zn);
	har->ys= 0.5f*re->winy*(hoco[1]/zn);
	har->zs= 0x7FFFFF*(hoco[2]/zn);
	
	har->zBufDist = 0x7FFFFFFF*(hoco[2]/zn); 
	
	/* halovect */
	if (vec1) {

		har->type |= HA_VECT;

		xn=  har->xs - 0.5f*re->winx*(hoco1[0]/hoco1[3]);
		yn=  har->ys - 0.5f*re->winy*(hoco1[1]/hoco1[3]);
		if (xn==0.0f || (xn==0.0f && yn==0.0f)) zn= 0.0;
		else zn= atan2(yn, xn);

		har->sin= sin(zn);
		har->cos= cos(zn);
		zn= len_v3v3(vec1, vec)*0.5f;

		har->hasize= vectsize*zn + (1.0f-vectsize)*hasize;
		
		sub_v3_v3v3(har->no, vec, vec1);
		normalize_v3(har->no);
	}

	if (ma->mode & MA_HALO_XALPHA) har->type |= HA_XALPHA;

	har->alfa= ma->alpha;
	har->r= ma->r;
	har->g= ma->g;
	har->b= ma->b;
	har->add= (255.0f*ma->add);
	har->mat= ma;
	har->hard= ma->har;
	har->seed= seed % 256;

	if (ma->mode & MA_STAR) har->starpoints= ma->starc;
	if (ma->mode & MA_HALO_LINES) har->linec= ma->linec;
	if (ma->mode & MA_HALO_RINGS) har->ringc= ma->ringc;
	if (ma->mode & MA_HALO_FLARE) har->flarec= ma->flarec;

	if ((ma->mode & MA_HALOTEX) && ma->mtex[0])
		har->tex= 1;
	
	for (i=0; i<MAX_MTEX; i++)
		if (ma->mtex[i] && (ma->septex & (1<<i))==0) {
			mtex= ma->mtex[i];
			copy_v3_v3(texvec, vec);

			if (mtex->texco & TEXCO_NORM) {
				;
			}
			else if (mtex->texco & TEXCO_OBJECT) {
				if (mtex->object)
					mul_m4_v3(mtex->object->imat_ren, texvec);
			}
			else if (mtex->texco & TEXCO_GLOB) {
				copy_v3_v3(texvec, vec);
			}
			else if (mtex->texco & TEXCO_UV && uvco) {
				int uv_index=CustomData_get_named_layer_index(&dm->faceData, CD_MTFACE, mtex->uvname);
				if (uv_index<0)
					uv_index=CustomData_get_active_layer_index(&dm->faceData, CD_MTFACE);

				uv_index-=CustomData_get_layer_index(&dm->faceData, CD_MTFACE);

				texvec[0]=2.0f*uvco[2*uv_index]-1.0f;
				texvec[1]=2.0f*uvco[2*uv_index+1]-1.0f;
				texvec[2]=0.0f;
			}
			else if (mtex->texco & TEXCO_PARTICLE) {
				/* particle coordinates in range [0, 1] */
				texvec[0] = 2.f * pa_co[0] - 1.f;
				texvec[1] = 2.f * pa_co[1] - 1.f;
				texvec[2] = pa_co[2];
			}
			else if (orco) {
				copy_v3_v3(texvec, orco);
			}

			hasrgb = externtex(mtex, texvec, &tin, &tr, &tg, &tb, &ta, 0);

			//yn= tin*mtex->colfac;
			//zn= tin*mtex->alphafac;
			if (mtex->mapto & MAP_COL) {
				tex[0]=tr;
				tex[1]=tg;
				tex[2]=tb;
				out[0]=har->r;
				out[1]=har->g;
				out[2]=har->b;

				texture_rgb_blend(in, tex, out, tin, mtex->colfac, mtex->blendtype);
			//	zn= 1.0-yn;
				//har->r= (yn*tr+ zn*ma->r);
				//har->g= (yn*tg+ zn*ma->g);
				//har->b= (yn*tb+ zn*ma->b);
				har->r= in[0];
				har->g= in[1];
				har->b= in[2];
			}

			/* alpha returned, so let's use it instead of intensity */
			if (hasrgb)
				tin = ta;

			if (mtex->mapto & MAP_ALPHA)
				har->alfa = texture_value_blend(mtex->def_var, har->alfa, tin, mtex->alphafac, mtex->blendtype);
			if (mtex->mapto & MAP_HAR)
				har->hard = 1.0f+126.0f*texture_value_blend(mtex->def_var, ((float)har->hard)/127.0f, tin, mtex->hardfac, mtex->blendtype);
			if (mtex->mapto & MAP_RAYMIRR)
				har->hasize = 100.0f*texture_value_blend(mtex->def_var, har->hasize/100.0f, tin, mtex->raymirrfac, mtex->blendtype);
			if (mtex->mapto & MAP_TRANSLU) {
				float add = texture_value_blend(mtex->def_var, (float)har->add/255.0f, tin, mtex->translfac, mtex->blendtype);
				CLAMP(add, 0.f, 1.f);
				har->add = 255.0f*add;
			}
			/* now what on earth is this good for?? */
			//if (mtex->texco & 16) {
			//	har->alfa= tin;
			//}
		}

	return har;
}