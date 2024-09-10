XMMATRIX LightHandler::CalcView(Camera* camera)
{
	XMVECTOR posVec = XMLoadFloat3(&mPoints[0].Position);
	XMVECTOR up = XMLoadFloat3(&XMFLOAT3(0.0f, 1.0f, 0.0f));
	XMVECTOR look = XMLoadFloat3(&XMFLOAT3(0.0f, 0.0f, 1.0f));
	return XMMatrixLookAtLH(posVec, look, up);
}