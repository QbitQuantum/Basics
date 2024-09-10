void  IObject::Scale(float scaleX, float scaleY, float scaleZ)
{

	XMVECTOR quat = XMQuaternionRotationMatrix(XMLoadFloat4x4(&m_mWorld));
	XMFLOAT3 pos = *GetPosition();
	XMMATRIX newScale = XMMatrixIdentity();
	XMMATRIX newMat = XMMatrixIdentity();
	
	newScale = XMMatrixScaling(scaleX, scaleY, scaleZ);

	newMat = newScale * XMMatrixRotationQuaternion(quat);
	XMStoreFloat4x4(&m_mWorld, newMat);
	m_mWorld._41 = pos.x;
	m_mWorld._42 = pos.y;
	m_mWorld._43 = pos.z;

	if (m_cpRenderMesh)
		m_cpRenderMesh->GetPositionMatrix() = m_mWorld;
}