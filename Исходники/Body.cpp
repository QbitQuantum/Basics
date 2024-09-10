void Body::Update(float dt, btTransform& Parent)
{
	btVector3 parentPos;
	parentPos = Parent.getOrigin();

	//Get Offset Rotation of a model(child)
	btQuaternion LocalRot;
	LocalRot = btQuaternion(m_yaw, m_pitch, m_roll);

	btQuaternion parentRotation;
	parentRotation = Parent.getRotation();

	//Construct Directx Matricies out of give Quaternion rotations, sets up proper transformation of a model, Global + local
	XMMATRIX matrixChildRotation = XMMatrixRotationQuaternion(XMLoadFloat4(&XMFLOAT4(LocalRot.getX(), LocalRot.getY(), LocalRot.getZ(), LocalRot.getW())));
	XMMATRIX matrixParentRotation = XMMatrixRotationQuaternion(XMLoadFloat4(&XMFLOAT4(parentRotation.getX(), parentRotation.getY(), parentRotation.getZ(), parentRotation.getW())));

	//calcualte the final rotation by multiplying quaternions using dxmatrix
	XMMATRIX matrixFinalRotation = matrixChildRotation * matrixParentRotation;

	XMFLOAT3 m_offset = XMFLOAT3(0, 0, 0);
	XMMATRIX childOffset = XMMatrixTranslation(m_offset.x, m_offset.y, m_offset.z);

	XMMATRIX zeroWorld = XMMatrixTranslation(0, 0, 0);

	XMMATRIX translationMat = XMMatrixTranslation(parentPos.getX(), parentPos.getY(), parentPos.getZ());
	XMMATRIX scaleMat = XMMatrixScaling(m_scale, m_scale, m_scale);
	XMMATRIX worldMat = childOffset * matrixFinalRotation * zeroWorld * scaleMat * translationMat;

	XMStoreFloat4x4(&m_worldMat, worldMat);
}