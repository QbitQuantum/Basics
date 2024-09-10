ComponentBulletLauncher::ComponentBulletLauncher(float damage, float fireRate,void (ComponentBulletLauncher::*fnc)())
{
	gameObjectManager = GameManager::getInstance()->getGameObjectManager();
	this->damage = damage;
	delay = Clock();
	shooting = false;
	targetObject = NULL;
	this->fireRate = fireRate;
	superShoot = fnc;
}