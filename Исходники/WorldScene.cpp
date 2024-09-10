void WorldScene::mouseClick(cocos2d::Event* event, Player* player) {
	CCLOG("mouse");
	CCLOG("Category %x", player->getPhysicsBody()->getCategoryBitmask());
	CCLOG("Collision %x", player->getPhysicsBody()->getCollisionBitmask());
	if (player->getArrow() > 0) {
		Vec2 loc = player->getPosition();
		CCLOG("%d", player->getArrow());
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		mouseEvent->getMouseButton();
		//auto pro = Sprite::create("CloseNormal.png");
		auto pro = Projectile::create();
		pro->setPosition(loc);

		this->addChild(pro, 1);
		//pro->setPosition(mouseEvent->getLocation().x, this->getContentSize().height-mouseEvent->getLocation().y);
		if (player->getMode() == 'a') {
			pro->setMode('a');
			Vec2 offset = mouseEvent->getLocation();
			offset.y = this->getContentSize().height - offset.y;
			offset -= player->getPosition();
			offset.normalize();

			auto deg = atan(offset.x / offset.y) * 180 /3.14;
			if (offset.y<0) {
				deg += 180;
			}
			CCLOG("%f", deg);

			auto target = offset*1000 + player->getPosition();
			auto rotate = RotateBy::create(0, deg);
			auto shoot = MoveTo::create(2.0f, target);
			auto remove = RemoveSelf::create();
			pro->runAction(Sequence::create(rotate, shoot, remove, nullptr));
			player->setArrow(player->getArrow() - 1);
		}
		else {
			pro->setMode('b');
			auto shoot = MoveBy::create(2.0f, Vec2(0, 500));
			auto remove = RemoveSelf::create();
			pro->runAction(Sequence::create(shoot, remove, nullptr));
			player->setArrow(player->getArrow() - 4);
		}
		
		
		setArrow(player->getArrow());
	}
}