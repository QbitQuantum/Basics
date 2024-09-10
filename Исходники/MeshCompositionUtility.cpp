/**
 @brief vector 4개로 triangle 2개를 그리는 index buffer를 생성한다.
 @date 2014-01-30
*/
void SampleRenderer::GenerateTriangleFrom4Vector2( void *positions, void *normals, void *bones, void *colors, 
	PxU32 stride, PxU32 startVtxIdx, PxU16 *indices, PxU32 startIndexIdx, const PxVec3 &center, 
	const vector<PxU16> &faceIndices, OUT vector<PxU16> &outfaceIndices )
{
	vector<PxU16> triangle0; triangle0.reserve(3);
	vector<PxU16> triangle1; triangle1.reserve(3);
	triangle0.push_back( faceIndices[ 0] );
	triangle0.push_back( faceIndices[ 2] );
	triangle0.push_back( faceIndices[ 3] );

	triangle1.push_back( faceIndices[ 0] );
	triangle1.push_back( faceIndices[ 1] );
	triangle1.push_back( faceIndices[ 3] );

	GenerateTriangleFrom3Vector(positions, normals, stride, center, triangle0, outfaceIndices);
	GenerateTriangleFrom3Vector(positions, normals, stride, center, triangle1, outfaceIndices);

	if (outfaceIndices.size() != 6)
		return; // error occur
	
	for (u_int i=0; i < outfaceIndices.size();)
	{
		const PxVec3 p0 = *(PxVec3*)(((PxU8*)positions) + (stride * outfaceIndices[ i]));
		const PxVec3 p1 = *(PxVec3*)(((PxU8*)positions) + (stride * outfaceIndices[ i+1]));
		const PxVec3 p2 = *(PxVec3*)(((PxU8*)positions) + (stride * outfaceIndices[ i+2]));

		*(PxVec3*)(((PxU8*)positions) + (stride * startVtxIdx)) = p0;
		*(PxVec3*)(((PxU8*)positions) + (stride * (startVtxIdx+1))) = p1;
		*(PxVec3*)(((PxU8*)positions) + (stride * (startVtxIdx+2))) = p2;

		if (bones)
		{
			const PxU32 b0 = *(PxU32*)(((PxU8*)bones) + (stride * outfaceIndices[ i]));
			const PxU32 b1 = *(PxU32*)(((PxU8*)bones) + (stride * outfaceIndices[ i+1]));
			const PxU32 b2 = *(PxU32*)(((PxU8*)bones) + (stride * outfaceIndices[ i+2]));

			*(PxU32*)(((PxU8*)bones) + (stride * startVtxIdx)) = b0;
			*(PxU32*)(((PxU8*)bones) + (stride * (startVtxIdx+1))) = b1;
			*(PxU32*)(((PxU8*)bones) + (stride * (startVtxIdx+2))) = b2;
		}

		if (colors)
		{
			const PxU32 c0 = *(PxU32*)(((PxU8*)colors) + (stride * outfaceIndices[ i]));
			const PxU32 c1 = *(PxU32*)(((PxU8*)colors) + (stride * outfaceIndices[ i+1]));
			const PxU32 c2 = *(PxU32*)(((PxU8*)colors) + (stride * outfaceIndices[ i+2]));

			*(PxU32*)(((PxU8*)colors) + (stride * startVtxIdx)) = c0;
			*(PxU32*)(((PxU8*)colors) + (stride * (startVtxIdx+1))) = c1;
			*(PxU32*)(((PxU8*)colors) + (stride * (startVtxIdx+2))) = c2;
		}

		if (normals)
		{
			PxVec3 v01 = p1 - p0;
			PxVec3 v02 = p2 - p0;
			v01.normalize();
			v02.normalize();
			PxVec3 n = v01.cross(v02);
			n.normalize();
			n = -n;

			*(PxVec3*)(((PxU8*)normals) + (stride * startVtxIdx)) = n;
			*(PxVec3*)(((PxU8*)normals) + (stride * (startVtxIdx+1))) = n;
			*(PxVec3*)(((PxU8*)normals) + (stride * (startVtxIdx+2))) = n;
		}		

		indices[ startIndexIdx] = startVtxIdx;
		indices[ startIndexIdx+1] = startVtxIdx+1;
		indices[ startIndexIdx+2] = startVtxIdx+2;

		startIndexIdx += 3;
		startVtxIdx += 3;
		i += 3;
	}
}