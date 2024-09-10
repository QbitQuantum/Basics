// return intersect triangle position
bool D3D9RendererMesh::IntersectTri( const PxTransform &tm, const PxVec3 &rayOrigin, const PxVec3 &rayDirection, OUT PxVec3 &out)
{
	if (m_numVertexBuffers <= 0)
		return false;

	PxU32 stride = 0;
	void* vertPositions = m_vertexBuffers[0]->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, stride);
	if (!vertPositions)
		return false;

	PxU16* indices = (PxU16*)m_indexBuffer->lock();

	bool findFace = false;
	float minLength = FLT_MAX;
	for (PxU32 i=0; i < m_numIndices; i+=3)
	{
		const PxVec3 &pos1 = *(PxVec3*) (((PxU8*)vertPositions) + (stride * indices[ i]));
		const PxVec3 &pos2 = *(PxVec3*) (((PxU8*)vertPositions) + (stride * indices[ i+1]));
		const PxVec3 &pos3 = *(PxVec3*) (((PxU8*)vertPositions) + (stride * indices[ i+2]));
		PxVec3 p1 = tm.transform(pos1);
		PxVec3 p2 = tm.transform(pos2);
		PxVec3 p3 = tm.transform(pos3);

		float d;
		float u, v;	
		BOOL isHit1 = D3DXIntersectTri((D3DXVECTOR3*)&p1, (D3DXVECTOR3*)&p2, (D3DXVECTOR3*)&p3, 
			(D3DXVECTOR3*)&rayOrigin, (D3DXVECTOR3*)&rayDirection, &u, &v, &d);
		if(isHit1 && (minLength > d)) 
		{
			//out.x = 1 * ((1-u-v)*p3.x + u*p3.y + v*p3.z);
			//out.y = 0.2f;
			//out.z = -1 * ((1-u-v)*p1.x + u*p1.y + v*p1.z);
			out = (p1 + p2 + p3)/3;
			minLength = d;
			findFace = true;
		}
	}

	m_indexBuffer->unlock();
	m_vertexBuffers[0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);

	return findFace;
}