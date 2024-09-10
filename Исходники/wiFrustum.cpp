void Frustum::ConstructFrustum(float screenDepth, XMFLOAT4X4 projectionMatrix, XMFLOAT4X4 viewMatrix)
{
	view=viewMatrix;

	float zMinimum, r;
	XMFLOAT4X4 matrix;

	
	// Calculate the minimum Z distance in the frustum.
	zMinimum = -projectionMatrix._43 / projectionMatrix._33;
	r = screenDepth / (screenDepth - zMinimum);
	projectionMatrix._33 = r;
	projectionMatrix._43 = -r * zMinimum;

	// Create the frustum matrix from the view matrix and updated projection matrix.
	XMStoreFloat4x4( &matrix,XMMatrixMultiply(XMLoadFloat4x4(&viewMatrix), XMLoadFloat4x4(&projectionMatrix)) );

	// Calculate near plane of frustum.
	m_planes[0].x = matrix._14 + matrix._13;
	m_planes[0].y = matrix._24 + matrix._23;
	m_planes[0].z = matrix._34 + matrix._33;
	m_planes[0].w = matrix._44 + matrix._43;
	XMStoreFloat4( &m_planesNorm[0],XMPlaneNormalize(XMLoadFloat4(&m_planes[0])) );

	// Calculate far plane of frustum.
	m_planes[1].x = matrix._14 - matrix._13; 
	m_planes[1].y = matrix._24 - matrix._23;
	m_planes[1].z = matrix._34 - matrix._33;
	m_planes[1].w = matrix._44 - matrix._43;
	XMStoreFloat4( &m_planesNorm[1],XMPlaneNormalize(XMLoadFloat4(&m_planes[1])) );

	// Calculate left plane of frustum.
	m_planes[2].x = matrix._14 + matrix._11; 
	m_planes[2].y = matrix._24 + matrix._21;
	m_planes[2].z = matrix._34 + matrix._31;
	m_planes[2].w = matrix._44 + matrix._41;
	XMStoreFloat4( &m_planesNorm[2],XMPlaneNormalize(XMLoadFloat4(&m_planes[2])) );

	// Calculate right plane of frustum.
	m_planes[3].x = matrix._14 - matrix._11; 
	m_planes[3].y = matrix._24 - matrix._21;
	m_planes[3].z = matrix._34 - matrix._31;
	m_planes[3].w = matrix._44 - matrix._41;
	XMStoreFloat4( &m_planesNorm[3],XMPlaneNormalize(XMLoadFloat4(&m_planes[3])) );

	// Calculate top plane of frustum.
	m_planes[4].x = matrix._14 - matrix._12; 
	m_planes[4].y = matrix._24 - matrix._22;
	m_planes[4].z = matrix._34 - matrix._32;
	m_planes[4].w = matrix._44 - matrix._42;
	XMStoreFloat4( &m_planesNorm[4],XMPlaneNormalize(XMLoadFloat4(&m_planes[4])) );

	// Calculate bottom plane of frustum.
	m_planes[5].x = matrix._14 + matrix._12;
	m_planes[5].y = matrix._24 + matrix._22;
	m_planes[5].z = matrix._34 + matrix._32;
	m_planes[5].w = matrix._44 + matrix._42;
	XMStoreFloat4( &m_planesNorm[5],XMPlaneNormalize(XMLoadFloat4(&m_planes[5])) );

}