bool			Human::update(gdl::AShader &s, const gdl::Clock &c, gdl::Input &i, const std::vector<Block *> &list, const std::vector<Block *> &wall, std::vector<Bonus *> &listBonus)
{
  glm::mat4		transformation;

  transformation = glm::lookAt(glm::vec3(this->_position.x, this->_position.y - 3, 5), glm::vec3(this->_position.x, this->_position.y, this->_position.z), glm::vec3(0, 1, 0));
  s.setUniform("view", transformation);
  if (this->_number == 0)
    {
      if (i.getKey(SDLK_DOWN))
	{
	  double	x = round(this->_position.x);
	  double	y = round(this->_position.y - 0.5);
	  for (double i = 0; i < list.size(); ++i)
	    {
	      if (x == round(list[i]->getPos().x) && y == round(list[i]->getPos().y) && this->_position.z == list[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < wall.size(); ++i)
	    {
	      if (x == round(wall[i]->getPos().x) && y == round(wall[i]->getPos().y) && this->_position.z == wall[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < listBonus.size(); i++)
	    {
	      if (x == round(listBonus[i]->getPos().x) && y == round(listBonus[i]->getPos().y))
		{
		  this->pickUpBonus(listBonus, i);
		}
	    }
	  switch (this->_dir)
	    {
	    case Player::UP:
	      this->rotate(glm::vec3(0, -1, 0), 180);
	      break;
	    case Player::LEFT:
	      this->rotate(glm::vec3(0, -1, 0), 270);
	      break;
	    case Player::RIGHT:
	      this->rotate(glm::vec3(0, -1, 0), 90);
	      break;
	    }
	  this->_dir = Player::DOWN;      
	  this->translate(glm::vec3(0, -1, 0) * static_cast<float>(c.getElapsed()) * this->speed);
	}
      if (i.getKey(SDLK_UP))
	{
	  double	x = round(this->_position.x);
	  double	y = round(this->_position.y + 0.5);
 
	  for (double i = 0; i < list.size(); ++i)
	    {
	      if (x == round(list[i]->getPos().x) && y == round(list[i]->getPos().y) && this->_position.z == list[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < wall.size(); ++i)
	    {
	      if (x == round(wall[i]->getPos().x) && y == round(wall[i]->getPos().y) && this->_position.z == wall[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < listBonus.size(); i++)
	    if (x == round(listBonus[i]->getPos().x) && y == round(listBonus[i]->getPos().y))
	      this->pickUpBonus(listBonus, i);
	  switch (this->_dir)
	    {
	    case Player::DOWN:
	      this->rotate(glm::vec3(0, -1, 0), 180);
	      break;
	    case Player::LEFT:
	      this->rotate(glm::vec3(0, -1, 0), 90);
	      break;
	    case Player::RIGHT:
	      this->rotate(glm::vec3(0, -1, 0), 270);
	      break;
	    }
	  this->_dir = Player::UP;    
	  this->translate(glm::vec3(0, 1, 0) * static_cast<float>(c.getElapsed()) * this->speed);
	}
      if (i.getKey(SDLK_RIGHT))
	{
	  double	x = round(this->_position.x + 0.5);
	  double	y = round(this->_position.y);

	  for (double i = 0; i < list.size(); ++i)
	    {
	      if (x == round(list[i]->getPos().x) && y == round(list[i]->getPos().y) && this->_position.z == list[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < wall.size(); ++i)
	    {
	      if (x == round(wall[i]->getPos().x) && y == round(wall[i]->getPos().y) && this->_position.z == wall[i]->getPos().z)
		return (true);
	    }    
	  for (double i = 0; i < listBonus.size(); i++)
	    if (x == round(listBonus[i]->getPos().x) && y == round(listBonus[i]->getPos().y))
	      this->pickUpBonus(listBonus, i);
	  switch (this->_dir)
	    {
	    case Player::UP:
	      this->rotate(glm::vec3(0, -1, 0), 90);
	      break;
	    case Player::LEFT:
	      this->rotate(glm::vec3(0, -1, 0), 180);
	      break;
	    case Player::DOWN:
	      this->rotate(glm::vec3(0, -1, 0), 270);
	      break;
	    }
	  this->_dir = Player::RIGHT;    
	  this->translate(glm::vec3(1, 0, 0) * static_cast<float>(c.getElapsed()) * this->speed);
	}
      if (i.getKey(SDLK_LEFT))
	{
	  double	x = round(this->_position.x - 0.5);
	  double	y = round(this->_position.y);

	  for (double i = 0; i < list.size(); ++i)
	    {
	      if (x == round(list[i]->getPos().x) && y == round(list[i]->getPos().y) && this->_position.z == list[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < wall.size(); ++i)
	    {
	      if (x == round(wall[i]->getPos().x) && y == round(wall[i]->getPos().y) && this->_position.z == wall[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < listBonus.size(); i++)
	    if (x == round(listBonus[i]->getPos().x) && y == round(listBonus[i]->getPos().y))
	      this->pickUpBonus(listBonus, i);
	  switch (this->_dir)
	    {
	    case Player::RIGHT:
	      this->rotate(glm::vec3(0, -1, 0), 180);
	      break;
	    case Player::UP:
	      this->rotate(glm::vec3(0, -1, 0), 270);
	      break;
	    case Player::DOWN:
	      this->rotate(glm::vec3(0, -1, 0), 90);
	      break;
	    }
	  this->_dir = Player::LEFT;
	  this->translate(glm::vec3(-1, 0, 0) * static_cast<float>(c.getElapsed()) * this->speed);
	}
    }  
  if (this->_number == 1)
    {
      if (i.getKey(SDLK_s))
	{
	  double	x = round(this->_position.x);
	  double	y = round(this->_position.y - 0.5);

	  for (double i = 0; i < list.size(); ++i)
	    {
	      if (x == round(list[i]->getPos().x) && y == round(list[i]->getPos().y) && this->_position.z == list[i]->getPos().z)
		return (true);
	    }

	  for (double i = 0; i < wall.size(); ++i)
	    {
	      if (x == round(wall[i]->getPos().x) && y == round(wall[i]->getPos().y) && this->_position.z == wall[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < listBonus.size(); i++)
	    if (x == round(listBonus[i]->getPos().x) && y == round(listBonus[i]->getPos().y))
	      this->pickUpBonus(listBonus, i);
	  switch (this->_dir)
	    {
	    case Player::UP:
	      this->rotate(glm::vec3(0, -1, 0), 180);
	      break;
	    case Player::LEFT:
	      this->rotate(glm::vec3(0, -1, 0), 270);
	      break;
	    case Player::RIGHT:
	      this->rotate(glm::vec3(0, -1, 0), 90);
	      break;
	    }
	  this->_dir = Player::DOWN;      
	  this->translate(glm::vec3(0, -1, 0) * static_cast<float>(c.getElapsed()) * this->speed);
	}
      if (i.getKey(SDLK_z))
	{
	  double	x = round(this->_position.x);
	  double	y = round(this->_position.y + 0.5);

	  for (double i = 0; i < list.size(); ++i)
	    {
	      if (x == round(list[i]->getPos().x) && y == round(list[i]->getPos().y) && this->_position.z == list[i]->getPos().z)
		return (true);
	    }        
	  for (double i = 0; i < wall.size(); ++i)
	    {
	      if (x == round(wall[i]->getPos().x) && y == round(wall[i]->getPos().y) && this->_position.z == wall[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < listBonus.size(); i++)
	    if (x == round(listBonus[i]->getPos().x) && y == round(listBonus[i]->getPos().y))
	      this->pickUpBonus(listBonus, i);
	  switch (this->_dir)
	    {
	    case Player::DOWN:
	      this->rotate(glm::vec3(0, -1, 0), 180);
	      break;
	    case Player::LEFT:
	      this->rotate(glm::vec3(0, -1, 0), 90);
	      break;
	    case Player::RIGHT:
	      this->rotate(glm::vec3(0, -1, 0), 270);
	      break;
	    }
	  this->_dir = Player::UP;    
	  this->translate(glm::vec3(0, 1, 0) * static_cast<float>(c.getElapsed()) * this->speed);
	}
      if (i.getKey(SDLK_d))
	{
	  double	x = round(this->_position.x + 0.5);
	  double	y = round(this->_position.y);

	  for (double i = 0; i < list.size(); ++i)
	    {
	      if (x == round(list[i]->getPos().x) && y == round(list[i]->getPos().y) && this->_position.z == list[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < wall.size(); ++i)
	    {
	      if (x == round(wall[i]->getPos().x) && y == round(wall[i]->getPos().y) && this->_position.z == wall[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < listBonus.size(); i++)
	    if (x == round(listBonus[i]->getPos().x) && y == round(listBonus[i]->getPos().y))
	      this->pickUpBonus(listBonus, i);
	  switch (this->_dir)
	    {
	    case Player::UP:
	      this->rotate(glm::vec3(0, -1, 0), 90);
	      break;
	    case Player::LEFT:
	      this->rotate(glm::vec3(0, -1, 0), 180);
	      break;
	    case Player::DOWN:
	      this->rotate(glm::vec3(0, -1, 0), 270);
	      break;
	    }
	  this->_dir = Player::RIGHT;    
	  this->translate(glm::vec3(1, 0, 0) * static_cast<float>(c.getElapsed()) * this->speed);
	}
      if (i.getKey(SDLK_q))
	{
	  double	x = round(this->_position.x - 0.5);
	  double	y = round(this->_position.y);

	  for (double i = 0; i < list.size(); ++i)
	    {
	      if (x == round(list[i]->getPos().x) && y == round(list[i]->getPos().y) && this->_position.z == list[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < wall.size(); ++i)
	    {
	      if (x == round(wall[i]->getPos().x) && y == round(wall[i]->getPos().y) && this->_position.z == wall[i]->getPos().z)
		return (true);
	    }
	  for (double i = 0; i < listBonus.size(); i++)
	    if (x == round(listBonus[i]->getPos().x) && y == round(listBonus[i]->getPos().y))
	      this->pickUpBonus(listBonus, i);
	  switch (this->_dir)
	    {
	    case Player::RIGHT:
	      this->rotate(glm::vec3(0, -1, 0), 180);
	      break;
	    case Player::UP:
	      this->rotate(glm::vec3(0, -1, 0), 270);
	      break;
	    case Player::DOWN:
	      this->rotate(glm::vec3(0, -1, 0), 90);
	      break;
	    }
	  this->_dir = Player::LEFT;
	  this->translate(glm::vec3(-1, 0, 0) * static_cast<float>(c.getElapsed()) * this->speed);
	}
    }
  transformation = glm::lookAt(glm::vec3(this->_position.x, this->_position.y - 3, 5), glm::vec3(this->_position.x, this->_position.y, this->_position.z), glm::vec3(0, 1, 0));
  s.setUniform("view", transformation);
  return (true);
}