// object まで移動
double MyController::goToObj(Vector3d nextPos, double velocity, double range, double now)
{
	printf("goToObj関数内　goToObj %lf %lf %lf \n", nextPos.x(), nextPos.y(), nextPos.z());	
  	// 自分の位置の取得
  	Vector3d myPos;
 	m_my->getPosition(myPos);
	printf("goToObj関数内 ロボットの現在位置: x: %lf, z %lf \n", myPos.x(), myPos.z()); 

	// 自分の位置からターゲットを結ぶベクトル
	Vector3d pos = nextPos;
	pos -= myPos;

	// y方向は考えない
	pos.y(0);

	// 距離計算
	double distance = pos.length() - range;
	//printf("distance: %lf \n", distance);
	//printf("range = %lf \n", range);

	// 車輪の半径から移動速度を得る
	double vel = m_radius*velocity;

	// 移動開始
	m_my->setWheelVelocity(velocity, velocity);

	// 到着時間取得
	double time = distance / vel;

	return now + time;
}