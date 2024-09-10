void ResetVert (PatchMesh *patch)
{
	// Make a edge table
	// Static table to avoid alloc prb
	CVertexNeighborhood& edgeTab=vertexNeighborhoodGlobal;
	edgeTab.build (*patch);

	// For each vertices
	for (int nV=0; nV<patch->numVerts; nV++)
	{
		// Selected ?
		if (patch->vertSel[nV])
		{
			Point3 vert=patch->verts[nV].p;
			Point3 normal (0,0,0);

			// Count of neigbor for vertex n
			uint listSize=edgeTab.getNeighborCount (nV);

			// List of neigbor
			const uint* pList=edgeTab.getNeighborList (nV);

			// For each neigbor
			uint nn;
			for (nn=0; nn<listSize; nn++)
			{
#if (MAX_RELEASE < 4000)
				// Compute average plane
				if (patch->edges[pList[nn]].patch1!=-1)
					normal+=patch->PatchNormal(patch->edges[pList[nn]].patch1);
				if (patch->edges[pList[nn]].patch2!=-1)
					normal+=patch->PatchNormal(patch->edges[pList[nn]].patch2);
#else // (MAX_RELEASE <= 4000)
				// Compute average plane
				if (patch->edges[pList[nn]].patches[0]!=-1)
					normal+=patch->PatchNormal(patch->edges[pList[nn]].patches[0]);
				if (patch->edges[pList[nn]].patches[1]!=-1)
					normal+=patch->PatchNormal(patch->edges[pList[nn]].patches[1]);
#endif // (MAX_RELEASE <= 4000)
			}
			
			// Normalize
			normal=normal.Normalize();
			
			// Plane
			float fD=-DotProd(normal, vert);

			// Reset normales
			float fNorme=0.f;

			// For each neigbor
			for (nn=0; nn<listSize; nn++)
			{
				Point3 vect2=patch->verts[(patch->edges[pList[nn]].v1==nV)?patch->edges[pList[nn]].v2:patch->edges[pList[nn]].v1].p;
				vect2-=vert;
				vect2/=3.f;
				Point3 tmp1=CrossProd (vect2, normal);
				tmp1=CrossProd (normal, tmp1);
				tmp1=Normalize(tmp1);
				int nTang=(patch->edges[pList[nn]].v1==nV)?patch->edges[pList[nn]].vec12:patch->edges[pList[nn]].vec21;
				patch->vecs[nTang].p=vert+tmp1*DotProd (tmp1,vect2);
				tmp1=patch->vecs[nTang].p;
				tmp1-=vert;
				fNorme+=tmp1.Length();
			}

			// Renorme new normal
			/*fNorme/=(float)edgeTab[nV].size();
			ite=edgeTab[nV].begin();
			while (ite!=edgeTab[nV].end())
			{
				int nTang=(patch->edges[pList[nn]].v1==nV)?patch->edges[pList[nn]].vec12:patch->edges[pList[nn]].vec21;
				patch->vecs[nTang].p=fNorme*(Normalize(patch->vecs[nTang].p-vert))+vert;

				ite++;
			}*/
		}
	}
	patch->computeInteriors();
	patch->InvalidateGeomCache ();
}