XMFLOAT3 CMinotaurSpawn::LerpPosition(XMFLOAT3 _start, XMFLOAT3 _end, float lamda)
{
	XMFLOAT3 result;

	XMVECTOR start = XMLoadFloat3(&_start);
	XMVECTOR end = XMLoadFloat3(&_end);

	XMStoreFloat3(&result, XMVectorLerp(start, end, lamda));
	return result;


}