/**
 * @brief CG_AddParticleToScene
 * @param[in,out] p
 * @param[in] org
 * @param alpha - unused
 */
void CG_AddParticleToScene(cparticle_t *p, vec3_t org, float alpha)
{
	polyVert_t verts[4];
	polyVert_t TRIverts[3];

	switch (p->type)
	{
	case P_WEATHER:
	case P_WEATHER_TURBULENT:
	case P_WEATHER_FLURRY:
	case P_BUBBLE:
	case P_BUBBLE_TURBULENT:  // create a front facing polygon
	{
		if (p->type != P_WEATHER_FLURRY)
		{
			if (p->type == P_BUBBLE || p->type == P_BUBBLE_TURBULENT)
			{
				if (org[2] > p->end)
				{
					p->time = cg.time;
					VectorCopy(org, p->org);   // fixes rare snow flakes that flicker on the ground

					p->org[2] = (p->start + crandom() * 4);

					if (p->type == P_BUBBLE_TURBULENT)
					{
						p->vel[0] = crandom() * 4;
						p->vel[1] = crandom() * 4;
					}
				}
			}
			else
			{
				if (org[2] < p->end)
				{
					p->time = cg.time;
					VectorCopy(org, p->org);   // fixes rare snow flakes that flicker on the ground

					while (p->org[2] < p->end)
					{
						p->org[2] += (p->start - p->end);
					}

					if (p->type == P_WEATHER_TURBULENT)
					{
						p->vel[0] = crandom() * 16;
						p->vel[1] = crandom() * 16;
					}
				}
			}

			// snow pvs check
			if (!p->link)
			{
				return;
			}

			p->alpha = 1;
		}

		// had to do this or MAX_POLYS is being exceeded in village1.bsp
		if (VectorDistanceSquared(cg.snap->ps.origin, org) > Square(1024))
		{
			return;
		}

		if (p->type == P_BUBBLE || p->type == P_BUBBLE_TURBULENT)
		{
			vec3_t point;

			VectorMA(org, -p->height, vup, point);
			VectorMA(point, -p->width, vright, point);
			VectorCopy(point, verts[0].xyz);
			verts[0].st[0]       = 0;
			verts[0].st[1]       = 0;
			verts[0].modulate[0] = 255;
			verts[0].modulate[1] = 255;
			verts[0].modulate[2] = 255;
			verts[0].modulate[3] = (byte)(255 * p->alpha);

			VectorMA(org, -p->height, vup, point);
			VectorMA(point, p->width, vright, point);
			VectorCopy(point, verts[1].xyz);
			verts[1].st[0]       = 0;
			verts[1].st[1]       = 1;
			verts[1].modulate[0] = 255;
			verts[1].modulate[1] = 255;
			verts[1].modulate[2] = 255;
			verts[1].modulate[3] = (byte)(255 * p->alpha);

			VectorMA(org, p->height, vup, point);
			VectorMA(point, p->width, vright, point);
			VectorCopy(point, verts[2].xyz);
			verts[2].st[0]       = 1;
			verts[2].st[1]       = 1;
			verts[2].modulate[0] = 255;
			verts[2].modulate[1] = 255;
			verts[2].modulate[2] = 255;
			verts[2].modulate[3] = (byte)(255 * p->alpha);

			VectorMA(org, p->height, vup, point);
			VectorMA(point, -p->width, vright, point);
			VectorCopy(point, verts[3].xyz);
			verts[3].st[0]       = 1;
			verts[3].st[1]       = 0;
			verts[3].modulate[0] = 255;
			verts[3].modulate[1] = 255;
			verts[3].modulate[2] = 255;
			verts[3].modulate[3] = (byte)(255 * p->alpha);
		}
		else
		{
			vec3_t point;

			VectorMA(org, -p->height, vup, point);
			VectorMA(point, -p->width, vright, point);
			VectorCopy(point, TRIverts[0].xyz);
			TRIverts[0].st[0]       = 1;
			TRIverts[0].st[1]       = 0;
			TRIverts[0].modulate[0] = 255;
			TRIverts[0].modulate[1] = 255;
			TRIverts[0].modulate[2] = 255;
			TRIverts[0].modulate[3] = (byte)(255 * p->alpha);

			VectorMA(org, p->height, vup, point);
			VectorMA(point, -p->width, vright, point);
			VectorCopy(point, TRIverts[1].xyz);
			TRIverts[1].st[0]       = 0;
			TRIverts[1].st[1]       = 0;
			TRIverts[1].modulate[0] = 255;
			TRIverts[1].modulate[1] = 255;
			TRIverts[1].modulate[2] = 255;
			TRIverts[1].modulate[3] = (byte)(255 * p->alpha);

			VectorMA(org, p->height, vup, point);
			VectorMA(point, p->width, vright, point);
			VectorCopy(point, TRIverts[2].xyz);
			TRIverts[2].st[0]       = 0;
			TRIverts[2].st[1]       = 1;
			TRIverts[2].modulate[0] = 255;
			TRIverts[2].modulate[1] = 255;
			TRIverts[2].modulate[2] = 255;
			TRIverts[2].modulate[3] = (byte)(255 * p->alpha);
		}
	}
	break;
	case P_SPRITE:
	{
		vec3_t point, rr, ru, rotate_ang;
		float  time   = cg.time - p->time;
		float  time2  = p->endtime - p->time;
		float  ratio  = time / time2;
		float  width  = p->width + (ratio * (p->endwidth - p->width));
		float  height = p->height + (ratio * (p->endheight - p->height));

		if (p->roll)
		{
			vectoangles(cg.refdef_current->viewaxis[0], rotate_ang);
			rotate_ang[ROLL] += p->roll;
			AngleVectors(rotate_ang, NULL, rr, ru);
		}

		if (p->roll)
		{
			VectorMA(org, -height, ru, point);
			VectorMA(point, -width, rr, point);
		}
		else
		{
			VectorMA(org, -height, vup, point);
			VectorMA(point, -width, vright, point);
		}
		VectorCopy(point, verts[0].xyz);
		verts[0].st[0]       = 0;
		verts[0].st[1]       = 0;
		verts[0].modulate[0] = 255;
		verts[0].modulate[1] = 255;
		verts[0].modulate[2] = 255;
		verts[0].modulate[3] = 255;

		if (p->roll)
		{
			VectorMA(point, 2 * height, ru, point);
		}
		else
		{
			VectorMA(point, 2 * height, vup, point);
		}
		VectorCopy(point, verts[1].xyz);
		verts[1].st[0]       = 0;
		verts[1].st[1]       = 1;
		verts[1].modulate[0] = 255;
		verts[1].modulate[1] = 255;
		verts[1].modulate[2] = 255;
		verts[1].modulate[3] = 255;

		if (p->roll)
		{
			VectorMA(point, 2 * width, rr, point);
		}
		else
		{
			VectorMA(point, 2 * width, vright, point);
		}
		VectorCopy(point, verts[2].xyz);
		verts[2].st[0]       = 1;
		verts[2].st[1]       = 1;
		verts[2].modulate[0] = 255;
		verts[2].modulate[1] = 255;
		verts[2].modulate[2] = 255;
		verts[2].modulate[3] = 255;

		if (p->roll)
		{
			VectorMA(point, -2 * height, ru, point);
		}
		else
		{
			VectorMA(point, -2 * height, vup, point);
		}
		VectorCopy(point, verts[3].xyz);
		verts[3].st[0]       = 1;
		verts[3].st[1]       = 0;
		verts[3].modulate[0] = 255;
		verts[3].modulate[1] = 255;
		verts[3].modulate[2] = 255;
		verts[3].modulate[3] = 255;
	}
	break;
	case P_SMOKE:
	case P_SMOKE_IMPACT: // create a front rotating facing polygon
	{
		vec3_t point, rup2, rright2, color;
		float  invratio, time, time2, ratio, width, height;

		if (p->type == P_SMOKE_IMPACT && VectorDistanceSquared(cg.snap->ps.origin, org) > Square(1024))
		{
			return;
		}

		if (p->color == MUSTARD)
		{
			VectorSet(color, 0.42f, 0.33f, 0.19f);
		}
		else if (p->color == BLOODRED)
		{
			VectorSet(color, 0.22f, 0, 0);
		}
		else if (p->color == ZOMBIE)
		{
			VectorSet(color, 0.4f, 0.28f, 0.23f);
		}
		else if (p->color == GREY75)
		{
			float len, greyit;

			len = Distance(cg.snap->ps.origin, org);
			if (len == 0.f)
			{
				len = 1;
			}

			//val    = 4096 / len;
			greyit = 0.25f * (4096 / len);
			if (greyit > 0.5f)
			{
				greyit = 0.5f;
			}

			VectorSet(color, greyit, greyit, greyit);
		}
		else
		{
			VectorSet(color, 1.0f, 1.0f, 1.0f);
		}

		time  = cg.time - p->time;
		time2 = p->endtime - p->time;
		ratio = time / time2;

		if (cg.time > p->startfade)
		{
			invratio = 1 - ((cg.time - p->startfade) / (p->endtime - p->startfade));

			if (p->color == EMISIVEFADE)
			{
				float fval = invratio * invratio;

				if (fval < 0)
				{
					fval = 0;
				}
				VectorSet(color, fval, fval, fval);
			}
			invratio *= p->alpha;
		}
		else
		{
			invratio = 1 * p->alpha;
		}

		if (invratio > 1)
		{
			invratio = 1;
		}

		width  = p->width + (ratio * (p->endwidth - p->width));
		height = p->height + (ratio * (p->endheight - p->height));

		//if (p->type != P_SMOKE_IMPACT)
		{
			vec3_t temp;

			vectoangles(rforward, temp);
			p->accumroll += p->roll;
			temp[ROLL]   += p->accumroll * 0.1;
			//temp[ROLL] += p->roll * 0.1;
			AngleVectors(temp, NULL, rright2, rup2);
		}
		//else
		//{
		//VectorCopy (rright, rright2);
		//VectorCopy (rup, rup2);
		//}

		if (p->rotate)
		{
			VectorMA(org, -height, rup2, point);
			VectorMA(point, -width, rright2, point);
		}
		else
		{
			VectorMA(org, -p->height, vup, point);
			VectorMA(point, -p->width, vright, point);
		}
		VectorCopy(point, verts[0].xyz);
		verts[0].st[0]       = 0;
		verts[0].st[1]       = 0;
		verts[0].modulate[0] = (byte)(255 * color[0]);
		verts[0].modulate[1] = (byte)(255 * color[1]);
		verts[0].modulate[2] = (byte)(255 * color[2]);
		verts[0].modulate[3] = (byte)(255 * invratio);

		if (p->rotate)
		{
			VectorMA(org, -height, rup2, point);
			VectorMA(point, width, rright2, point);
		}
		else
		{
			VectorMA(org, -p->height, vup, point);
			VectorMA(point, p->width, vright, point);
		}
		VectorCopy(point, verts[1].xyz);
		verts[1].st[0]       = 0;
		verts[1].st[1]       = 1;
		verts[1].modulate[0] = (byte)(255 * color[0]);
		verts[1].modulate[1] = (byte)(255 * color[1]);
		verts[1].modulate[2] = (byte)(255 * color[2]);
		verts[1].modulate[3] = (byte)(255 * invratio);

		if (p->rotate)
		{
			VectorMA(org, height, rup2, point);
			VectorMA(point, width, rright2, point);
		}
		else
		{
			VectorMA(org, p->height, vup, point);
			VectorMA(point, p->width, vright, point);
		}
		VectorCopy(point, verts[2].xyz);
		verts[2].st[0]       = 1;
		verts[2].st[1]       = 1;
		verts[2].modulate[0] = (byte)(255 * color[0]);
		verts[2].modulate[1] = (byte)(255 * color[1]);
		verts[2].modulate[2] = (byte)(255 * color[2]);
		verts[2].modulate[3] = (byte)(255 * invratio);

		if (p->rotate)
		{
			VectorMA(org, height, rup2, point);
			VectorMA(point, -width, rright2, point);
		}
		else
		{
			VectorMA(org, p->height, vup, point);
			VectorMA(point, -p->width, vright, point);
		}
		VectorCopy(point, verts[3].xyz);
		verts[3].st[0]       = 1;
		verts[3].st[1]       = 0;
		verts[3].modulate[0] = (byte)(255 * color[0]);
		verts[3].modulate[1] = (byte)(255 * color[1]);
		verts[3].modulate[2] = (byte)(255 * color[2]);
		verts[3].modulate[3] = (byte)(255 * invratio);

	}
	break;
	case P_BLEED:
	{
		vec3_t point, rr, ru, rotate_ang;
		float  alpha = p->alpha;

		if (p->roll)
		{
			vectoangles(cg.refdef_current->viewaxis[0], rotate_ang);
			rotate_ang[ROLL] += p->roll;
			AngleVectors(rotate_ang, NULL, rr, ru);
		}
		else
		{
			VectorCopy(vup, ru);
			VectorCopy(vright, rr);
		}

		VectorMA(org, -p->height, ru, point);
		VectorMA(point, -p->width, rr, point);
		VectorCopy(point, verts[0].xyz);
		verts[0].st[0]       = 0;
		verts[0].st[1]       = 0;
		verts[0].modulate[0] = 111;
		verts[0].modulate[1] = 19;
		verts[0].modulate[2] = 9;
		verts[0].modulate[3] = (byte)(255 * alpha);

		VectorMA(org, -p->height, ru, point);
		VectorMA(point, p->width, rr, point);
		VectorCopy(point, verts[1].xyz);
		verts[1].st[0]       = 0;
		verts[1].st[1]       = 1;
		verts[1].modulate[0] = 111;
		verts[1].modulate[1] = 19;
		verts[1].modulate[2] = 9;
		verts[1].modulate[3] = (byte)(255 * alpha);

		VectorMA(org, p->height, ru, point);
		VectorMA(point, p->width, rr, point);
		VectorCopy(point, verts[2].xyz);
		verts[2].st[0]       = 1;
		verts[2].st[1]       = 1;
		verts[2].modulate[0] = 111;
		verts[2].modulate[1] = 19;
		verts[2].modulate[2] = 9;
		verts[2].modulate[3] = (byte)(255 * alpha);

		VectorMA(org, p->height, ru, point);
		VectorMA(point, -p->width, rr, point);
		VectorCopy(point, verts[3].xyz);
		verts[3].st[0]       = 1;
		verts[3].st[1]       = 0;
		verts[3].modulate[0] = 111;
		verts[3].modulate[1] = 19;
		verts[3].modulate[2] = 9;
		verts[3].modulate[3] = (byte)(255 * alpha);
	}
	break;
	case P_FLAT_SCALEUP:
	{
		vec3_t color;
		float  width, height;
		float  sinR, cosR;
		float  time  = cg.time - p->time;
		float  time2 = p->endtime - p->time;
		float  ratio = time / time2;

		if (p->color == BLOODRED)
		{
			VectorSet(color, 1, 1, 1);
		}
		else
		{
			VectorSet(color, 0.5f, 0.5f, 0.5f);
		}

		width  = p->width + (ratio * (p->endwidth - p->width));
		height = p->height + (ratio * (p->endheight - p->height));

		if (width > p->endwidth)
		{
			width = p->endwidth;
		}

		if (height > p->endheight)
		{
			height = p->endheight;
		}

		sinR = height * (float)(sin(DEG2RAD(p->roll)) * M_SQRT2);
		cosR = width * (float)(cos(DEG2RAD(p->roll)) * M_SQRT2);

		VectorCopy(org, verts[0].xyz);
		verts[0].xyz[0]     -= sinR;
		verts[0].xyz[1]     -= cosR;
		verts[0].st[0]       = 0;
		verts[0].st[1]       = 0;
		verts[0].modulate[0] = (byte)(255 * color[0]);
		verts[0].modulate[1] = (byte)(255 * color[1]);
		verts[0].modulate[2] = (byte)(255 * color[2]);
		verts[0].modulate[3] = 255;

		VectorCopy(org, verts[1].xyz);
		verts[1].xyz[0]     -= cosR;
		verts[1].xyz[1]     += sinR;
		verts[1].st[0]       = 0;
		verts[1].st[1]       = 1;
		verts[1].modulate[0] = verts[0].modulate[0];
		verts[1].modulate[1] = verts[0].modulate[1];
		verts[1].modulate[2] = verts[0].modulate[2];
		verts[1].modulate[3] = verts[0].modulate[3];

		VectorCopy(org, verts[2].xyz);
		verts[2].xyz[0]     += sinR;
		verts[2].xyz[1]     += cosR;
		verts[2].st[0]       = 1;
		verts[2].st[1]       = 1;
		verts[2].modulate[0] = verts[0].modulate[0];
		verts[2].modulate[1] = verts[0].modulate[1];
		verts[2].modulate[2] = verts[0].modulate[2];
		verts[2].modulate[3] = verts[0].modulate[3];

		VectorCopy(org, verts[3].xyz);
		verts[3].xyz[0]     += cosR;
		verts[3].xyz[1]     -= sinR;
		verts[3].st[0]       = 1;
		verts[3].st[1]       = 0;
		verts[3].modulate[0] = verts[0].modulate[0];
		verts[3].modulate[1] = verts[0].modulate[1];
		verts[3].modulate[2] = verts[0].modulate[2];
		verts[3].modulate[3] = verts[0].modulate[3];
	}
	break;
	case P_FLAT:
	{
		VectorCopy(org, verts[0].xyz);
		verts[0].xyz[0]     -= p->height;
		verts[0].xyz[1]     -= p->width;
		verts[0].st[0]       = 0;
		verts[0].st[1]       = 0;
		verts[0].modulate[0] = 255;
		verts[0].modulate[1] = 255;
		verts[0].modulate[2] = 255;
		verts[0].modulate[3] = 255;

		VectorCopy(org, verts[1].xyz);
		verts[1].xyz[0]     -= p->height;
		verts[1].xyz[1]     += p->width;
		verts[1].st[0]       = 0;
		verts[1].st[1]       = 1;
		verts[1].modulate[0] = 255;
		verts[1].modulate[1] = 255;
		verts[1].modulate[2] = 255;
		verts[1].modulate[3] = 255;

		VectorCopy(org, verts[2].xyz);
		verts[2].xyz[0]     += p->height;
		verts[2].xyz[1]     += p->width;
		verts[2].st[0]       = 1;
		verts[2].st[1]       = 1;
		verts[2].modulate[0] = 255;
		verts[2].modulate[1] = 255;
		verts[2].modulate[2] = 255;
		verts[2].modulate[3] = 255;

		VectorCopy(org, verts[3].xyz);
		verts[3].xyz[0]     += p->height;
		verts[3].xyz[1]     -= p->width;
		verts[3].st[0]       = 1;
		verts[3].st[1]       = 0;
		verts[3].modulate[0] = 255;
		verts[3].modulate[1] = 255;
		verts[3].modulate[2] = 255;
		verts[3].modulate[3] = 255;
	}
	break;
	case P_ANIM:
	case P_DLIGHT_ANIM:
	{
		vec3_t point, rr, ru, rotate_ang;
		float  width, height;
		float  time = cg.time - p->time;
		float  time2 = p->endtime - p->time;
		float  ratio = time / time2;
		int    i, j;

		if (ratio >= 1)
		{
			ratio = 0.9999f;
		}
		else if (ratio < 0)
		{
			// make sure that ratio isn't negative or
			// we'll walk out of bounds when j is calculated below
			ratio = 0.0001f;
		}

		width  = p->width + (ratio * (p->endwidth - p->width));
		height = p->height + (ratio * (p->endheight - p->height));

		// add dlight if necessary
		if (p->type == P_DLIGHT_ANIM)
		{
			// fixme: support arbitrary color
			trap_R_AddLightToScene(org, 320,        //%	1.5 * (width > height ? width : height),
			                       1.25f * (1.0f - ratio), 1.0f, 0.95f, 0.85f, 0, 0);
		}

		// if we are "inside" this sprite, don't draw
		if (VectorDistanceSquared(cg.snap->ps.origin, org) < Square(width / 1.5f))
		{
			return;
		}

		i          = p->shaderAnim;
		j          = (int)floor((double)ratio * shaderAnimCounts[p->shaderAnim]);
		p->pshader = shaderAnims[i][j];

		if (p->roll)
		{
			vectoangles(cg.refdef_current->viewaxis[0], rotate_ang);
			rotate_ang[ROLL] += p->roll;
			AngleVectors(rotate_ang, NULL, rr, ru);
		}

		if (p->roll)
		{
			VectorMA(org, -height, ru, point);
			VectorMA(point, -width, rr, point);
		}
		else
		{
			VectorMA(org, -height, vup, point);
			VectorMA(point, -width, vright, point);
		}
		VectorCopy(point, verts[0].xyz);
		verts[0].st[0]       = 0;
		verts[0].st[1]       = 0;
		verts[0].modulate[0] = 255;
		verts[0].modulate[1] = 255;
		verts[0].modulate[2] = 255;
		verts[0].modulate[3] = 255;

		if (p->roll)
		{
			VectorMA(point, 2 * height, ru, point);
		}
		else
		{
			VectorMA(point, 2 * height, vup, point);
		}
		VectorCopy(point, verts[1].xyz);
		verts[1].st[0]       = 0;
		verts[1].st[1]       = 1;
		verts[1].modulate[0] = 255;
		verts[1].modulate[1] = 255;
		verts[1].modulate[2] = 255;
		verts[1].modulate[3] = 255;

		if (p->roll)
		{
			VectorMA(point, 2 * width, rr, point);
		}
		else
		{
			VectorMA(point, 2 * width, vright, point);
		}
		VectorCopy(point, verts[2].xyz);
		verts[2].st[0]       = 1;
		verts[2].st[1]       = 1;
		verts[2].modulate[0] = 255;
		verts[2].modulate[1] = 255;
		verts[2].modulate[2] = 255;
		verts[2].modulate[3] = 255;

		if (p->roll)
		{
			VectorMA(point, -2 * height, ru, point);
		}
		else
		{
			VectorMA(point, -2 * height, vup, point);
		}
		VectorCopy(point, verts[3].xyz);
		verts[3].st[0]       = 1;
		verts[3].st[1]       = 0;
		verts[3].modulate[0] = 255;
		verts[3].modulate[1] = 255;
		verts[3].modulate[2] = 255;
		verts[3].modulate[3] = 255;
	}
	break;
	default:
		break;
	}

	if (!cg_wolfparticles.integer)
	{
		return;
	}

	if (!p->pshader)
	{
		CG_Printf("CG_AddParticleToScene type %d p->pshader == ZERO\n", p->type);
		return;
	}

	if (p->type == P_WEATHER || p->type == P_WEATHER_TURBULENT || p->type == P_WEATHER_FLURRY)
	{
		trap_R_AddPolyToScene(p->pshader, 3, TRIverts);
	}
	else
	{
		trap_R_AddPolyToScene(p->pshader, 4, verts);
	}
}