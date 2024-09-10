double AI::TurnToward(const Ship &ship, const Point &vector)
{
	static const double RAD_TO_DEG = 180. / 3.14159265358979;
	Point facing = ship.Facing().Unit();
	double cross = vector.Cross(facing);
	
	if(vector.Dot(facing) > 0.)
	{
		double angle = asin(cross / vector.Length()) * RAD_TO_DEG;
		if(fabs(angle) <= ship.TurnRate())
			return -angle / ship.TurnRate();
	}
	
	bool left = cross < 0.;
	return left - !left;
}