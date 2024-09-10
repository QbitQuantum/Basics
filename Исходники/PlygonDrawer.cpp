void PlygonDrawer::playBlastAnim(Point2i pos, enNodeColor color) 
{
	auto convt = m_graph->m_coordCvt;
	Vec2 coord = convt.getCoord(pos);

	auto scene = Director::getInstance()->getRunningScene();
	PhysicsWorld* phyWld = scene->getPhysicsWorld();

	for (int i = 0; i < 5; ++i)
	{
		Sprite* spStar = BeadFactory::createBlastStar(color, 0.2 + 0.1 * i);
		float radius = spStar->getContentSize().width/2 * spStar->getScaleX();
		spStar->retain();
		spStar->setPosition(coord);
		/*spStar->runAction( Sequence::createWithTwoActions(MoveBy::create(2.0f, dir),
				CallFunc::create([=]() {
				spStar->removeFromParent();
				spStar->release();
		})));*/
		spStar->runAction( Sequence::createWithTwoActions(DelayTime::create(15.0f),
			CallFunc::create([=]() {
				spStar->removeFromParent();
				spStar->release();
		})));
#define GravityAmpl 50
		PhysicsMaterial phyMat = PHYSICSBODY_MATERIAL_DEFAULT; phyMat.density = 200.0f;
		auto body = PhysicsBody::createCircle(radius, phyMat);
		Vec2 dir = ccp(rand()%100 - 50, rand()%100 - 50);
		dir.normalize(); dir = dir * body->getMass() * 8.0f * GravityAmpl;
		Vect force(dir);
		body->applyImpulse(force);
		body->setDynamic(true);
		//body->setCategoryBitmask(0x04);
		//body->setCollisionBitmask(0x08);
		body->setGroup(-1);
		body->setGravityEnable(true);

		spStar->setPhysicsBody(body);
		m_tileMap->addChild(spStar, 100);
	}

	static bool isPhyInit = false;
	if (! isPhyInit) {
		isPhyInit = true;
		phyWld->setGravity(Vect(0.0f, -9.8f * GravityAmpl));
		//phyWld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		phyWld->setUpdateRate(2.5f);
	}
}