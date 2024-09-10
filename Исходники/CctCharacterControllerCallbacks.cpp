static void outputBoxToStream(PxShape* boxShape, const PxTransform& globalPose, IntArray& geomStream, TriArray& worldTriangles, IntArray& triIndicesArray,
								const PxExtendedVec3& origin, const PxBounds3& tmpBounds, const CCTParams& params, Cm::RenderBuffer* renderBuffer)
{
	PX_ASSERT(boxShape->getGeometryType() == PxGeometryType::eBOX);
	PxBoxGeometry bg;
	boxShape->getBoxGeometry(bg);

	//8 verts in local space.
	const PxF32 dx = bg.halfExtents.x;
	const PxF32 dy = bg.halfExtents.y;
	const PxF32 dz = bg.halfExtents.z;
	PxVec3 boxVerts[8]=
	{
		PxVec3(-dx,-dy,-dz),
		PxVec3(+dx,-dy,-dz),
		PxVec3(+dx,+dy,-dz),
		PxVec3(-dx,+dy,-dz),
		PxVec3(-dx,-dy,+dz),
		PxVec3(+dx,-dy,+dz),
		PxVec3(+dx,+dy,+dz),
		PxVec3(-dx,+dy,+dz)
	};
	//Transform verts into world space.
	PxVec3 pxOrigin = toVec3(origin);
	for(PxU32 i = 0; i < 8; i++)
	{
		boxVerts[i] = globalPose.transform(boxVerts[i]) - pxOrigin;
	}

	//Index of triangles.
	PxU32 boxTris[12][3]=
	{
		{0,2,1},
		{2,0,3},	//0,1,2,3

		{3,6,2},
		{6,3,7},	//3,2,6,7
		
		{7,5,6},
		{5,7,4},	//7,6,5,4

		{4,1,5},
		{1,4,0},	//4,5,1,0

		{0,7,3},
		{7,0,4},	//0,3,7,4

		{2,5,1},
		{5,2,6}		//2,1,5,6
	};

	TouchedMesh* touchedMesh			= (TouchedMesh*)reserve(geomStream, sizeof(TouchedMesh)/sizeof(PxU32));
	touchedMesh->mType					= TouchedGeomType::eMESH;
	touchedMesh->mUserData				= boxShape;
	touchedMesh->mOffset				= origin;
	touchedMesh->mNbTris				= 12;
	touchedMesh->mIndexWorldTriangles	= worldTriangles.size();

	// Reserve memory for incoming triangles
	PxTriangle* TouchedTriangles = reserve(worldTriangles, 12);

	for(PxU32 i = 0; i < 12; i++)
	{
		PxTriangle& CurrentTriangle = TouchedTriangles[i];

		CurrentTriangle.verts[0] = boxVerts[boxTris[i][0]];
		CurrentTriangle.verts[1] = boxVerts[boxTris[i][1]];
		CurrentTriangle.verts[2] = boxVerts[boxTris[i][2]];

		triIndicesArray.pushBack(PX_INVALID_U32);
	}
}