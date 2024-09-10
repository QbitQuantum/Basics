inline XMFLOAT4X4 BuildTransform( XMFLOAT3& translation , XMFLOAT4& rotation )
{
	XMVECTOR stuff = XMLoadFloat4(&rotation);
	XMMATRIX matrix = XMMatrixRotationQuaternion(stuff);
	matrix._41 = translation.x;
	matrix._42 = translation.y;
	matrix._43 = translation.z;
	XMFLOAT4X4 mtx;
	XMStoreFloat4x4(&mtx, matrix);
	return mtx;
}