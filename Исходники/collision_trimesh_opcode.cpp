void dxTriMeshData::Preprocess()
{

#if dTRIMESH_ENABLED

	// If this mesh has already been preprocessed, exit
	if (UseFlags)
		return;

	udword numTris = Mesh.GetNbTriangles();
	udword numEdges = numTris * 3;

	UseFlags = new uint8[numTris];
	memset(UseFlags, 0, sizeof(uint8) * numTris);

	EdgeRecord* records = new EdgeRecord[numEdges];

	// Make a list of every edge in the mesh
	const IndexedTriangle* tris = Mesh.GetTris();
	const unsigned tristride = Mesh.GetTriStride();
	for (unsigned int i = 0; i < numTris; i++)
	{
		SetupEdge(&records[i*3],   0, i, tris->mVRef);
		SetupEdge(&records[i*3+1], 1, i, tris->mVRef);
		SetupEdge(&records[i*3+2], 2, i, tris->mVRef);

		tris = (const IndexedTriangle*)(((uint8*)tris) + tristride);
	}

	// Sort the edges, so the ones sharing the same verts are beside each other
	qsort(records, numEdges, sizeof(EdgeRecord), EdgeCompare);

	// Go through the sorted list of edges and flag all the edges and vertices that we need to use
	for (unsigned int i = 0; i < numEdges; i++)
	{
		EdgeRecord* rec1 = &records[i];
		EdgeRecord* rec2 = 0;
		if (i < numEdges - 1)
			rec2 = &records[i+1];

		if (rec2 &&
			rec1->VertIdx1 == rec2->VertIdx1 &&
			rec1->VertIdx2 == rec2->VertIdx2)
		{
			VertexPointers vp;
			ConversionArea vc;
			Mesh.GetTriangle(vp, rec1->TriIdx, vc);

			// Get the normal of the first triangle
			Point triNorm = (*vp.Vertex[2] - *vp.Vertex[1]) ^ (*vp.Vertex[0] - *vp.Vertex[1]);
			triNorm.Normalize();

			// Get the vert opposite this edge in the first triangle
			Point oppositeVert1 = GetOppositeVert(rec1, vp.Vertex);

			// Get the vert opposite this edge in the second triangle
			Mesh.GetTriangle(vp, rec2->TriIdx, vc);
			Point oppositeVert2 = GetOppositeVert(rec2, vp.Vertex);

			float dot = triNorm.Dot((oppositeVert2 - oppositeVert1).Normalize());

			// We let the dot threshold for concavity get slightly negative to allow for rounding errors
			static const float kConcaveThresh = -0.000001f;

			// This is a concave edge, leave it for the next pass
			if (dot >= kConcaveThresh)
				rec1->Concave = true;
			// If this is a convex edge, mark its vertices and edge as used
			else
				UseFlags[rec1->TriIdx] |= rec1->Vert1Flags | rec1->Vert2Flags | rec1->EdgeFlags;

			// Skip the second edge
			i++;
		}
		// This is a boundary edge
		else
		{
			UseFlags[rec1->TriIdx] |= rec1->Vert1Flags | rec1->Vert2Flags | rec1->EdgeFlags;
		}
	}

	// Go through the list once more, and take any edge we marked as concave and
	// clear it's vertices flags in any triangles they're used in
	for (unsigned int i = 0; i < numEdges; i++)
	{
		EdgeRecord& er = records[i];

		if (er.Concave)
		{
			for (unsigned int j = 0; j < numEdges; j++)
			{
				EdgeRecord& curER = records[j];

				if (curER.VertIdx1 == er.VertIdx1 ||
					curER.VertIdx1 == er.VertIdx2)
					UseFlags[curER.TriIdx] &= ~curER.Vert1Flags;

				if (curER.VertIdx2 == er.VertIdx1 ||
					curER.VertIdx2 == er.VertIdx2)
					UseFlags[curER.TriIdx] &= ~curER.Vert2Flags;
			}
		}
	}

	delete [] records;

#endif // dTRIMESH_ENABLED

}