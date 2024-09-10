void
BatMan::AliveUpdate()
{
	Vector2 vec = (_playerRef.GetCollider().Center() - _collider.Center());//normalizeで変な値になってる
	vec = vec.Normalize();
	_pos.x += vec.x * 2;
	_collider.pos = _pos + Vector2(_cameraRef.OffsetX(), 0);
	_walkFrame++;
}