int cScene::getTile(glm::vec3 p) {
	//std::cout << floor(playerx) << " " << ceil(playerz) + 0.5f << std::endl; 
	return map[ceil(playerx + 0.1f)][ceil(playerz) + 0.5f];
}