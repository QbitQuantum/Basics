// Generates a random position in the rectangle created by MinPos and MaxPos
POS_2D GetRandomPosition(POS_2D MinPos, POS_2D MaxPos)
{
	POS_2D newPos;
	newPos.X = rand()%(MaxPos.X-MinPos.X+1) + MinPos.X;
	newPos.Y = rand()%(MaxPos.Y-MinPos.Y+1) + MinPos.Y;

	return newPos;
}