bool			AObject::dropBomb()
{
  if (_simult > 0)
    {
      AObject *bomb;

      bomb = new Bomb();
      if (bomb->initialize() == false)
  	return false;
      bomb->setPos(getPos());
      bomb->setRange(getRange());
      getMap()->setBox(bomb->getPos(), Map::BOMB);
      _bomb.push_back(bomb);
      setSimult(getSimult() - 1);
      _time = 0;
    }
  return true;
}