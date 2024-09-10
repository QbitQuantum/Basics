bool TryToQuadify(EERIEPOLY * ep,EERIE_3DOBJ * eobj) {
	
	const float tolerance = 0.1f;
	
	float centerx = (ep->v[0].p.x + ep->v[1].p.x + ep->v[2].p.x) * (1.f/3);
	float centerz = (ep->v[0].p.z + ep->v[1].p.z + ep->v[2].p.z) * (1.f/3);
	
	short tilex = centerx * ACTIVEBKG->Xmul;
	short tilez = centerz * ACTIVEBKG->Zmul;
	short radius = 1;
	
	short minx = std::max(tilex - radius, 0);
	short maxx = std::min(tilex + radius, ACTIVEBKG->Xsize - 1);
	short minz = std::max(tilez - radius, 0);
	short maxz = std::min(tilez + radius, ACTIVEBKG->Zsize - 1);
	
	for(long kl = 0; kl < 2; kl++)
	for(short z = minz; z <= maxz; z++)
	for(short x = minx; x <= maxx; x++) {
		EERIE_BKG_INFO *eg = &ACTIVEBKG->fastdata[x][z];
		
		long val1 = 0;

		long type, val2;
		if(!GetNameInfo(eobj->name, type, val1, val2))
			return false;

		if(type != TYPE_ROOM)
			return false;

		if(eg)
		for(long n = 0; n < eg->nbpoly; n++) {
			EERIEPOLY *ep2 = (EERIEPOLY *)&eg->polydata[n];

			if(ep2->room != val1)
				continue;

			if(ep == ep2)
				continue;

			if(kl == 0 && (ep2->type & POLY_QUAD)) {
				if(Quadable(ep, ep2, tolerance))
					return true;
			} else if(kl == 1 && !(ep2->type & POLY_QUAD)) {
				if(Quadable(ep, ep2, tolerance))
					return true;
			}
		}
	}

	return false;
}