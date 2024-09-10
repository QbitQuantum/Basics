int CMinotaurIdle::UpdateState(CMinotaur* _agent)
{
	XMFLOAT3 curPos = *_agent->GetPosition();

	// Convert them for math
	XMVECTOR mathPos = XMLoadFloat3(&curPos);
	XMVECTOR mathTarget = XMLoadFloat3(_agent->GetPlayer()->GetPosition());

	// Find the vector between the two points
	XMVECTOR mathToVec = XMVectorSubtract(mathTarget, mathPos);
	XMVECTOR mathDistToTarget = XMVector3Length(mathToVec);
	/*if (mathDistToTarget.m128_f32[0] <= 1000.0f)
		return CMinotaur::eChaseState;

	if (m_fWaitTimer < 0)*/
		return CMinotaur::ePatrolState;

	//return CMinotaur::eIdleState;
}