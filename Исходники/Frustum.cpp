//-----------------------------------------------------------------------------//
// 카메라(view) * 프로젝션(projection)행렬을 입력받아 6개의 평면을 만든다.
//-----------------------------------------------------------------------------//
bool cFrustum::Create(cRenderer &renderer, const Matrix44 &matViewProj)
{
	// 투영행렬까지 거치면 모든 3차원 월드좌표의 점은 (-1,-1,0) ~ (1,1,1)사이의 값으로 바뀐다.
	SetCube(renderer, Vector3(-1,-1,0), Vector3(1,1,1) );

	// view * proj의 역행렬을 구한다.
	Matrix44 matInv = matViewProj.Inverse();

	// Vertex_최종 = Vertex_local * Matrix_world * Matrix_view * Matrix_Proj 인데,
	// Vertex_world = Vertex_local * Matrix_world이므로,
	// Vertex_최종 = Vertex_world * Matrix_view * Matrix_Proj 이다.
	// Vertex_최종 = Vertex_world * ( Matrix_view * Matrix_Proj ) 에서
	// 역행렬( Matrix_view * Matrix_Proj )^-1를 양변에 곱하면
	// Vertex_최종 * 역행렬( Matrix_view * Matrix_Proj )^-1 = Vertex_World 가 된다.
	// 그러므로, m_Vtx * matInv = Vertex_world가 되어, 월드좌표계의 프러스텀 좌표를 얻을 수 있다.
	sVertexDiffuse *vertices = (sVertexDiffuse*)m_vtxBuff.Lock();
	RETV(!vertices, false);

	m_fullCheck = false;

	for (int i = 0; i < 8; i++)
		vertices[ i].p *= matInv;

	// 2번과 5번은 프러스텀중 near평면의 좌측상단과 우측하단이므로, 둘의 좌표를 더해서 2로 나누면
	// 카메라의 좌표를 얻을 수 있다.(정확히 일치하는 것은 아니다.)
	m_pos = ( vertices[2].p + vertices[5].p ) / 2.0f;

	// 얻어진 월드좌표로 프러스텀 평면을 만든다
	// 벡터가 프러스텀 안쪽에서 바깥쪽으로 나가는 평면들이다.
	m_plane[3].Init( vertices[ 4].p, vertices[ 5].p, vertices[ 6].p );	// 원 평면(far)
	m_plane[4].Init( vertices[ 0].p, vertices[ 2].p, vertices[ 6].p );	// 좌 평면(left)
	m_plane[5].Init( vertices[ 1].p, vertices[ 5].p, vertices[ 7].p );	// 우 평면(right)

	m_vtxBuff.Unlock();

	return TRUE;
}