std::string RobotController::getPointedTrashName(std::string entName)
{
  // 発話者の名前からSimObjを取得します
  SimObj *tobj = getObj(entName.c_str());

  // メッセージ送信者の左肘関節の位置を取得します
  Vector3d jpos;
  if(!tobj->getJointPosition(jpos, "RARM_JOINT4")) {
    LOG_ERR(("failed to get joint position"));
    return "";
  }
  // メッセージ送信者の左肘から左手首をつなぐベクトルを取得します
  Vector3d jvec;
  if(!tobj->getPointingVector(jvec, "RARM_JOINT4", "RARM_JOINT7")) {
    LOG_ERR(("failed to get pointing vector"));
    return "";
  }

  double distance = 0.0;
  std::string objName = "";

  // 全ゴミオブジェクトでループします
  int trashboxSize = m_trashboxs.size();
  for(int i = 0; i < trashboxSize; i++) {

  // エンティティの位置を取得します
  SimObj *obj = getObj(m_trashboxs[i].c_str());
  Vector3d objVec;
  obj->getPosition(objVec);

  // エンティティと左肘関節を結ぶベクトルを作成します
  objVec -= jpos;

  // cos角度が不の場合（指差した方向と反対側にある場合)は対象から外します
  double cos = jvec.angle(objVec);
  if(cos < 0)
    continue;

  // 指差した方向ベクトルまでの最短距離の計算
  double theta = acos(cos);
  double tmp_distance = sin(theta) * objVec.length();

  // 最小距離の場合は名前、距離を保存しておく
  if(tmp_distance < distance || distance == 0.0){
    distance = tmp_distance;
    objName = obj->name();
    }
  }
  // エンティティでループして最も近いオブジェクトの名前を取得する
  return objName;
}