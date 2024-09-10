void PlayerArrow::Update()
{
	// アングル
	Vector3 playerFront = Vector3(player->GetParameter().mat.GetFront() * Vector3(1, 0, 1)).Normalized();
	if (playerFront.Length() != 0)
	{
		angle_ = Vector3::Inner(playerFront, -Vector3::Forward);
		if (Vector3::Dot(playerFront, Vector3::Left) > 0.0f)
			angle_ *= -1;
	}

	/* プレイヤーデータ */
	// ポジション
	Vector3 playerPos = player->GetParameter().mat.GetPosition();
	Vector2 pos = Vector2(playerPos.x, -playerPos.z);
	if (pos.Length() != 0.0f)
		drawPos_ = MAP_DRAW_POSITION + pos.Normalized() * pos.Length() * RE_SIZE_SCALE;
	else
		drawPos_ = MAP_DRAW_POSITION;

	/* 気流発生 */
	isDash = player->ReturnTackleParameter().dashFlag;
	if (isDash && isDash != prevDash)
		world.UIAdd(UI_ID::FLOWROOT_UI, std::make_shared<FlowRoot>(world, player, &drawPos_, resPiece));
	prevDash = isDash;
}