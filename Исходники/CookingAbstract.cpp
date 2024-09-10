void CookingAbstract::PhysicalMesh::computeTriangleAreas()
{
	smallestTriangleArea = largestTriangleArea = 0.0f;

	if (indices == NULL || vertices == NULL)
	{
		return;
	}

	smallestTriangleArea = PX_MAX_F32;

	for (PxU32 i = 0; i < numIndices; i += 3)
	{
		const PxVec3 edge1 = vertices[indices[i + 1]] - vertices[indices[i]];
		const PxVec3 edge2 = vertices[indices[i + 2]] - vertices[indices[i]];
		const PxF32 triangleArea = edge1.cross(edge2).magnitude();

		largestTriangleArea = PxMax(largestTriangleArea, triangleArea);
		smallestTriangleArea = PxMin(smallestTriangleArea, triangleArea);
	}
}