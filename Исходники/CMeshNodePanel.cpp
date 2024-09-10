void CMeshNodePanel::updateSelectedObjectTransform(f32 delta)
{
	EditorScene* scene = EditorScene::getInstance();
	if (!scene)
		return;

	SNodeInfo* info = scene->GetSelectedNodeInfo();
	if (!info)
		return;

	const f32 MOVE_UNIT = 10.0f;
	const f32 SCALING_UNIT = 5.0f;
	
	ICameraNode* camera = scene->GetCamera();
	XMFLOAT3 look = camera->getLookVector();
	XMFLOAT3 up(0, 1.0f, 0);
	XMFLOAT3 right = camera->getRightVector();

	XMVECTOR look_v = XMVectorSet(look.x, 0, look.z, 0);
	look_v = XMVector4Normalize(look_v);

	XMStoreFloat3(&look, look_v);

	XMFLOAT3 movement(0, 0, 0);
	XMFLOAT3 scaling(0, 0, 0);

	if (GetAsyncKeyState('W') & 0x8000)
	{
		movement = math::VectorMultiply(look, delta * MOVE_UNIT);
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		movement = math::VectorMultiply(look, -delta * MOVE_UNIT);
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		movement = math::VectorMultiply(right, -delta * MOVE_UNIT);
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		movement = math::VectorMultiply(right, delta * MOVE_UNIT);
	}

	if (GetAsyncKeyState('R') & 0x8000)
	{
		movement = math::VectorMultiply(up, delta * MOVE_UNIT);
	}

	if (GetAsyncKeyState('F') & 0x8000)
	{
		movement = math::VectorMultiply(up, -delta * MOVE_UNIT);
	}

	if (GetAsyncKeyState(VK_ADD) & 0x8000)
	{
		scaling = XMFLOAT3(1.0f, 1.0f, 1.0f);
	}

	if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000)
	{
		scaling = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	}

	scaling = math::VectorMultiply(scaling, delta * SCALING_UNIT);

	info->Position = math::VectorAdd(info->Position, movement);
	info->Scaling = math::VectorAdd(info->Scaling, scaling);

	scene->UpdateNodeInfo(info);
	ShowNodeInfo(info);
}