void PlaneProtect::ContactEff( Node* node, float radius, const Vec2& pos, float s, const Vec2& offset )
{
	Vec2 randPos = Vec2(pos.x + rand_minus1_1() * 80, pos.y + rand_minus1_1() * 80);

	//两点之间的连线，计算碰撞特效需要旋转的角度
	Vec2 mypos = node->convertToWorldSpaceAR(Vec2::ZERO);
	Vec2 newVec = randPos - mypos;
	float angle = newVec.getAngle() * Pi2Angle;

	newVec.normalize();
	newVec *= radius;

	auto size = node->getContentSize();

	auto endPos =Vec2( size.width*0.5 + newVec.x, size.height*0.5 + newVec.y);
	endPos += offset;

	auto sp = Sprite::create("Effect/contactEff/contactEff.png");
	sp->setPosition(endPos);
	sp->setRotation(90 - angle);
	node->addChild(sp);

	auto parti1 = EffectsManager::addParticle("particla/SpeedUpContact/SpeedUpContact.plist",node,endPos);
	if (parti1)
	{
		parti1->setScale(s);
	}

	ActionInterval* scale = ScaleTo::create(0.1f,(7.0 + rand_0_1()) * s,(2.0f + rand_0_1())*s);
	CallFuncN* func = CallFuncN::create(nullptr,callfuncN_selector(PlaneProtect::removeEff));
	ActionInterval* seq = Sequence::create(scale, func, nullptr);
	sp->runAction(seq);
}