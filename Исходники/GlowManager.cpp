void CGlowManager::render_selected()
{
	// 2. Sort by shader
	std::sort		(Selected.begin(),Selected.end(),glow_compare);

	FVF::LIT		*pv;

	u32				pos = 0, count;
	ref_shader		T;

	Fplane			NP;
	NP.build		(Device.vCameraPosition,Device.vCameraDirection);

	float		dlim2	= MAX_GlowsDist2;
	for (;pos<Selected.size();) 
	{
		T		= ((CGlow*)Selected[pos]._get())->shader;
		count	= 0;
		while	((pos+count<Selected.size()) && (((CGlow*)Selected[pos+count]._get())->shader==T)) count++;

		u32		vOffset;
		u32		end		= pos+count;
		FVF::LIT* pvs	= pv = (FVF::LIT*) RCache.Vertex.Lock(count*4,hGeom->vb_stride,vOffset);
		for (; pos<end; pos++)
		{
			// Cull invisible 
			CGlow&	G					= *( (CGlow*)Selected[pos]._get() );
			if (G.fade<=1.f)			continue;

			// Now perform dotproduct if need it
			float	scale	= 1.f, dist_sq;
			Fvector	dir;
			dir.sub			(Device.vCameraPosition,G.position);
			dist_sq			= dir.square_magnitude();
			if (G.direction.square_magnitude()>EPS)	{
				dir.div			(_sqrt(dist_sq));
				scale			= dir.dotproduct(G.direction);
			}
			if (G.fade*scale<=1.f)		continue;

			// near fade
			float dist_np	= NP.distance(G.position)-VIEWPORT_NEAR;
			float snear		= dist_np/0.15f;	clamp	(snear,0.f,1.f);
			scale			*=	snear;
			if (G.fade*scale<=1.f)		continue;

			u32 C			= iFloor(G.fade*scale*(1-(dist_sq/dlim2)));
			u32 clr			= color_rgba(C,C,C,C);
			Fvector	gp		;
					gp.mad	(G.position,dir,G.radius*scale);
			FillSprite		(pv,G.position,G.radius,clr);
		}
		int vCount				= int(pv-pvs);
		RCache.Vertex.Unlock	(vCount,hGeom->vb_stride);
		if (vCount) {
			RCache.set_Shader		(T);
			RCache.set_Geometry		(hGeom);
			RCache.Render			(D3DPT_TRIANGLELIST,vOffset,0,vCount,0,vCount/2);
		}
	}
	Selected.clear_not_free			();
}