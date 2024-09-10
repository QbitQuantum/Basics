void AppEntry::onCreateComplete()
{

	DirectEngine *engine = DirectEngine::getInstance();

	Reflect *scene = new Reflect();
	scene->init();

	engine->addScene(scene);
	scene->release();
}