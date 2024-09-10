void ObjectManager::addCorpse(float x, float y, float w, float h, float d, float f, bool r, std::string fileName){
	Corpse * c = new Corpse;
	c->setInterfaces( renderer, this, gameStats );
	c->setDensity(d);
	c->setFriction(f);
	c->setRight(r);
	c->setImage(fileName);

	Object * temp = c;
	objects.push_back(temp);
	objects.back()->setID( objects.size() - 1);
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.userData = temp;
	bodyDef.position.Set(x, y);

	temp->setBody( world->CreateBody(&bodyDef) );
	temp->initialize(w, h);
}