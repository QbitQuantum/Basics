void Alien::dropBomb(){

	Image bombImage("assets/redLaserRay.png", true);
	//Sprite* bomb = new Bomb(&bombImage, "Bomb");
	GameObject* bomb = new Bomb(&bombImage, "Bomb");

	bomb->setPosition(getX() + (getW() / 2) - 4, getY() + 30);
	bomb->toggle_collidable();
	GameEngine::getInstance()->getStateManager()->getCurrentState()->addGameObject(bomb);
}