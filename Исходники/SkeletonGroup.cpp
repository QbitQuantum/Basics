XMVECTOR CSkeletonGroup::CalculateAlignment()
{

	// Calculate the avarage velocity
	XMVECTOR avgVelocity = XMVECTOR();
	for (size_t i = 0; i < m_vSkeletons.size(); i++)
	{
		CSkeleton* other = reinterpret_cast<CSkeleton*>(m_vSkeletons[i]);
		XMFLOAT3 vec = other->GetWorldVelocity();
		XMVECTOR otherVelocity = XMLoadFloat3(&vec);
		avgVelocity += otherVelocity;
	}
	avgVelocity /= (float)m_vSkeletons.size();
	avgVelocity.m128_f32[1] = 0.0f;

	if (XMVector3Length(avgVelocity).m128_f32[0] > 1.0f)
		avgVelocity = XMVector3Normalize(avgVelocity);

	return avgVelocity * ALIGNMENT_STRENGTH;

}