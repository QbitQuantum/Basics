void		IA::move(gdl::Clock const& clock, int input, std::vector<AObject*>&object)
{
  float move_val;

  move_val = 1 * static_cast<float>(clock.getElapsed()) * _speed;
  if (input == 0)
    {
      if (_map[round(_x)][round(_y + move_val + 0.4)] != NULL)
	return ;
      _y += 1 * static_cast<float>(clock.getElapsed()) * _speed;
      if (_y >= _height - 2)
	{
	  _y = _height - 2;
	  return ;
	}
      translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    }
  if (input == 1)
    {
      if (_y > 2)
	if (_map[round(_x)][round(_y - move_val - 0.4)] != NULL)
	  return ;
      _y -= 1 * static_cast<float>(clock.getElapsed()) * _speed;
      if (_y < 1)
	{
	  _y = 1;
	  return ;
	}
      translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    }
  if (input == 2)
    {
      if (_map[round(_x + move_val + 0.4)][round(_y)] != NULL)
	return ;
      _x += 1 * static_cast<float>(clock.getElapsed()) * _speed;
      if (_x >= _widht - 2)
	{
	  _x = _widht - 2;
	  return ;
	}
      translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    }    
  if (input == 3)
    {
      if (_map[round(_x - move_val - 0.4)][round(_y)] != NULL)
	return ;
      _x -= 1 * static_cast<float>(clock.getElapsed()) * _speed;
      if (_x < 1)
	{
	  _x = 1;
	  return;
	}
      translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    }
  if (input == 4 && this->_nbbomb != 0)
    {
      AObject *bomb = new Bomb(round(_x), round(_y));
      this->_bomb.push_back(bomb);
      if(bomb->initialize() == false)
	{
	  std::cerr << "Cannot load the bomb" << std::endl;
	  return ;
	}
      object.push_back(bomb);
      this->_nbbomb = 0;
    }
  this->_nbbomb = 1; 
}