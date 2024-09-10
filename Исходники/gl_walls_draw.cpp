void GLWall::SetupLights()
{
	// check for wall types which cannot have dynamic lights on them (portal types never get here so they don't need to be checked.)
	switch (type)
	{
	case RENDERWALL_FOGBOUNDARY:
	case RENDERWALL_MIRRORSURFACE:
	case RENDERWALL_COLOR:
	case RENDERWALL_COLORLAYER:
		return;
	}

	float vtx[]={glseg.x1,zbottom[0],glseg.y1, glseg.x1,ztop[0],glseg.y1, glseg.x2,ztop[1],glseg.y2, glseg.x2,zbottom[1],glseg.y2};
	Plane p;

	lightdata.Clear();
	p.Init(vtx,4);

	if (!p.ValidNormal()) 
	{
		return;
	}
	FLightNode *node;
	if (seg->sidedef == NULL)
	{
		node = NULL;
	}
	else if (!(seg->sidedef->Flags & WALLF_POLYOBJ))
	{
		node = seg->sidedef->lighthead;
	}
	else if (sub)
	{
		// Polobject segs cannot be checked per sidedef so use the subsector instead.
		node = sub->lighthead;
	}
	else node = NULL;

	// Iterate through all dynamic lights which touch this wall and render them
	while (node)
	{
		if (!(node->lightsource->flags2&MF2_DORMANT))
		{
			iter_dlight++;

			Vector fn, pos;

			float x = FIXED2FLOAT(node->lightsource->X());
			float y = FIXED2FLOAT(node->lightsource->Y());
			float z = FIXED2FLOAT(node->lightsource->Z());
			float dist = fabsf(p.DistToPoint(x, z, y));
			float radius = (node->lightsource->GetRadius() * gl_lights_size);
			float scale = 1.0f / ((2.f * radius) - dist);

			if (radius > 0.f && dist < radius)
			{
				Vector nearPt, up, right;

				pos.Set(x,z,y);
				fn=p.Normal();
				fn.GetRightUp(right, up);

				Vector tmpVec = fn * dist;
				nearPt = pos + tmpVec;

				Vector t1;
				int outcnt[4]={0,0,0,0};
				texcoord tcs[4];

				// do a quick check whether the light touches this polygon
				for(int i=0;i<4;i++)
				{
					t1.Set(&vtx[i*3]);
					Vector nearToVert = t1 - nearPt;
					tcs[i].u = (nearToVert.Dot(right) * scale) + 0.5f;
					tcs[i].v = (nearToVert.Dot(up) * scale) + 0.5f;

					if (tcs[i].u<0) outcnt[0]++;
					if (tcs[i].u>1) outcnt[1]++;
					if (tcs[i].v<0) outcnt[2]++;
					if (tcs[i].v>1) outcnt[3]++;

				}
				if (outcnt[0]!=4 && outcnt[1]!=4 && outcnt[2]!=4 && outcnt[3]!=4) 
				{
					gl_GetLight(p, node->lightsource, true, false, lightdata);
				}
			}
		}
		node = node->nextLight;
	}

	dynlightindex = GLRenderer->mLights->UploadLights(lightdata);
}