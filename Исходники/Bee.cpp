/*
 * Update
 */
void Bee::update(sf::Time dt)
{
	action(dt);
	move(dt);
	if(moveState_ == MoveState::REST){
		energy_ -= getConfig()["energy"]["consumption rates"]
		["idle"].toDouble()*dt.asSeconds();
	}else if(moveState_ == MoveState::TARGET ||
			 moveState_ == MoveState::RAND){
		energy_ -= getConfig()["energy"]["consumption rates"]
		["moving"].toDouble()*dt.asSeconds();
	}	
	if(energy_ <= 0){ throw energy_; }
}