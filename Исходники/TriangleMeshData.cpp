int TriangleMeshData::createDebugMesh( CFly::Object* obj , CFly::Material* mat )
{
	struct vtx_t
	{
		vtx_t( Vec3D const& v , Vec3D const& c)
			:vtx(v),color(c){}
		Vec3D vtx;
		Vec3D color;
	};

	std::vector< vtx_t > vtxVec;
	std::vector< TriangleIndex > triVec;
	vtxVec.reserve( m_triVec.size() * 3 );
	triVec.reserve( m_triVec.size() );
	int index = -1;
	for (int i = 0; i < m_triVec.size(); ++i )
	{
		TriangleIndex& tri = m_triVec[i];
		Vec3D& v0 = m_vertexVec[ tri.v[0] ]; 
		Vec3D& v1 = m_vertexVec[ tri.v[1] ]; 
		Vec3D& v2 = m_vertexVec[ tri.v[2] ]; 
		Vec3D normal = ( v1 - v0 ).cross( v2 - v1 );

		float len = sqrt( normal.dot(normal) );
		float c = ( 2 + (normal.y + normal.z)/len )/ 4 ;

		Vec3D color( c ,c , c );
		vtxVec.push_back( vtx_t( v0 , color ) );
		vtxVec.push_back( vtx_t( v1 , color ) );
		vtxVec.push_back( vtx_t( v2 , color ) );

		TriangleIndex t;
		t.v[0] = ++index;
		t.v[1] = ++index;
		t.v[2] = ++index;

		triVec.push_back( t );
	}

	return obj->createIndexedTriangle( 
		mat , CFVT_XYZ_CF1 , 
		(float*) &vtxVec[0] , vtxVec.size() , 
		&( triVec[0].v[0] ) , triVec.size() );
}