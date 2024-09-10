void BoidManager::initialisePositions()
{
	for	(int i = 0; i < maxBirds; ++i)
	{
		XMMATRIX mRotX, mRotY, mRotZ, mTrans, WorldMatrix;
		XMFLOAT4 iPos = m_birds.at(i)->getPosition();
		XMFLOAT4 iRot = m_birds.at(i)->getRotation();

		mRotX = XMMatrixRotationX(XMConvertToRadians(iRot.x));
		mRotY = XMMatrixRotationY(XMConvertToRadians(iRot.y));
		mRotZ = XMMatrixRotationZ(XMConvertToRadians(iRot.z));

		mTrans = XMMatrixTranslation(iPos.x, iPos.y, iPos.z);

		WorldMatrix = mRotZ * mRotX * mRotY * mTrans;

		m_birds.at(i)->setWorldMatrix(WorldMatrix);
		m_birds.at(i)->setVector(XMVector4Normalize(WorldMatrix.r[2]));
	}
}