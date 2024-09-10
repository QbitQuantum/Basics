XMFLOAT3 EliteEnemyShip::getPosition()
{
	XMFLOAT4 pos;
	XMFLOAT4 orig = XMFLOAT4(0,0,0,1);
	XMFLOAT4X4 mat = *(body->getWorldMatrix());
	XMStoreFloat4(&pos, XMVector4Transform(XMLoadFloat4(&orig), XMLoadFloat4x4(&mat)));
	return (XMFLOAT3(pos.x, pos.y, pos.z));
}