//--------------------------------------------------------------------------------------
// Rotates the entity towards a specific point.
// Param1: The position, the entity should look at.
//--------------------------------------------------------------------------------------
void EntityMovementManager::LookAt(const XMFLOAT2& lookAtPosition)
{
	XMFLOAT2 newViewDirection(0.0f, 1.0f);
	XMStoreFloat2(&newViewDirection, XMVector2Normalize(XMLoadFloat2(&lookAtPosition) - XMLoadFloat2(&m_pEntity->GetPosition())));
	
	m_pEntity->SetViewDirection(newViewDirection);
	
	float rotation = (atan2(m_pEntity->GetViewDirection().x, m_pEntity->GetViewDirection().y)) * 180 / XM_PI;
	m_pEntity->SetRotation(rotation);
}