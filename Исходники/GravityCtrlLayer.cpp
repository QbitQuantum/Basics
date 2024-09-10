bool GravityCtrlLayer::checkIsCancelled(cocos2d::Point& screenPosition) {
  cocos2d::Size screenSize = Director::getInstance()->getWinSize();
  Vec2 center = Vec2(screenSize.width/2, screenSize.height/2);
  Vec2 touch = Vec2(screenPosition.x, screenPosition.y);
  float distance = center.distance(touch);
  if (distance < screenSize.width * m_ratioToCancel / 2)
    return false;
  else
    return true;
}