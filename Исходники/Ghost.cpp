void ChoosePath(Unit &ghost)
{
	int choices = CanMoveTo(ghost, Right)
	              + CanMoveTo(ghost, Left)
	              + CanMoveTo(ghost, Up)
	              + CanMoveTo(ghost, Down);

	if(ghost.Rotating == false && choices >= 3)
	{
		Direction backwards = Invert(ghost.Face);
		do
		{
			ghost.Face = (Direction) (rand() % 4);
		} while(CanMove(ghost) == false || ghost.Face == backwards);

		ghost.Rotating = true;
	}
}