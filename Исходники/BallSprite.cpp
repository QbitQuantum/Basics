void BallSprite::update(float dt)
{
	Vec2 vec = this->getPhysicsBody()->getVelocity();
	vec.normalize();
	vec = vec * _velocity;
	this->getPhysicsBody()->setVelocity(vec);
	
}