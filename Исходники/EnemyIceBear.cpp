void EnemyIceBear::DrawLifeBar(const GameContext& gameContext)
{
	int width = OverlordGame::GetGameSettings().Window.Width;
	int height = OverlordGame::GetGameSettings().Window.Height;

	XMFLOAT3 worldPos = m_Position;
	worldPos.y += 8;

	XMVECTOR healthPos = XMLoadFloat3(&worldPos);
	XMMATRIX proj = XMLoadFloat4x4(&gameContext.pCamera->GetViewProjection());

	healthPos = XMVector3Transform(healthPos, proj);
	
	XMFLOAT4 screenPos;
	XMStoreFloat4(&screenPos, healthPos);

	screenPos.x /= screenPos.w;
	screenPos.y /= screenPos.w;

	if (screenPos.z > 0)
	{
		XMFLOAT3 pos = XMFLOAT3(screenPos.x, screenPos.y, 0.9f);

		pos.x = width*(pos.x + 1.0f) / 2.0f;
		pos.y = height * (1.0f - ((pos.y + 1.0f) / 2.0f));
		m_pHealthBarFrame->GetTransform()->Translate(pos);

		XMFLOAT3 posInside = XMFLOAT3(pos.x - 48, pos.y, 0.9f);
		m_pHealthBarInside->GetTransform()->Translate(posInside);
	}
	else
	{
		m_pHealthBarFrame->GetTransform()->Translate(XMFLOAT3(-300, 0, 0));
		m_pHealthBarInside->GetTransform()->Translate(XMFLOAT3(-300, 0, 0));
	}

}