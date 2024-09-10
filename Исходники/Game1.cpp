void Game1::Init()
{
	{
		world = new Physics::World(Vector2F(0, 9.8f));
		b2PolygonShape shape;
		shape.SetAsBox(40, 10);

		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(40, 50);
		groundBodyDef.type = b2_staticBody;
		ground = world->AddRigidBody(&groundBodyDef);
		ground->CreateFixture(&shape, 0.0f);
	}
}