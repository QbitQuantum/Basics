	{
		memset(normals, 0, sizeof(PxVec3)*numVerts);
		
		const PxU32 numIndices = numFaces*3;

		// accumulate area weighted face normals in each vertex
		for (PxU32 t=0; t < numIndices; t+=3)
		{
			PxU16 i = faces[t];
			PxU16 j = faces[t+1];
			PxU16 k = faces[t+2];

			PxVec3 e1 = vertices[j]-vertices[i];
			PxVec3 e2 = vertices[k]-vertices[i];

			PxVec3 n = e2.cross(e1);

			normals[i] += n;
			normals[j] += n;
			normals[k] += n;
		}

		// average
		for (PxU32 i=0; i < numVerts; ++i)
			normals[i].normalize();
	}
}


void RenderClothActor::updateRenderShape()
{