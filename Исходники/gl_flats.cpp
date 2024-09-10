void GLFlat::ProcessSector(sector_t * frontsector)
{
	lightlist_t * light;

#ifdef _DEBUG
	if (frontsector->sectornum==gl_breaksec)
	{
		int a = 0;
	}
#endif

	// Get the real sector for this one.
	sector=&sectors[frontsector->sectornum];	
	extsector_t::xfloor &x = sector->e->XFloor;
	this->sub=NULL;
	dynlightindex = -1;

	byte &srf = gl_drawinfo->sectorrenderflags[sector->sectornum];

	//
	//
	//
	// do floors
	//
	//
	//
	if (frontsector->floorplane.ZatPoint(FIXED2FLOAT(viewx), FIXED2FLOAT(viewy)) <= FIXED2FLOAT(viewz))
	{
		// process the original floor first.

		srf |= SSRF_RENDERFLOOR;

		lightlevel = gl_ClampLight(frontsector->GetFloorLight());
		Colormap=frontsector->ColorMap;
		if ((stack = (frontsector->portals[sector_t::floor] != NULL)))
		{
			gl_drawinfo->AddFloorStack(sector);
			alpha = frontsector->GetAlpha(sector_t::floor)/65536.0f;
		}
		else
		{
			alpha = 1.0f-frontsector->GetReflect(sector_t::floor);
		}
		if (frontsector->VBOHeightcheck(sector_t::floor))
		{
			vboindex = frontsector->vboindex[sector_t::floor];
		}
		else
		{
			vboindex = -1;
		}

		ceiling=false;
		renderflags=SSRF_RENDERFLOOR;

		if (x.ffloors.Size())
		{
			light = P_GetPlaneLight(sector, &frontsector->floorplane, false);
			if ((!(sector->GetFlags(sector_t::floor)&PLANEF_ABSLIGHTING) || !light->fromsector)	
				&& (light->p_lightlevel != &frontsector->lightlevel))
			{
				lightlevel = *light->p_lightlevel;
			}

			Colormap.CopyLightColor(light->extra_colormap);
		}
		renderstyle = STYLE_Translucent;
		if (alpha!=0.0f) Process(frontsector, false, false);
	}
	
	//
	//
	//
	// do ceilings
	//
	//
	//
	if (frontsector->ceilingplane.ZatPoint(FIXED2FLOAT(viewx), FIXED2FLOAT(viewy)) >= FIXED2FLOAT(viewz))
	{
		// process the original ceiling first.

		srf |= SSRF_RENDERCEILING;

		lightlevel = gl_ClampLight(frontsector->GetCeilingLight());
		Colormap=frontsector->ColorMap;
		if ((stack = (frontsector->portals[sector_t::ceiling] != NULL))) 
		{
			gl_drawinfo->AddCeilingStack(sector);
			alpha = frontsector->GetAlpha(sector_t::ceiling)/65536.0f;
		}
		else
		{
			alpha = 1.0f-frontsector->GetReflect(sector_t::ceiling);
		}

		if (frontsector->VBOHeightcheck(sector_t::ceiling))
		{
			vboindex = frontsector->vboindex[sector_t::ceiling];
		}
		else
		{
			vboindex = -1;
		}

		ceiling=true;
		renderflags=SSRF_RENDERCEILING;

		if (x.ffloors.Size())
		{
			light = P_GetPlaneLight(sector, &sector->ceilingplane, true);

			if ((!(sector->GetFlags(sector_t::ceiling)&PLANEF_ABSLIGHTING))
				&& (light->p_lightlevel != &frontsector->lightlevel))
			{
				lightlevel = *light->p_lightlevel;
			}
			Colormap.CopyLightColor(light->extra_colormap);
		}
		renderstyle = STYLE_Translucent;
		if (alpha!=0.0f) Process(frontsector, true, false);
	}

	//
	//
	//
	// do 3D floors
	//
	//
	//

	stack=false;
	if (x.ffloors.Size())
	{
		player_t * player=players[consoleplayer].camera->player;

		renderflags=SSRF_RENDER3DPLANES;
		srf |= SSRF_RENDER3DPLANES;
		// 3d-floors must not overlap!
		fixed_t lastceilingheight=sector->CenterCeiling();	// render only in the range of the
		fixed_t lastfloorheight=sector->CenterFloor();		// current sector part (if applicable)
		F3DFloor * rover;	
		int k;
		
		// floors are ordered now top to bottom so scanning the list for the best match
		// is no longer necessary.

		ceiling=true;
		for(k=0;k<(int)x.ffloors.Size();k++)
		{
			rover=x.ffloors[k];
			
			if ((rover->flags&(FF_EXISTS|FF_RENDERPLANES|FF_THISINSIDE))==(FF_EXISTS|FF_RENDERPLANES))
			{
				if (rover->flags&FF_FOG && gl_fixedcolormap) continue;
				if (!rover->top.copied && rover->flags&(FF_INVERTPLANES|FF_BOTHPLANES))
				{
					fixed_t ff_top=rover->top.plane->ZatPoint(CenterSpot(sector));
					if (ff_top<lastceilingheight)
					{
						if (FIXED2FLOAT(viewz) <= rover->top.plane->ZatPoint(FIXED2FLOAT(viewx), FIXED2FLOAT(viewy)))
						{
							SetFrom3DFloor(rover, true, !!(rover->flags&FF_FOG));
							Colormap.FadeColor=frontsector->ColorMap->Fade;
							Process(rover->top.model, rover->top.isceiling, !!(rover->flags&FF_FOG));
						}
						lastceilingheight=ff_top;
					}
				}
				if (!rover->bottom.copied && !(rover->flags&FF_INVERTPLANES))
				{
					fixed_t ff_bottom=rover->bottom.plane->ZatPoint(CenterSpot(sector));
					if (ff_bottom<lastceilingheight)
					{
						if (FIXED2FLOAT(viewz)<=rover->bottom.plane->ZatPoint(FIXED2FLOAT(viewx), FIXED2FLOAT(viewy)))
						{
							SetFrom3DFloor(rover, false, !(rover->flags&FF_FOG));
							Colormap.FadeColor=frontsector->ColorMap->Fade;
							Process(rover->bottom.model, rover->bottom.isceiling, !!(rover->flags&FF_FOG));
						}
						lastceilingheight=ff_bottom;
						if (rover->alpha<255) lastceilingheight++;
					}
				}
			}
		}
			  
		ceiling=false;
		for(k=x.ffloors.Size()-1;k>=0;k--)
		{
			rover=x.ffloors[k];
			
			if ((rover->flags&(FF_EXISTS|FF_RENDERPLANES|FF_THISINSIDE))==(FF_EXISTS|FF_RENDERPLANES))
			{
				if (rover->flags&FF_FOG && gl_fixedcolormap) continue;
				if (!rover->bottom.copied && rover->flags&(FF_INVERTPLANES|FF_BOTHPLANES))
				{
					fixed_t ff_bottom=rover->bottom.plane->ZatPoint(CenterSpot(sector));
					if (ff_bottom>lastfloorheight || (rover->flags&FF_FIX))
					{
						if (FIXED2FLOAT(viewz) >= rover->bottom.plane->ZatPoint(FIXED2FLOAT(viewx), FIXED2FLOAT(viewy)))
						{
							SetFrom3DFloor(rover, false, !(rover->flags&FF_FOG));
							Colormap.FadeColor=frontsector->ColorMap->Fade;

							if (rover->flags&FF_FIX)
							{
								lightlevel = gl_ClampLight(rover->model->lightlevel);
								Colormap = rover->GetColormap();
							}

							Process(rover->bottom.model, rover->bottom.isceiling, !!(rover->flags&FF_FOG));
						}
						lastfloorheight=ff_bottom;
					}
				}
				if (!rover->top.copied && !(rover->flags&FF_INVERTPLANES))
				{
					fixed_t ff_top=rover->top.plane->ZatPoint(CenterSpot(sector));
					if (ff_top>lastfloorheight)
					{
						if (FIXED2FLOAT(viewz) >= rover->top.plane->ZatPoint(FIXED2FLOAT(viewx), FIXED2FLOAT(viewy)))
						{
							SetFrom3DFloor(rover, true, !!(rover->flags&FF_FOG));
							Colormap.FadeColor=frontsector->ColorMap->Fade;
							Process(rover->top.model, rover->top.isceiling, !!(rover->flags&FF_FOG));
						}
						lastfloorheight=ff_top;
						if (rover->alpha<255) lastfloorheight--;
					}
				}
			}
		}
	}
}