void mouseMovement(POINT mouseInfoNew, XMMATRIX* ViewMatrix){

	LONG x = mouseInfoNew.x;
	LONG y = mouseInfoNew.y;

	float xMovement = (float)960 - x;
	float yMovement = (float)540 - y;

	//---------------------------------------

	*ViewMatrix = XMMatrixTranspose(*ViewMatrix);
	XMMATRIX ViewInverse = XMMatrixInverse(NULL, *ViewMatrix);

	XMFLOAT4X4 View4x4;
	XMStoreFloat4x4(&View4x4, ViewInverse);

	XMVECTOR CamPos = XMVectorSet(View4x4._41, View4x4._42, View4x4._43, 0);
	
	XMMATRIX RotationX = XMMatrixRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), cameraSpeed*xMovement);

	XMVECTOR newCamLook = (XMVectorSet(View4x4._31, View4x4._32 + cameraSpeed*yMovement, View4x4._33, 0)) + CamPos;

	*ViewMatrix = XMMatrixLookAtLH(CamPos, newCamLook, { 0, 1, 0 });
	*ViewMatrix = *ViewMatrix * RotationX;
	*ViewMatrix = XMMatrixTranspose(*ViewMatrix);

}