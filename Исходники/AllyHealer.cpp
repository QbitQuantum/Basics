//-----------------------------------------------------------------------------
//! 更新(プレイヤーの周りに常にいる)
//!	@param	[in]	player	プレイヤー座標
//-----------------------------------------------------------------------------
void AllyHealer::UpdateNormal(Vector3& playerPos)
{
	// プレイヤーへのベクトル
	Vector3	dir	   = playerPos - _position;
	// 長さ取得
	f32		length = dir.length();

	Circle	goalCircle(playerPos, 100.0f);
	Circle	myCircle(_position, _radius);

	// プレイヤーの近くにいるかどうか
	if( goalCircle.isHit(myCircle) ){
		// 近くにいる
		_speed = 0.0f;
		_keyUpdate = true;
	}else{
		// 近くにいない
		_speed = 3.0f;
		dir = dir.normalize();
		_rotation._y = atan2f(dir._x, dir._z);
		_keyUpdate = false;
	}



}