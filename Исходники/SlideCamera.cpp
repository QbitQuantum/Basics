void SlideCamera::UpdateSlideCamera(std::vector<XMFLOAT3> collidableGeometryPositions,
	std::vector<DWORD> collidableGeometryIndices)
{	
	static XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	static XMVECTOR DefaultRight   = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	static XMVECTOR camForward     = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	static XMVECTOR camRight       = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	static XMVECTOR camUp  = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	static XMVECTOR camPosition    = XMVectorSet(0.0f, 2.0f, -5.0f, 0.0f);
	static XMVECTOR camTarget      = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	static XMMATRIX camView;

	//Rotating the SlideCamera by euler angle
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget         = XMVector3TransformCoord(DefaultForward, camRotationMatrix );
	camTarget         = XMVector3Normalize(camTarget);

	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw);

	//We only move the xz plane by axis y
	//Update the SlideCamera vector
	camRight   = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
	camUp      = XMVector3TransformCoord(camUp, RotateYTempMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);

	CollisionPacket SlideCameraCP;
	SlideCameraCP.ellipsoidSpace = XMVectorSet(1.0f, 3.0f, 1.0f, 0.0f);
	SlideCameraCP.w_Position = camPosition;
	SlideCameraCP.w_Velocity = (moveLeftRight*camRight) + (moveBackForward*camForward);

	camPosition = CollisionSlide(SlideCameraCP,
		collidableGeometryPositions,
		collidableGeometryIndices);

	/*
	// Free-Look SlideCamera
	camRight = XMVector3TransformCoord(DefaultRight, camRotationMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camUp = XMVector3Cross(camForward, camRight);

	//Moving the SlideCamera
	camPosition += moveLeftRight*camRight;
	camPosition += moveBackForward*camForward;
	*/
	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	camTarget = camPosition + camTarget;	

	//Set the SlideCamera matrix
	camView = XMMatrixLookAtLH( camPosition, camTarget, camUp );
	XMStoreFloat4x4(&m_camView, XMMatrixTranspose(camView));
}