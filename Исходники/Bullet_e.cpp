Bullet_e::Bullet_e(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color, XMFLOAT3 TravelVec)
{
	XMVECTOR _rotzAxis{ TravelVec.x, TravelVec.y, TravelVec.z, 0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_rotationValue = 0.0f;
	m_scale = Scale;
	m_position = Position;
	m_entityBox.Extents = XMFLOAT3(1, 0, 1);
	m_health = Health;
	m_speed = 28;
	m_travelVec = TravelVec;
	m_light = new Light(XMFLOAT4(Position.x, Position.y, Position.z, 1.0f), XMFLOAT4(Color.x, Color.y, Color.z, 1.0f), XMFLOAT4(2, 1, 0, 0));
}