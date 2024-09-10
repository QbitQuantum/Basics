// AP: function version to reduce SPU code size
void sweepCapsuleTrianglesOutputTri2(
	const PxVec3& p0, const PxVec3& p1, const PxVec3& p2, const PxVec3& d, PxTriangle* extrudedTris,
	PxU32& nbExtrudedTris, PxVec3* extrudedTrisNormals
	)
{
	PxTriangle& t = extrudedTris[nbExtrudedTris];
	t.verts[0] = p0;
	t.verts[1] = p1;
	t.verts[2] = p2;
	PxVec3 nrm;
	t.denormalizedNormal(nrm);
	if(nrm.dot(d)>0.0f)
	{
		PxVec3 tmp = t.verts[1];
		t.verts[1] = t.verts[2];
		t.verts[2] = tmp;
		nrm = -nrm;
	}
	extrudedTrisNormals[nbExtrudedTris] = nrm;
	nbExtrudedTris++;
}