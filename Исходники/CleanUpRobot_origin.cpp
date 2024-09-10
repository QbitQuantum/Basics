// object まで移動
double MyController::goToObj(Vector3d pos, double velocity, double range, double now)
{
  // 自分の位置の取得
  Vector3d myPos;
  m_my->getPosition(myPos);
  
  // 自分の位置からターゲットを結ぶベクトル
  pos -= myPos;
  
  // y方向は考えない
  pos.y(0);

  // 距離計算
  double distance = pos.length() - range;

  // 車輪の半径から移動速度を得る
  double vel = m_radius*velocity;

  // 移動開始
  m_my->setWheelVelocity(velocity, velocity);

  // 到着時間取得
  double time = distance / vel;

  return now + time;
}