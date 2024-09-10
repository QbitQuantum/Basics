void GameEntity::init()
{
	_scale = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
	XMStoreFloat4(&_rotation, XMQuaternionIdentity());
	_position = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	_layer = 1;
	_color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}