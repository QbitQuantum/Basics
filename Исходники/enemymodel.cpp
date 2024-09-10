void EnemyModel::MoveForwardDelta(float delta)
{
	XMFLOAT3 effectiveDirectionVector;
	XMFLOAT4X4 torsoDirectionMatrix = m_Torso->GetWorldRotateMatrix();
    XMStoreFloat3( &effectiveDirectionVector,  XMVector3Transform( XMLoadFloat3(&m_directionVector), XMLoadFloat4x4(&torsoDirectionMatrix) ));

	float deltaX = effectiveDirectionVector.x*delta;
	float deltaY = effectiveDirectionVector.y*delta;
	float deltaZ = effectiveDirectionVector.z*delta;
	
	m_Head->worldTranslate(deltaX, deltaY, deltaZ);
	m_Torso->worldTranslate(deltaX, deltaY, deltaZ);
	m_LeftArm->worldTranslate(deltaX, deltaY, deltaZ);
	m_RightArm->worldTranslate(deltaX, deltaY, deltaZ);
	m_LeftLeg->worldTranslate(deltaX, deltaY, deltaZ);
	m_RightLeg->worldTranslate(deltaX, deltaY, deltaZ);
}