ComponentHealth::ComponentHealth(float health, float shield, float rechargeTime)
{
	this->health = health;
	this->maxHealth = health;
	this->shield = shield;
	this->maxShield = shield;
	this->initialHP = health;
	this->initialShield = shield;
	this->rechargeActivated = true;
	// El tiempo que tarda en comenzar a regenerarse el escudo
	this->rechargeTime = rechargeTime; 
	this->rechargeClock = Clock();
	// Tiempo que un jugador puede permanecer derribado antes de morir
	this->deathTime = 40000; // 40 segundos
	this->deathClock = Clock();
	// Tiempo para revivir a un jugador 
	this->reviveTime = 5000; // 5 segundos
	this->reviveClock = Clock();
	this->playersVision = 0;
}