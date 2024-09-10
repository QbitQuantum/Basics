neBool SearchResult::SearchEETri(s32 flag, s32 aIndex, s32 bIndex, neBool & assigned)
{
	assigned = false;

	gEdgeStack.Init();

	neByte edgeIndex;

	if (flag == 0) //fv
	{
		// face of convex A
		// vertex of triangle B
		for (s32 i = 0; i < objA.mesh.numNeighbour; i++) // for each edge neighbour of Face aIndex
		{
			int j = 0;

			while ((edgeIndex = objB.mesh.VertGetEdgeNeighbour(bIndex, j)) != 0xff)
			{
				gEdgeStack.Push(objA.mesh.FaceGetEdgeNeighbour(aIndex, i),
								objB.mesh.VertGetEdgeNeighbour(bIndex, j));
				
				j++;
			}
		}
	}
	else //vf
	{
		//vertex of convex A
		//face of triangle B
		s32 i = 0;

		//for each edge neighbour incident to Vertex aIndex
		
		while ((edgeIndex = objA.mesh.VertGetEdgeNeighbour(aIndex, i)) != 0xff)
		{
			for (s32 j = 0; j < objB.mesh.numNeighbour; j++)
			{
				gEdgeStack.Push(objA.mesh.VertGetEdgeNeighbour(aIndex, i),
								objB.mesh.FaceGetEdgeNeighbour(bIndex, j));
			}			
			i++;
		}
	}
	while (!gEdgeStack.IsEmpty())
	{
		_num_edge_test++;

		s32 edgeP, edgeQ;

		gEdgeStack.Pop(edgeP, edgeQ);

		// does the edge form a face
		neV3 a = objA.GetWorldNormalByEdge1(edgeP);

		neV3 b = objA.GetWorldNormalByEdge2(edgeP);

		neV3 c = objB.GetWorldNormalByEdge1(edgeQ) * -1.0f;

		neV3 d = objB.GetWorldNormalByEdge2(edgeQ) * -1.0f;

		c += (TriEdgeDir[edgeQ] * 0.01f);

		d += (TriEdgeDir[edgeQ] * 0.01f);

		c.Normalize();

		d.Normalize();

		f32 cba = Determinant(c,b,a);

		f32 dba = Determinant(d,b,a);

		f32 prod0 = cba * dba;

		if (prod0 >= -1.0e-6f)
		{
			continue;
		}

		f32 adc = Determinant(a,d,c);

		f32 bdc = Determinant(b,d,c);

		f32 prod1 = adc * bdc;

		if (prod1 >= -1.0e-6f)
		{
			continue;
		}
		f32 prod2 = cba * bdc;

		if (prod2 <= 1.0e-6f)
		{
			continue;
		}


		neV3 ai, bi;
		neV3 naj, nbj;

		objA.GetWorldEdgeVerts(edgeP, ai, bi);

		objB.GetWorldEdgeVerts(edgeQ, naj, nbj);
		
		naj *= -1.0f; nbj *= -1.0f;

		neV3 ainaj = ai + naj;
		neV3 ainbj = ai + nbj;
		neV3 binaj = bi + naj;
		//neV3 binbj = bi + nbj;

		neV3 diff1 = ainaj - ainbj;
		neV3 diff2 = ainaj - binaj ;

		Face testFace;

		testFace.normal = diff1.Cross(diff2);

		f32 len = testFace.normal.Length();

		if (neIsConsiderZero(len))
		{
			continue;
		}
		testFace.normal *= (1.0f / len);

		testFace.k = testFace.normal.Dot(ainaj);

		f32 testD = funcD(testFace);

		if (testD >= 0)
			return false;

		if (testD <= dMax)
			continue;

		assigned = true;
		dMax = testD;
		face = testFace;
		indexA = edgeP;
		indexB = edgeQ;
		typeA = SearchResult::EDGE; 
		typeB = SearchResult::EDGE;

		// push
		s32 i, j;

		s32 vindex;

		vindex = objB.mesh.EdgeGetVert1(edgeQ);

		i = 0;

		while ((j = objB.mesh.VertGetEdgeNeighbour(vindex, i)) != 0xff)
		{
			if (j != edgeQ)
				gEdgeStack.Push(edgeP, j);

			i++;
		}

		vindex = objB.mesh.EdgeGetVert2(edgeQ);

		i = 0;

		while ((j = objB.mesh.VertGetEdgeNeighbour(vindex, i)) != 0xff)
		{
			if (j != edgeQ)
				gEdgeStack.Push(edgeP, j);

			i++;
		}

		vindex = objA.mesh.EdgeGetVert1(edgeP);

		i = 0;
		
		while((j = objA.mesh.VertGetEdgeNeighbour(vindex, i)) != 0xff)
		{
			if (j != edgeP)
				gEdgeStack.Push(j, edgeQ);

			i++;
		}

		vindex = objA.mesh.EdgeGetVert2(edgeP);

		//for (i = 0; i < objA.mesh.VertGetNumEdgeNeighbour(vindex); i++)
		i = 0;

		while ((j = objA.mesh.VertGetEdgeNeighbour(vindex, i)) != 0xff)
		{
			if (j != edgeP)
				gEdgeStack.Push(j, edgeQ);

			i++;
		}
	}
	return true;
}