bool GamePlay::onTouchBegan(Touch* touch, Event* unused_event) {
  // 1  - Just an example for how to get the  _player object
  //auto node = unused_event->getCurrentTarget();

  // 2
  Vec2 touchLocation = touch->getLocation();
  Vec2 offset = touchLocation - _player->getPosition();

  // 3
  if (offset.x > 0) {
    return true;
  }

  // 4
  auto projectile = Sprite::create("HelloWorld.png");
  projectile->setScale(0.2);
  projectile->setPosition(this->_player->getPosition());

  auto projectileSize = projectile->getBoundingBox().size;
  auto physicsBody = PhysicsBody::createCircle(projectileSize.width *2);
  physicsBody->setDynamic(true);
  physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
  physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
  physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
  projectile->setPhysicsBody(physicsBody);

  this->addChild(projectile);

  // 5
  offset.normalize();
  auto shootAmount = offset * 1000;

  // 6
  auto realDest = shootAmount + projectile->getPosition();

  // 7
  auto actionMove = MoveTo::create(2.0f, realDest);
  auto actionRemove = RemoveSelf::create();
  projectile->runAction(Sequence::create(actionMove,actionRemove, nullptr));

  return true;
}