void CLevelGraph::draw_covers	()
{
	float					half_size = ai().level_graph().header().cell_size()*.5f;
	xr_vector<CCoverPoint*>	nearest;
	nearest.reserve			(1000);
	ai().cover_manager().covers().nearest(Device.vCameraPosition,5.f,nearest);
	xr_vector<CCoverPoint*>::const_iterator	I = nearest.begin();
	xr_vector<CCoverPoint*>::const_iterator	E = nearest.end();
	for ( ; I != E; ++I) {
		Fvector				position = (*I)->position();
		position.y			+= 1.f;
		Level().debug_renderer().draw_aabb	(position,half_size - .01f,1.f,ai().level_graph().header().cell_size()*.5f-.01f,D3DCOLOR_XRGB(0*255,255,0*255));

		CVertex				*v = vertex((*I)->level_vertex_id());
		Fvector				direction;
		float				best_value = -1.f;

		u32 i = 0, j = 0;
		for (; i<36; ++i) {
			float				value = cover_in_direction(float(10*i)/180.f*PI,v);
			direction.setHP		(float(10*i)/180.f*PI,0);
			direction.normalize	();
			direction.mul		(value*half_size);
			direction.add		(position);
			direction.y			= position.y;
			Level().debug_renderer().draw_line(Fidentity,position,direction,D3DCOLOR_XRGB(0,0,255));
			value				= compute_square(float(10*i)/180.f*PI,PI/2.f,v);
			if (value > best_value) {
				best_value		= value;
				j				= i;
			}
		}

		direction.set		(position.x - half_size*float(v->cover(0))/15.f,position.y,position.z);
		Level().debug_renderer().draw_line(Fidentity,position,direction,D3DCOLOR_XRGB(255,0,0));

		direction.set		(position.x,position.y,position.z + half_size*float(v->cover(1))/15.f);
		Level().debug_renderer().draw_line(Fidentity,position,direction,D3DCOLOR_XRGB(255,0,0));

		direction.set		(position.x + half_size*float(v->cover(2))/15.f,position.y,position.z);
		Level().debug_renderer().draw_line(Fidentity,position,direction,D3DCOLOR_XRGB(255,0,0));

		direction.set		(position.x,position.y,position.z - half_size*float(v->cover(3))/15.f);
		Level().debug_renderer().draw_line(Fidentity,position,direction,D3DCOLOR_XRGB(255,0,0));

		float				value = cover_in_direction(float(10*j)/180.f*PI,v);
		direction.setHP		(float(10*j)/180.f*PI,0);
		direction.normalize	();
		direction.mul		(value*half_size);
		direction.add		(position);
		direction.y			= position.y;
		Level().debug_renderer().draw_line	(Fidentity,position,direction,D3DCOLOR_XRGB(0,0,0));
	}
}