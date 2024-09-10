void regionDataPublisher(zmqpp::socket &publisher, PATH_FIND_NODE &pathFindNode, tbb::concurrent_queue<PathEntity*> &solvedPathQueue, tbb::concurrent_vector<Entity*> entities) {
	using namespace std;

	std::chrono::steady_clock clock;

	// Initialize path.
	for (auto entity : entities) {
		pathFindNode.try_put(std::tuple<size_t, glm::vec2>(entity->id, entity->position));
	}

	while (1) {
		auto start = clock.now();

		// Grab a bunch fo path
		{
			//size_t size = entities.size();
			for (size_t i = 0; i < 200; ++i) {
				PathEntity* pathEntity;
				if (solvedPathQueue.try_pop(pathEntity)) {

					entities[pathEntity->id]->pathNodes = pathEntity->pathNodes;
					entities[pathEntity->id]->currentNode = 0;
				}
			}
		}

		// Traverse nodes
		{
			for (auto entity : entities) {
				if (entity->pathNodes != 0) {
					if (entity->currentNode < entity->pathNodes->size()) {
						size_t currentIndex = (size_t)(*entity->pathNodes)[entity->currentNode++];
						//wss::Utils::indexToXY(currentIndex, MAP_W, entity->position);
						wss::Utils::indexToXY(currentIndex, MAP_W, entity->position);
					}
					else {
						entity->pathNodes = 0;
						pathFindNode.try_put(std::tuple<size_t, glm::vec2>(entity->id, entity->position));
					}
				}
			}
		}

		{
			rapidjson::Document document;
			document.SetObject();
			serializeEntities(document, 0, entities.size(), entities);

			rapidjson::StringBuffer sb;
			rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

			document.Accept(writer);

			publisher.send(sb.GetString());
		}
		std::chrono::duration<double> elapsed = clock.now() - start;
		if (elapsed.count() < 1.0/5.0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000/5 - (size_t)(elapsed.count() * 1000.0)));
		//cout << "elpased region publisher" << endl;
		}

	}
}