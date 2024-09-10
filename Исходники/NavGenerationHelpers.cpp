	bool CreateGeometryFromPhysxGeometry(PxTriangleMeshGeometry &g, const PxTransform &globalPose, LevelGeometry::Mesh &mesh)
	{
		PxTriangleMesh *tm = g.triangleMesh;

		const PxU32 nbVerts = tm->getNbVertices();
		const PxVec3* verts = tm->getVertices();
		PxU32 nbTris = tm->getNbTriangles();
		const void* typelessTris = tm->getTriangles();

		PxU32 numIndices = nbTris * 3;
		mesh.indices.Resize(numIndices);

		if (tm->has16BitTriangleIndices())
		{
			//	Convert indices to 32 bit
			const short *i16 = reinterpret_cast<const short*>(typelessTris);

			for (PxU32 i = 0; i < numIndices; ++i)
			{
				mesh.indices[i] = i16[i];
			}
		}
		else
		{
			int size = numIndices * sizeof(mesh.indices[0]);
			memcpy_s(&mesh.indices[0], size, typelessTris, size);
		}

		//	Transform vertices to world space
		mesh.vertices.Resize(nbVerts);
		for (PxU32 i = 0; i < nbVerts; ++i)
		{
			PxVec3 pos = globalPose.transform(verts[i]);
			mesh.vertices[i].Assign(pos.x, pos.y, pos.z);
		}

		//	Reject out-of-regions triangles
		numIndices = gConvexRegionsManager.FilterOutsideTriangles(&mesh.vertices[0], &mesh.indices[0], numIndices);
		r3d_assert(numIndices % 3 == 0);

		mesh.indices.Resize(numIndices);

		return true;
	}