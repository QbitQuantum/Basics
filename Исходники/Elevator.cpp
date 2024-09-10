Elevator::Elevator(const int cap, const int spd, const Floor& startFloor)
  : ID(Elevator::elevatorID), capacity(cap), speed(spd), toFloor(0)
{
  elevatorID++;
  location = startFloor.getLocation();
  direction = IDLE;
  doorOpen = true;
}