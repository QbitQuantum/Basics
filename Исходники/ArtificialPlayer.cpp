void ArtificialPlayer::update(const gdl::Clock &clock, std::vector<std::vector<AObject *> > &map, std::list<APlayer *> &players)
{
  (void)players;
  this->_elapse = clock.getElapsed();
  if (this->_x != this->_objX || this->_y != this->_objY)
    {
      if (this->_x + (this->_w + this->_w / 10) < this->_objX)
	this->goRight(map, clock);
      else if (this->_x > this->_objX)
	this->goLeft(map, clock);
      else if (this->_y + (this->_h + this->_h / 10) < this->_objY)
	this->goDown(map, clock);
      else if (this->_y > this->_objY)
	this->goUp(map, clock);
      else
	{
	  this->_objX = this->_x;
	  this->_objY = this->_y;
	  this->wait();
	}
    }
  else if (this->isDanger(map, this->_x, this->_y))
    {
      if (!map[this->_y - 1][this->_x] && !this->isDanger(map, this->_x, this->_y - 1))
	this->_objY -= 0.9;
      else if (!map[this->_y][this->_x + 1] && !this->isDanger(map, this->_x + 1, this->_y))
	this->_objX += 0.9;
      else if (!map[this->_y + 1][this->_x] && !this->isDanger(map, this->_x, this->_y + 1))
	this->_objY += 0.9;
      else if (!map[this->_y][this->_x - 1] && !this->isDanger(map, this->_x - 1, this->_y))
	this->_objX -= 0.9;
    }
  else
    {
      this->_objX = this->_x;
      this->_objY = this->_y;
    }
}