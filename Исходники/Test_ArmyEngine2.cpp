int main() {
	auto armyEngine = ArmyEngine::getInstance();
	armyEngine->addEntity(createCursor());
	armyEngine->addEntity(createButton("Resume", 100, 100));
	/*armyEngine->addEntity(createButton("Restart", 100, 60));
	armyEngine->addEntity(createButton("Quit", 100, 110));
	armyEngine->addEntity(createButton("Other3", 100, 160));
	armyEngine->addEntity(createButton("Other1", 250, 10));
	armyEngine->addEntity(createButton("Other2", 250, 60));
	armyEngine->addEntity(createButton("Other3", 250, 110));
	armyEngine->addEntity(createButton("Other3", 250, 160));
	armyEngine->addEntity(createButton("Other1", 400, 10));
	armyEngine->addEntity(createButton("Other2", 400, 60));
	armyEngine->addEntity(createButton("Other3", 400, 110));
	armyEngine->addEntity(createButton("Other3", 400, 160));
	armyEngine->addEntity(createButton("Other1", 550, 10));
	armyEngine->addEntity(createButton("Other2", 550, 60));
	armyEngine->addEntity(createButton("Other3", 550, 110));
	armyEngine->addEntity(createButton("Other3", 550, 160));
	armyEngine->addEntity(createButton("Other1", 700, 10));
	armyEngine->addEntity(createButton("Other2", 700, 60));
	armyEngine->addEntity(createButton("Other3", 700, 110));
	armyEngine->addEntity(createButton("Other3", 700, 160));*/


	//create the close program event
	armyEngine->addEventCallback(EnumEventType::EVENT_CLOSED, [] (int eventIndex) {
		auto armyEngine = ArmyEngine::getInstance();
		auto window = armyEngine->getWindow();
		window->close();
		return 0;
	});


	armyEngine->runMainLoop();

	return 0;
}