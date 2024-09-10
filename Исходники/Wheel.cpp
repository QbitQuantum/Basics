void Wheel::Update(float dt,btTransform & parentTransform)
{
	///ROTATION
	//get the quaternion rotation from euler angles using bt
	//offset rotation(initial rotation)
	btQuaternion btLocalRot = btQuaternion(m_yaw, m_pitch, m_roll);
	XMMATRIX localRot = XMMatrixRotationQuaternion(XMLoadFloat4(&XMFLOAT4(btLocalRot.getX(), btLocalRot.getY(), btLocalRot.getZ(), btLocalRot.getW())));
	//worldspace rotation
	btQuaternion btParentRot = parentTransform.getRotation();
	XMMATRIX ParentRot = XMMatrixRotationQuaternion(XMLoadFloat4(&XMFLOAT4(btParentRot.getX(), btParentRot.getY(), btParentRot.getZ(), btParentRot.getW())));
	//add rotations together
	XMMATRIX finalRot = localRot *  ParentRot;
	
	
	btVector3 btparentPos = parentTransform.getOrigin();
	XMMATRIX translationMat = XMMatrixTranslation(btparentPos.getX(), btparentPos.getY(), btparentPos.getZ());
	//XMMATRIX scaleMat = XMMatrixScaling(m_scale, m_scale, m_scale);
	XMMATRIX scaleMat = XMMatrixScaling(m_scale, m_scale, m_scale);
	XMMATRIX worldMat = finalRot * scaleMat * translationMat;
	XMStoreFloat4x4(&m_worldMat, worldMat);
}