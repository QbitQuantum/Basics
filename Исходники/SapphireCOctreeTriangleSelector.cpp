	void COctreeTriangleSelector::getTrianglesFromOctree(
		SOctreeNode* node, SINT32& trianglesWritten,
		SINT32 maximumSize, const AxisAlignedBox& box,
		const Matrix4* mat, triangle3df* triangles) const
	{
		if (!box.intersects(node->Box))    //if (!box.intersectsWithBox(node->Box))
			return;

		const UINT32 cnt = node->Triangles.size();

		for (UINT32 i = 0; i<cnt; ++i)
		{
			const triangle3df& srcTri = node->Triangles[i];
			// This isn't an accurate test, but it's fast, and the 
			// API contract doesn't guarantee complete accuracy.
			if (srcTri.isTotalOutsideBox(box))
				continue;

			triangle3df& dstTri = triangles[trianglesWritten];
			//mat->transformVect(dstTri.pointA, srcTri.pointA
			//mat->transformVect(dstTri.pointB, srcTri.pointB);
			//mat->transformVect(dstTri.pointC, srcTri.pointC);
			dstTri.pointA = mat->transformAffine(srcTri.pointA);
			dstTri.pointB = mat->transformAffine(srcTri.pointB);
			dstTri.pointC = mat->transformAffine(srcTri.pointC);
			++trianglesWritten;

			// Halt when the out array is full.
			if (trianglesWritten == maximumSize)
				return;
		}

		for (UINT32 i = 0; i<8; ++i)
			if (node->Child[i])
				getTrianglesFromOctree(node->Child[i], trianglesWritten,
				maximumSize, box, mat, triangles);
	}