DirectX::SimpleMath::Ray D3D11App::CalcPickingRay(int sx, int sy)
{
	XMMATRIX view = g_objTrackballCameraController.View();
	//投影变换
	Matrix P = g_objTrackballCameraController.Proj();

	float vx = (+2.0f*sx / mClientWidth - 1.0f) / (P(0, 0));
	float vy = (-2.0f*sy / mClientHeight + 1.0f) / (P(1, 1));
	// Ray definition in view space.
	XMVECTOR rayOrigin = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR rayDir = XMVectorSet(vx, vy, 1.0f, 0.0f);

	XMMATRIX invP = XMMatrixInverse(&XMMatrixDeterminant(P), P);

	// Tranform ray to local space of Mesh.
	XMMATRIX V = view;
	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(V), V);


	XMMATRIX W = Matrix::Identity;
	XMMATRIX invWorld = XMMatrixInverse(&XMMatrixDeterminant(W), W);

	XMMATRIX toLocal = XMMatrixMultiply(invView, invWorld);


	rayOrigin = XMVector3TransformCoord(rayOrigin, toLocal);
	rayDir = XMVector3TransformNormal(rayDir, toLocal);

	// Make the ray direction unit length for the intersection tests.
	rayDir = XMVector3Normalize(rayDir);

	DirectX::SimpleMath::Ray ray(rayOrigin, rayDir);
	return ray;
}