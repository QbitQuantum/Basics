bool                MultiShootGraphical::update(sf::Clock const& clock)
{
  bool ret = MultiShoot::update(clock);

  _sprite->setPosition(
		       _pos.x,
		       _pos.y
		       );
  if ((clock.getElapsedTime() - _lastUpdate) > _referential)
    {
      if (_incr)
        {
            if (_angle >= 30)
	      _incr = !_incr;
            _angle++;
        }
      else
        {
	  if (_angle <= -30)
                _incr = !_incr;
	  _angle--;
        }
      _sprite->setRotation(_angle);
      _lastUpdate = clock.getElapsedTime();
    }
  return ret;
}