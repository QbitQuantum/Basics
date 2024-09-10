XMFLOAT3 CSteeringManager::DoSeek(XMFLOAT3 target, float slowDist)
{
	XMFLOAT3 force;
	XMVECTOR vForce;
	XMVECTOR desired;
	XMVECTOR currVelocity;

	currVelocity = XMLoadFloat3(m_pBoid->GetZAxis());

	float dist;

	desired = XMLoadFloat3(&target) - XMLoadFloat3(m_pBoid->GetPosition());
	dist = XMVector3Length(desired).m128_f32[0];
	desired = XMVector3Normalize(desired);

	if (dist <= slowDist)
		desired *= m_pBoid->GetMaxVelocity() * (dist / slowDist);
	else
		desired *= m_pBoid->GetMaxVelocity();

	vForce = desired - currVelocity;

	XMStoreFloat3(&force, vForce);
	return force;
}