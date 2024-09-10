/**
 @brief 
 @date 2014-01-04
*/
void RendererCompositionShape::GenerateTriangleFrom4Vector( void *positions, PxU32 positionStride, 
	void *normals, PxU32 normalStride, PxU32 startVtxIdx, PxU16 *indices, PxU32 startIndexIdx,
	const PxVec3 &center, PxVec3 v0, PxVec3 v1, PxVec3 v2, PxVec3 v3 )
{
	// test cw
	{
		PxVec3 n0 = v2 - v0;
		n0.normalize();
		PxVec3 n1 = v3 - v0;
		n1.normalize();
		PxVec3 n = n0.cross(n1);
		n.normalize();

		PxVec3 faceCenter = v0 + v2 + v3;
		faceCenter /= 3.f;
		PxVec3 cn = center - faceCenter;
		cn.normalize();
		const float d = n.dot(cn);
		if (d >= 0)
		{ // cw
		}
		else
		{ // ccw
			// switching
			PxVec3 tmp = v3;
			v3 = v2;
			v2 = tmp;
		}
	}

	// triangle 1
	{
		PxU32 face1VtxIdx = startVtxIdx;

		PxVec3 n0 = v1 - v0;
		n0.normalize();
		PxVec3 n1 = v2 - v0;
		n1.normalize();
		PxVec3 n = n0.cross(n1);
		n.normalize();
		PxVec3 faceCenter = v0 + v1 + v2;
		faceCenter /= 3.f;
		PxVec3 cn = center - faceCenter;
		cn.normalize();

		const float d = n.dot(cn);
		if (d >= 0)
		{ // cw
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v0;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v1;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v2;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * face1VtxIdx)) = -n;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * (face1VtxIdx+1))) = -n;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * (face1VtxIdx+2))) = -n;
		}
		else
		{ // ccw
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v0;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v2;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v1;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * face1VtxIdx)) = n;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * (face1VtxIdx+1))) = n;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * (face1VtxIdx+2))) = n;
		}

		indices[ startIndexIdx++] = face1VtxIdx;
		indices[ startIndexIdx++] = face1VtxIdx+1;
		indices[ startIndexIdx++] = face1VtxIdx+2;
	}


	// triangle2
	{
		PxU32 face2VtxIdx = startVtxIdx;

		PxVec3 n0 = v2 - v0;
		n0.normalize();
		PxVec3 n1 = v3 - v0;
		n1.normalize();
		PxVec3 n = n0.cross(n1);
		n.normalize();
		PxVec3 faceCenter = v0 + v2 + v3;
		faceCenter /= 3.f;
		PxVec3 cn = center - faceCenter;
		cn.normalize();

		const float d = n.dot(cn);
		if (d >= 0)
		{ // cw
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v0;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v2;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v3;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * face2VtxIdx)) = -n;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * (face2VtxIdx+1))) = -n;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * (face2VtxIdx+2))) = -n;
		}
		else
		{ // ccw
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v0;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v3;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx++)) = v2;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * face2VtxIdx)) = n;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * (face2VtxIdx+1))) = n;
			*(PxVec3*)(((PxU8*)normals) + (normalStride * (face2VtxIdx+2))) = n;
		}

		indices[ startIndexIdx++] = face2VtxIdx;
		indices[ startIndexIdx++] = face2VtxIdx+1;
		indices[ startIndexIdx++] = face2VtxIdx+2;
	}
}