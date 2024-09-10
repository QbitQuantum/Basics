void SeeDif::InsertDialog(Interactor* dialog)
{
  World *world=GetWorld();

  Coord x,y;
  Align(Center, 0, 0, x , y);
  world->InsertTransient(dialog, this, x, y, Center);
}