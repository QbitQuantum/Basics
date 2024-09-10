//--------------------------------------------------------------------------------------
// Tells whether a soldier is at a certain target or not. Accounts for the target reached
// radius used by the soldier.
// Param1: The target position, for which to check if the soldier has reached it.
// Returns true if the soldier has reached the target, false otherwise. 
//--------------------------------------------------------------------------------------
bool Soldier::IsAtTarget(const XMFLOAT2& target)
{
	float distance(0.0f);
	XMStoreFloat(&distance, XMVector2Length(XMLoadFloat2(&target) - XMLoadFloat2(&GetPosition())));

	return (distance <= m_soldierProperties.m_targetReachedRadius);
}